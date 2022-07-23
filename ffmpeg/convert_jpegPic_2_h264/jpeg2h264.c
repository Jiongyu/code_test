/** 
实现最新版FFMPEG把JPEG图像数据编码为264数据，作者自己测试正确可用 
作者：明天继续
使用的ffmpeg版本：ffmpeg-20180508-293a6e8-win32 
开发工具：vs2012 
**/  
  
#include "stdafx.h"  
#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
extern "C" {  
#include <libavcodec/avcodec.h>  
#include <libavformat/avformat.h>  
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
 
}  
  
#define INBUF_SIZE 4096
#pragma comment(lib,"../../ffmpeg-20180508-293a6e8-win32-dev/lib/avcodec.lib")  
#pragma comment(lib,"../../ffmpeg-20180508-293a6e8-win32-dev/lib/avformat.lib")  
#pragma comment(lib,"../../ffmpeg-20180508-293a6e8-win32-dev/lib/avfilter.lib")  
#pragma comment(lib,"../../ffmpeg-20180508-293a6e8-win32-dev/lib/avutil.lib")  
#pcommentragma (lib,"../../ffmpeg-20180508-293a6e8-win32-dev/lib/swscale.lib") 
  
#if _MSC_VER  
#define snprintf _snprintf_s  
#define PRIx64       "I64x"  
#define PRIX64       "I64X"  
#endif  
 
 
 
//编码frame 中的数据，pkt用于临时存储编码结果
static void encode_yuv_to_264(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
				   FILE *outfile)
{
	int ret;
 
	/* send the frame to the encoder */
 
	ret = avcodec_send_frame(enc_ctx, frame);
	if (ret < 0) {
		fprintf(stderr, "Error sending a frame for encoding\n");
		exit(1);
	}
 
	while (ret >= 0) {
		ret = avcodec_receive_packet(enc_ctx, pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			return;
		else if (ret < 0) {
			fprintf(stderr, "Error during encoding\n");
			exit(1);
		}
 
		fwrite(pkt->data, 1, pkt->size, outfile);
		av_packet_unref(pkt);
	}
}
 
 
//解码jpeg数据，并编码为h264保存到文件
static void decode_jpg_and_encode_264(AVCodecContext *dec_ctx, //jpeg解码器上下文
									  AVFrame *frameyuv, //存放中间解码获取的yuv数据
									  AVPacket *pktjpg,//输入数据中解析出的jpeg数据包
									  AVCodecContext *codech264,//h264的编码器上下文
									  AVPacket* packh264,//临时存储编码出的h264数据包
                                      FILE* file, //输出文件
									  int64_t pts)//时间戳
{
 
    int ret;
 
    ret = avcodec_send_packet(dec_ctx, pktjpg);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }
 
    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frameyuv);//解码一帧数据
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }
 
        printf("saving frame %3d\n", dec_ctx->frame_number);
        fflush(stdout);
        /* 图片是解码器分配的内存，不需要释放 */        
		frameyuv->pts = pts;
 
		 encode_yuv_to_264(codech264, frameyuv, packh264, file);
 
    }
}
 
 
long getFileSize(const char* sFile)
{
	FILE* f = fopen(sFile, "rb");
	fseek(f,0,SEEK_END);
	long s = ftell(f);
	fclose(f);
	return s;
}
 
//测试把yuv编码为h264
void test_Jpeg_to_Yuv_To_H264()
{
	const char *out_filename,//保存的h24文件名字
		*codec_name;//编码器的名字，ffmpeg.exe查看所有支持的编码器名字：ffmpeg -encoders
    const AVCodec *codec_264;//264的编码器
    AVCodecContext *codec_context_264= NULL;//264编码器上下文
    int i, ret, x, y;
    FILE *file_264;//264文件指针
    AVFrame *frame_yuv;//保存yuv数据帧
    AVPacket *pkt_264,//临时保存编码出的264包数据
		*pkt_jpg;//临时保存jpeg包数据
 
 
	av_register_all();  
 
	//保存的h24文件名字
    out_filename = "out.h264";
 
	//编码为h264
    codec_name = "libx264";
 
    /* 找到h264的编码器 */
    codec_264 = avcodec_find_encoder_by_name(codec_name);
    if (!codec_264) {
        fprintf(stderr, "Codec '%s' not found\n", codec_name);
        exit(1);
    }
 
	//生成h264的编码器上下文
    codec_context_264 = avcodec_alloc_context3(codec_264);
    if (!codec_context_264) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }
 
	//分配264包的临时存储空间
    pkt_264 = av_packet_alloc();
    if (!pkt_264)
        exit(1);
 
	//分配jpeg包的临时存储
	pkt_jpg = av_packet_alloc();
 
    /* 设置比特率 */
    codec_context_264->bit_rate = 400000;
    /* 设置需要编码的jpeg文件的分辨率，注意此处的分辨率应该和你要使用的jpeg数据的分辨率一致*/
    codec_context_264->width = 160;
    codec_context_264->height = 128;
    /* 设置帧率 每秒25帧*/
    codec_context_264->time_base.num = 1;
	codec_context_264->time_base.den = 25;
    codec_context_264->framerate.num = 25;
	codec_context_264->framerate.den = 1;
 
 
    codec_context_264->gop_size = 10;
    codec_context_264->max_b_frames = 1;
    codec_context_264->pix_fmt = AV_PIX_FMT_YUV420P;//设置编码器像素格式
 
    if (codec_264->id == AV_CODEC_ID_H264)
        av_opt_set(codec_context_264->priv_data, "preset", "slow", 0);
 
    /* 打开解码器 */
    ret = avcodec_open2(codec_context_264, codec_264, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }
 
	//打开要输出的264文件
    file_264 = fopen(out_filename, "wb");
    if (!file_264) {
        fprintf(stderr, "Could not open %s\n", out_filename);
        exit(1);
    }
 
	//分配保存yuv帧的临时存储
    frame_yuv = av_frame_alloc();
    if (!frame_yuv) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
 
	jpeg解码
	//jpeg解码器解析上下文
	AVCodecParserContext *parser_jpg;
	//jpeg解码器
	const AVCodec *codec_jpg;
	//jpeg的解码上下文
	AVCodecContext *codecContext_jpg= NULL;
	//查找jpeg的解码器
	codec_jpg = avcodec_find_decoder(AV_CODEC_ID_MJPEG);
	//初始化jpeg的解码器解析上下文
	parser_jpg = av_parser_init(codec_jpg->id);
	//jpeg的解码器上下文
	codecContext_jpg = avcodec_alloc_context3(codec_jpg);
	//打开jpeg解码器
	if (avcodec_open2(codecContext_jpg, codec_jpg, NULL) < 0) {
		fprintf(stderr, "Could not open codec\n");
		exit(1);
	}
    /* 循环编码250帧图片，帧率为25，所以生成的视频长度约为10秒，生成的h264文件可以用vlc软件播放 */
    for (i = 1; i <= 250; i++) {
        fflush(stdout);
		//读取jpeg图像数据
		std::string imageData;
		//250张图片放在程序路径下的image/文件夹下，命名规则是1.jpg  2.jpg  3.jpg  ...... 250.jpg
		char jpeName[256]={0};
		snprintf(jpeName, sizeof(jpeName), "image/%d.%s", i,"jpg");
		long filesize = getFileSize(jpeName);
		if (filesize > imageData.size())
		{
			imageData.resize(filesize);
		}		
		FILE* fileImage = fopen(jpeName, "rb");
		fread(&(imageData[0]),1,filesize,fileImage);
		fclose(fileImage);
 
		//把读取的jpeg数据解析为包		
		uint8_t *tempdata = (uint8_t *)(imageData.data());
		size_t   tempdata_size = filesize;
		while (tempdata_size > 0) {
			ret = av_parser_parse2(parser_jpg, codecContext_jpg, &pkt_jpg->data, &pkt_jpg->size,
				tempdata, tempdata_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
			if (ret < 0) {
				fprintf(stderr, "Error while parsing\n");
				exit(1);
			}
			tempdata      += ret;
			tempdata_size -= ret;
 
			if (pkt_jpg->size)
				decode_jpg_and_encode_264(codecContext_jpg, frame_yuv, pkt_jpg, codec_context_264,pkt_264,file_264,i);
		}
    }
	//处理最后可能残余的数据
    encode_yuv_to_264(codec_context_264, NULL, pkt_264, file_264);
 
    fclose(file_264);
 
    avcodec_free_context(&codec_context_264);
	av_frame_free(&frame_yuv);
    av_packet_free(&pkt_264);
	av_packet_free(&pkt_jpg);
	av_parser_close(parser_jpg);
	avcodec_free_context(&codecContext_jpg);
 
}
 
  
int _tmain(int argc, _TCHAR* argvec[])  
{  
   test_Jpeg_to_Yuv_To_H264();
    return 0;
}  