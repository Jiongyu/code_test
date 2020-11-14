#include <stdio.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    char buf[2048];

    setbuf(stdout, buf);

    fprintf(stdout, "123221313132131233\n");
    fprintf(stdout, "asdassdsasadas\n");

    printf("%s\n", buf);    


    fprintf(stdout, "123221313132131233\n");
    fprintf(stdout, "asdassdsasadas\n");
    printf("%s\n", buf);

    

    return 0;
}
