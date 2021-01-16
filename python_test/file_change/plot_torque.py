#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import sys

timeData = []
torqueData = []

def main(file):
    get_file_data(file)
    title = ['I1 Joint Torque', 'T2 Joint Torque', 'T3 Joint Torque', 'T4 Joint Torque', 'I5 Joint Torque']
    color = ['r','b','g','m','k']
    for i in range(len(title)):
        # plt.subplot(2, 3, (i + 1)) 
        plot_data(timeData, torqueData[i], title[i], color[i])
    plt.show()

def get_file_data(file):
    global timeData, torqueData
    with open(file ,'r') as file:

        temp_line = file.readline()
        while temp_line:
            temp_line = temp_line.replace('\n','')
            temp_lineData = temp_line.split(' ')
            # print temp_lineData
            timeData.append(float(temp_lineData[-1]))
            torqueData.append(temp_lineData[0:5])
            temp_line = file.readline()

        # print torqueData

        temp_data = torqueData
        torqueData = []
        for i in range(len(temp_data[0])):
            temp = []
            for j in range(len(temp_data)):
                temp.append(temp_data[j][i])
            torqueData.append(temp)

        temp_data = timeData
        timeData = []
        temp = 0
        for i in range(len(temp_data)):
            temp += temp_data[i]
            timeData.append(temp)

        # print timeData
        # print torqueData

def plot_data(x_data,y_data,label, color):

    label_font_size = {'family': 'Times New Roman',
         'weight': 'normal',
         'size': 15,
         }
    plt.xlabel("Time/s",label_font_size)
    plt.ylabel("Torque/mN.m",label_font_size)

    title_font_size = {'family': 'Times New Roman',
         'weight': 'normal',
         'size': 20,
         }
    plt.title(label, title_font_size)

    # plt.xlim(0,95)
    # plt.ylim(-300,300)
    plt.tick_params(labelsize=13)
    plt.plot(x_data, y_data, color, label=label)
    plt.legend(loc='best',ncol=3,fancybox=True,shadow=True)

if __name__ == "__main__":

    # file_torque = './horizon_muti_error/note_7.txt'
    file_torque = './temp_save.txt'


    main(file_torque)
    