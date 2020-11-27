# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt

import time

def on_connect(client, userdata, flags, rc):
    print("Connected with result code: " + str(rc))

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))    

client = mqtt.Client()
#设置用户名和密码
# client.username_pw_set("jony", "12345")
client.on_connect = on_connect
client.on_message = on_message
#连接 IP port keepalive
# client.connect('localhost', 1883, 600)

client.connect_async('localhost', 1883, 600)
client.reconnect()

# #订阅的 topic
client.subscribe('temperature/fahrenheit', qos=0)


# client.subscribe('test', qos=1)

# client.loop_forever()

client.loop_start()
time.sleep(5)
client.loop_stop()

client.disconnect()

# mosquitto_sub -h localhost -t "test/#" -u jony -P 12345 -i "client1"

# # 订阅客户端存活连接数
# mosquitto_sub -h localhost -t '$SYS/broker/clients/active' -u jony -P 12345 -i "client2"

# mosquitto_pub -h localhost -t "test/abc" -u jony -P 12345 -i "client3" -m "How are you?"

# mosquitto_pub -h localhost -t "temperature/celsius" -m "123"  
