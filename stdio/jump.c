#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;

void banana(){
    printf("In banana.\n");
    longjmp(buf, 1);
    printf("never see this!");
}

int main(int argc, char const *argv[])
{
    printf("In main\n");
    if(setjmp(buf)){
        printf("back in main\n");
        // banana();
    }else
    {
        printf("first jump\n");
        banana();
    }
    
    return 0;
}
