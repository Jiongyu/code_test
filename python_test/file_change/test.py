#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-


class File_convert(object):
    def __init__(self):
        self.__joint_num = 5
        self.__current_dera = [0,0,0,15,0]
        self.__time_data = []
        self.__torque_data = []

        self.__save_file = './temp_save.txt'
        self.__read_file = './temp_read.txt'

        pass
    def __get_file_data(self):
        print("get file data start")

        with open(self.__read_file ,'r') as file:
            temp_line = file.readline()
            while temp_line:
                temp_line = temp_line.replace('\n','')
                temp_lineData = temp_line.split(' ')
                self.__time_data.append(float(temp_lineData[-1]))
                self.__torque_data.append(temp_lineData[0:5])
                temp_line = file.readline()
        print("get file data success")

    def __fix_data(self):
        print("fix data start")

        length = len(self.__time_data)
        if(length == 0):
            print("data is null.")
            return

        for i in range(length):
            for j in range(self.__joint_num):
                    self.__torque_data[i][j] = float(self.__torque_data[i][j]) + self.__current_dera[j]
        print("fix data success")
        pass

    def __write_file_data(self):
        print("write data start")
        with open(self.__save_file, 'w') as file:
            for i in range(len(self.__time_data)):
                for j in range(len(self.__torque_data[i])):
                    file.write(str(self.__torque_data[i][j]) + str(' '))
                file.write(str(self.__time_data[i]) + '\n')
        print("write data success")



    def get_solution(self):
        self.__get_file_data()
        self.__fix_data()
        self.__write_file_data()
        pass


if __name__ == '__main__':
    demo = File_convert()
    demo.get_solution()

        