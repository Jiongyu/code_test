#include <stdio.h>


int main(int argc, char const *argv[])
{
    FILE *fp = fopen("temp.txt", "w");
    fputs("\nhello data", fp);

    char data[] = "hello data!\n";
    // fwrite((char *)&data, sizeof(data), 1, fp);
    fprintf(fp, "%s", data);
    fprintf(stdout, "%s", data);

    // fseek(fp, - (long) sizeof(data), 1);
    fseek(fp, 0, SEEK_END);

    // fwrite("data", sizeof("data--------"), 1, fp);
    fprintf(fp, "%s", "data--------");
    fprintf(stdout, "%s", "data--------");

    fputs("\nhello data", fp);
    char readData[100];
    rewind(fp);
    fscanf(fp, "%s", readData);
    printf("%s\n", readData);
    fclose(fp);
    
    return 0;
}
