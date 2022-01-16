#include <stdio.h>
#include <pthread.h> 

int g_data = 0;

 void thread1_func(void *args)
 {
    int i = 0;
    int j = 1;
    unsigned int ii = 0x11111111;
    unsigned int jj = 0x22222222;

     while(i < 2)
     {
         i++;
         g_data += i;
     }
 }

 int main()
{
    int i;
    int flag = 1;

    printf("wait gdb\n");
    while(1 == flag);
    printf("jump wait gdb\n");


    for(i = 1; i <= 100; i ++)
    {
        g_data += i;
    }
    printf("g_data[1-100] = %d \n", g_data );

	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, (void*)thread1_func, NULL);
    pthread_join(t1, NULL);
    return 0;
}