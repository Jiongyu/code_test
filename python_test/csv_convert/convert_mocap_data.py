#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import math
import csv

class Convert_Mocap_Data(object):

    def __init__(self, ros_topic = ['/vrpn_client_node/jonydata/pose']):
        self.__file_dir = None
        self.__ros_topic = ros_topic
        pass

    def convert_mocap_data(self):
        self.__file_dir = os.listdir(os.getcwd())
        self.__convert_mocap_data()
        pass

    def __convert_mocap_data(self):
        # 遍历当前文件夹
        for i in range(len(self.__file_dir)):
            last_dir_path = os.getcwd()
            # 判断是否为文件夹
            if (os.path.isdir(self.__file_dir[i])):
                print( "\n" + self.__file_dir[i] + ":")
                os.chdir(self.__file_dir[i])
                # 转换bag --> csv
                self.__convert_bag_csv()
                # 转换时间,位置,姿态
                self.__convert_time_pos_post()
            os.chdir(last_dir_path)
        # 已回到工程根目录
        # print(os.getcwd())
        pass

    def __convert_time_pos_post(self):

        temp_file = os.listdir()
        for i in range(len(temp_file)):
            if(os.path.isfile(temp_file[i])):
                if(temp_file[i].endswith('.csv')):
                    with open(temp_file[i], 'r') as f:

                        save_file = temp_file[i].split('.')[0] + '.txt'
                        print(save_file)
                        reader = csv.reader(f)
                        next(reader)

                        with open(save_file , 'w') as fw:
                            for row in reader:
                                # 修改时间单位
                                time_ = self.__convert_time(int(row[0]))
                                fw.write(str(time_) + ' ')
                                # 修改位置单位 x, y, z
                                temp_pos_ = self.__convert_position(float(row[4]))
                                fw.write(str(temp_pos_) + ' ')
                                temp_pos_ = self.__convert_position(float(row[5]))
                                fw.write(str(temp_pos_) + ' ')
                                temp_pos_ = self.__convert_position(float(row[6]))
                                fw.write(str(temp_pos_) + ' ')
                                # 转换四元数为欧拉角
                                temp_posture_ = self.__quat_to_eular(float(row[7]),float(row[8]),float(row[9]),float(row[10]))
                                for i in range(len(temp_posture_)):
                                    fw.write(str(temp_posture_[i]) + ' ')
                                fw.write('\n')

    # bag --> csv
    def __convert_bag_csv(self):
        temp_dir_file_ = os.listdir(os.getcwd())
        for i in range(len(temp_dir_file_)):
            if (os.path.isfile(temp_dir_file_[i])):
                if (temp_dir_file_[i].endswith('.bag')):
                    for j in range(len(self.__ros_topic)):
                        save_file = temp_dir_file_[i].split('.')[0] + self.__ros_topic[j].replace('/', '_') + ".csv"
                        print(save_file)
                        os.system("rostopic echo -b " + temp_dir_file_[i] + " -p "  + self.__ros_topic[j] + " > " + save_file)

    # ns --> s
    def __convert_time(self, time):
        return  time * 1e-9

    # m --> mm
    def __convert_position(self, pos):
        return pos * 1e3

    # 四元数 转欧拉角
    def __quat_to_eular(self, x, y, z, w):

        r = math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y))
        p = math.asin(2 * (w * y - x * z))
        y = math.atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y))

        angleR = r * 180 / math.pi
        angleP = p * 180 / math.pi
        angleY = y * 180 / math.pi

        return (angleR, angleP, angleY)

if __name__ == "__main__":
    demo = Convert_Mocap_Data()
    demo.convert_mocap_data()
