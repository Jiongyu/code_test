#include <stdio.h>


void print_int_data(int (*data)[2], int row){
    int col = 2;
    for(int i = 0; i < row; ++ i){
        for(int j = 0; j < col; ++ j){
            printf("%d, ", data[i][j]);
        }
        printf("\n");
    }
}

void print_char_data(char (*data)[10], int row){
    int col = 10;
    for(int i = 0; i < row; ++i){
        printf("%s\n", data[i]);
    }
}

void print_char_data_1(char **data, int row){
    for(int i = 0; i < row; ++ i){
        printf("%s\n", *data);
        *data ++;
    }
}



int main(int argc, char const *argv[])
{
    int data[3][2] = {
        {1,2},
        {2,3},
        {4,5},
    };

    int row = 3;
    int *intP = data;

    print_int_data(data, row);

    char charData[3][10] = {
        "Adadsad",
        "Asdasfd",
        "asdsa",
    };
    int charRow = 3;
    print_char_data(charData, charRow);


    char *charData_1[10] = {
        "asdasd",
        "adas",
        "asdasd",
    };

    char **charP = charData_1;
    printf("%s\n", *charP);
    printf("%s\n", charData_1[0]);
    printf("%s\n", *charData_1);
    printf("%s\n\n", *(charData_1 + 1));

    print_char_data_1(charP, charRow);


    return 0;
}
