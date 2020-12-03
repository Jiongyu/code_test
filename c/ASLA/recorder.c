#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

//socket
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// alsa
#include <alsa/asoundlib.h>

//signal
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
    // pcm属性
    snd_pcm_hw_params_t *params;
    
    // 打开设备
    int ret = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if(ret < 0 )
    {
        perror("snd_pcm_open failed!");
        return -1;
    }

    // 初始化pcm参数
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);

    // 交错模式
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

    // 设置双声道，小端格式，16位
    unsigned int channels = 2;
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
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
	snd_pcm_hw_params_get_rate(params, &val, 0);
    printf("one period have %d frames\n", frames);
    printf("sound capture frequence were %d hz\n", val);

    // 由于双通道， 16bit， 每个通道两个字节， 一个周期所需空间大小 4 × frames
    unsigned char *buffer  = malloc(channels * 2 * frames);

    // 写入设备
    ret = snd_pcm_hw_params(handle, params);
    if(ret < 0)
    {
        perror("snd_pcm_hw_params failed");
        return -1;
    }
    printf("sound device init set success!\n");

    // 初始化网络 udp
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);    

	struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_);
    addr.sin_addr.s_addr = htonl(IP_);

    printf("socket set success!\n");

    while (run_)
    {
        // 录音，返回帧数
        ret = snd_pcm_readi(handle, buffer, frames);
        if(ret != frames){
            printf("snd_pcm_readi: %s\n", snd_strerror(ret));
            snd_pcm_prepare(handle);
            continue;
        }
        ret = sendto(sockfd,  buffer, frames * channels * 2, 0, (struct sockaddr *)&addr, sizeof(addr));
        if(ret != frames * channels * 2){
            break;
        }

        // printf("record... \n");
    }

    close(sockfd);
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);

    return 0;
}
