ffmpeg -f video4linux2 -qscale 10 -r 12 -s 640x480 -i /dev/video0 -f alsa -i hw:1 -ab 16 -ar 22050 -ac 1 -f mp3 -f flv rtmp://192.168.1.5/rtmpsvr/rtmp1 -loglevel debug

ffmpeg -f video4linux2 -r 12 -s 640x480 -i /dev/video0 -ab 16 -ar 22050 -ac 1 -f mp3 -f flv rtmp://127.0.0.1/rtmpsvr/rtmp1 -loglevel debug

ffmpeg -f video4linux2 -s 640x480 -pixel_format yuyv422  -i /dev/video0  out.mp4 -loglevel debug


ffmpeg -f dshow -i video="Logitech Webcam C930e" -vcodec libx264 -preset:v ultrafast -tune:v zerolatency -rtsp_transport tcp -f rtsp rtsp://192.168.1.5/test


ffmpeg -rtsp_transport tcp -i rtsp://{}:{}@{} -an -vcodec copy -f h264 -t {} {}

str_acmd = "ffmpeg -rtsp_transport tcp -i rtsp://{}:{}@{} -an -vcodec copy -f h264 -t {} {}"
cmd = str_cmd.format(user, passwd, ip, time, videoPath)

ffmpeg -rtsp_transport tcp -i rtsp://127.0.0.1 -an -vcodec copy -f h264 -t 100 ./


可能用到的命令：
1）启动基于Nginx的rtmp服务
/usr/local/nginx/sbin/nginx -c nginx.conf的路径

2）ffmpeg命令：
推流：ffmpeg -re -i localFile.mp4 -c copy -f flv rtmp://live.hkstv.hk.lxdns.com/live/hks
收流：ffmpeg -i rtmp://live.hkstv.hk.lxdns.com/live/hks -c copy dump.flv

3）打开或关闭1935端口：
打开：iptables -A INPUT -p tcp --dport 1935 -j DROP
关闭：iptables -A OUTPUT -p tcp --dport 1935 -j DROP

iptables -A INPUT -p tcp --dport 1935 -j ACCEPT
iptables -A OUTPUT -p tcp --sport 1935 -j ACCEPT

service iptables save
4）关闭防火墙
iptables -F