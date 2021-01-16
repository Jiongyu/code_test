#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

class Change_file_direction(object):
    
    def __init__(self):
        self.__save_file = "./temp_save.txt"
        self.__read_file = "./temp_read.txt"

        self.__direction = [1, 1, 1, 1, 1]

        self.__axis = [1,2,3,4,5]

        self.__current_dera = [0,0,0,0,0]
        self.__time_data = []
        self.__current_data = []

        pass

    def changeFileDirection(self):
        self.__read_data()
        self.__sub_value()
        self.__write_data()

    def __read_data(self):
        with open(self.__read_file, 'r') as fr:
                temp_line = fr.readline()
                while temp_line:
                    temp_line = temp_line.replace('\n','')
                    temp_lineData = temp_line.split(' ')
                    
                    temp_time_data = float(temp_lineData[-1])
                    self.__time_data.append(temp_time_data)

                    temp_current_data = temp_lineData[0:5]
                    self.__current_data.append(temp_current_data)
                    
                    temp_line = fr.readline()

    def __sub_value(self):
        for i in range(len(self.__time_data)):
            for j in range(len(self.__current_data[i])):
                self.__current_data[i][j] = float(self.__current_data[i][j]) + self.__current_dera[j]
        pass

    def __write_data(self):
        with open(self.__save_file, 'w') as fw:
            for i in range(len(self.__time_data)):
                for j in range(len(self.__current_data[i])):
                    fw.write(str(float(self.__current_data[i][self.__axis[j] - 1]) * self.__direction[self.__axis[j] - 1]) + " ")
                fw.write(str(self.__time_data[i]))
                fw.write("\n")

if __name__ == "__main__":
    demo = Change_file_direction()
    demo.changeFileDirection()