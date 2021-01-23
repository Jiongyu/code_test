import os
import math

class ConvertCos(object):

    def __init__(self):
        self.__convert_angle = math.radians( 29.87 )
        self.__dir_file = os.listdir(os.getcwd())
        self.__convert_file = []
        self.__convert_index = 4
        pass

    def convert_pos(self):
        self.__get_convert_file()
        self.__get_convert_result()
        pass

    def __get_convert_file(self):
        for i in range(len(self.__dir_file)):
            if(os.path.isfile(self.__dir_file[i])):
                if(self.__dir_file[i].endswith('.txt')):
                    print(self.__dir_file[i])
                    self.__convert_file.append(self.__dir_file[i])
                    pass

    def __get_convert_result(self):

        for i in range(len(self.__convert_file)):
            temp_file_x = './data/' +  self.__convert_file[i].split('.')[0] + '_x.txt'
            temp_file_y = './data/' + self.__convert_file[i].split('.')[0] + '_y.txt'
            if (os.path.exists(temp_file_x) and os.path.exists(temp_file_y)):
                print(temp_file_x + ' ' + temp_file_y + ' already existed!')
            else:
                with open(self.__convert_file[i], 'r') as fr:
                    with open(temp_file_x, 'w') as fwx:
                        with open(temp_file_y, 'w') as fwy:
                            temp_line = fr.readline()
                            while(temp_line):
                                temp_line = temp_line.replace('\n', '')
                                temp_line = temp_line.split(' ')
                                for i in range(len(temp_line)):
                                    if(i == self.__convert_index):
                                        temp_consq = self.__get_projection(float(temp_line[i]))
                                        fwx.write(str(temp_consq[0]))
                                        fwy.write(str(temp_consq[1]))
                                    else:
                                        fwx.write(temp_line[i])
                                        fwy.write(temp_line[i])
                                    fwx.write(' ')
                                    fwy.write(' ')
                                fwx.write('\n')
                                fwy.write('\n')
                                temp_line = fr.readline()
                            pass

    def __get_projection(self, data):
        return (data * math.cos(self.__convert_angle), data * math.sin(self.__convert_angle))
        pass


if __name__ == '__main__':
    demo = ConvertCos()
    demo.convert_pos()