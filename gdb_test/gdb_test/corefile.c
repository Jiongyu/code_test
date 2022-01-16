	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
    #include <pthread.h>
	
	void mem_leak1(void *arg )
	{
        printf("mem_leak1\n");
	    char *p = malloc(1);
	}
	
	void mem_leak2(void *arg )
	{
        printf("mem_leak2\n");
	    FILE *p = fopen("test.txt", "w+");
	}
	
	void mem_overrun1(void *arg )
	{
        printf("mem_overrun1\n");
	    char *p = malloc(1);
	    *(short*)p = 2;
	    free(p);
	}
	
	void mem_overrun2(void *arg )
	{
        printf("mem_overrun2\n");
	    char arr[5];
	    strcpy(arr, "hellosadasdasd");
	}
	
	void mem_double_free(void *arg )
	{
        printf("mem_double_free\n");
	    char *p = malloc(1);
	    free(p);
	    free(p);
	}
	
	void mem_free_wild_pointer(void *arg )
	{
        printf("mem_free_wild_pointer\n");
	    char *p;
	    free(p);
	}
	
	int main(int argc, char const *argv[])
	{

        pthread_t th1, th2, th3, th4, th5;  
        int ret;  
        int arg = 10;  
        int *thread_ret = NULL;  
        ret = pthread_create( &th1, NULL, mem_leak1, &arg);  
        if( ret != 0 ){  
            printf( "Create thread error!\n");  
            return -1;  
        }
        
        ret = pthread_create( &th2, NULL, mem_leak2, &arg);  
        if( ret != 0 ){  
            printf( "Create thread error!\n");  
            return -1;  
        } 

        ret = pthread_create( &th3, NULL, mem_overrun1, &arg);  
        if( ret != 0 ){  
            printf( "Create thread error!\n");  
            return -1;  
        } 

        ret = pthread_create( &th4, NULL, mem_overrun2, &arg);  
        if( ret != 0 ){  
            printf( "Create thread error!\n");  
            return -1;  
        } 
        
        ret = pthread_create( &th5, NULL, mem_free_wild_pointer, &arg);  
        if( ret != 0 ){  
            printf( "Create thread error!\n");  
            return -1;  
        } 

        pthread_join( th1, (void**)&thread_ret );
        pthread_join( th2, (void**)&thread_ret );
        pthread_join( th3, (void**)&thread_ret );
        pthread_join( th4, (void**)&thread_ret );
        pthread_join( th5, (void**)&thread_ret );

        return 0;
	}
