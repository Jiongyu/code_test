#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// scoket
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// asla
#include <alsa/asoundlib.h>

// signal
#include <signal.h>

#define PORT_ 8888
// 本地IP
#define IP_ INADDR_ANY 

int run_ = 1;

void signal_hander()
{   
    run_ = 0;
    // printf("signal_hander activated.\n");
}

int main(int argc, char const *argv[])
{   

    // signal 注册
    signal(SIGINT, signal_hander);
    signal(SIGABRT, signal_hander);
    signal(SIGTERM, signal_hander);

    // pcm 句柄
    snd_pcm_t *handle;
    // pcm硬件属性
    snd_pcm_hw_params_t *params;
    // pcm  软件属性
    snd_pcm_sw_params_t *params_sw;
    
    // 打开设备
    int ret = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if(ret < 0 )
    {
        perror("snd_pcm_open failed!");
        return -1;
    }

    // 初始化pcm参数
    snd_pcm_hw_params_alloca(&params);
	snd_pcm_sw_params_alloca(&params_sw);

    snd_pcm_hw_params_any(handle, params);

    // 交错模式
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

    // 设置双声道，小端格式，16位
    unsigned int channels = 2;
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
    snd_pcm_hw_params_set_format(handle, params, format);
    snd_pcm_hw_params_set_channels(handle, params, channels);

    // 设置采样频率（44100 ,MP3采样赫兹）
    int val = 44100;
    snd_pcm_hw_params_set_rate_near(handle, params, &val, 0);

    // 设置采样周期
    // int frames = 4; // 高内存占用，实时好
    int frames = 4410; 
    snd_pcm_hw_params_set_period_size_near(handle, params, (snd_pcm_uframes_t *)&frames, 0);

    // 获取一个周期有多少帧数据组成
    snd_pcm_hw_params_get_period_size(params, (snd_pcm_uframes_t *)&frames, 0);

    // 设置缓冲区大小
    int bufferSize = 4 * frames;
    snd_pcm_hw_params_set_buffer_size(handle, params, bufferSize);

    // 由于双通道， 16bit， 每个通道两个字节， 一个周期所需空间大小 4 × frames
    unsigned char *buffer  = malloc(channels * 2 * frames);

    // 写入设备
    ret = snd_pcm_hw_params(handle, params);
    if(ret < 0)
    {
        perror("snd_pcm_hw_params failed");
        return ret;
    }

    // 获取 sw 当前param
    ret = snd_pcm_sw_params_current(handle, params_sw);
    if(ret < 0)
    {
       	printf("Unable to determine current swparams for playback: %s\n", snd_strerror(ret));
        return ret;
    }

	/* start the transfer when the buffer is almost full: */
	/* (buffer_size ) */
	// Set start threshold inside a software configuration container
	ret = snd_pcm_sw_params_set_start_threshold(handle, params_sw, bufferSize);
	if (ret < 0) {
		printf("Unable to set start threshold mode for playback: %s\n", snd_strerror(ret));
		return -1;
	}

	// /* allow the transfer when at least period_size samples can be processed */
	// /* or disable this mechanism when period event is enabled (aka interrupt like style processing) */
	// ret = snd_pcm_sw_params_set_avail_min(handle, params_sw, frames);
	// if (ret < 0) {
	// 	printf("Unable to set avail min for playback: %s\n", snd_strerror(ret));
	// 	return ret;
	// }

	/* write the parameters to the playback device */
    ret = snd_pcm_sw_params(handle, params_sw);
    if(ret < 0)
    {
		printf("Unable to set sw params for playback: %s\n", snd_strerror(ret));
		return ret;
    }

    printf("sound device init set success!\n");

    // 初始化网络 udp
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);    

	struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_);
    addr.sin_addr.s_addr = htonl(IP_);
    
    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind failed!");
        free(buffer);
        return -1;
    }

    // 设置udp receive timeout 5s
    struct timeval tv;
    tv.tv_sec = 5; // 5s
    tv.tv_usec = 0;

    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0 ){
        perror("setsockopt(SO_RCVTIMEO) failed.");
        free(buffer);
        return -1;
    }

    printf("socket set success!\n");

    while (run_)
    {
        ret = recvfrom(sockfd, buffer, frames * channels * 2, 0, NULL, NULL);
        if(ret < 0){
            perror("recvfrom failed ");
            continue;
        }

        ret = snd_pcm_writei(handle, buffer, frames);
        // 音频写错误snd_pcm_writei : Broken pipe。 重置错误
		if (ret < 0)
        {
			printf("snd_pcm_writei : %s \n", snd_strerror(ret));
            ret = snd_pcm_recover(handle, ret, 0);
            if (ret < 0)
            {
                printf("snd_pcm_recover: %s\n", snd_strerror(ret));
                break;
            }
        }
        // printf("play...\n");
    }

    close(sockfd);

    snd_pcm_drain(handle);
    snd_pcm_close(handle);

    free(buffer);
    return 0;
}
