#include <stdio.h>
#include <malloc.h>

int *func(void){
    
    int (*data)[20];
    // printf("sizeof data: %d", sizeof(data));
    data = malloc(20 * sizeof(int));

    printf("%p\n",data);
    printf("%p\n",data + 1);

    printf("%p\n",*data);
    printf("%p\n",*data + 1);

    for(int i = 0 ; i < 20; ++i){
        *(*data + i) = 2 * i; 
    }
    printf("\n");
    return data;
}

int main(int argc, char const *argv[])
{
    int *data = func();

    for(int i = 0; i < 20; ++ i){
        printf("%d ", *(data + i) );
    }
    printf("\n");

    printf("%p\n",data);
    printf("%p\n",data + 1);

    printf("%d\n",*data);
    printf("%d\n",*data + 1);

    free(data);

    int a = 3, b = 1;
 
    // printf("%d\n",c);

    return 0;
}
