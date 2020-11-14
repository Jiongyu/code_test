#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;

    fp = fopen("file.txt", "w");
    int index  = 5;
    while(index > 0){
        fprintf(fp, "%s", "runoob.com\n");
        index --;
    }
    fclose(fp);

    // system("rm ./file.txt");

    fp = fopen("file.txt", "r");
    if(fp == NULL){
        perror("file not exist : ");
        exit(-1);
    }
    char c;
    char str[10];
    
    // fseek(fp, 10, SEEK_SET);
    do
    {
        // c = fgetc(fp);
        // printf("%c", c);
        fread(str, sizeof(str), sizeof(str[0]), fp);
        printf("%s\n", str);
    } while (! feof(fp));
   fclose(fp);


   char buff[1024];
 
   memset( buff, '\0', sizeof( buff ));
 
   fprintf(stdout, "启用全缓冲\n");
   setvbuf(stdout, buff, _IOFBF, 1024);
 
   fprintf(stdout, "这里是 runoob.com\n");
   fprintf(stdout, "该输出将保存到 buff\n");
   fflush( stdout );
 
   fprintf(stdout, "这将在编程时出现\n");
   fprintf(stdout, "最后休眠五秒钟\n");
 
   sleep(5);
   return(0);
}