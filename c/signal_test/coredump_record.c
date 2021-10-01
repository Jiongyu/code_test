/**
 * @file coredump_record.c
 * @author your name (you@domain.com)
 * @brief 当段错误发生时，操作系统会发送一个
    SIGSEGV信号给进程，导致进程产生核心转储文件并且退出。进程先
    捕捉SIGSEGV信号，打印出有用的方便定位问题的信息，然后再优雅地退出.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// gcc -o coredump_record coredump_record.c -rdynamic
// -rdynamic 打印函数地址

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <unistd.h>

typedef struct _sig_ucontext {
    unsigned long uc_flags;
    struct ucontext *uc_link;
    stack_t uc_stack;
    struct sigcontext uc_mcontext;
    sigset_t uc_sigmask;
} sig_ucontext_t;

// ucontext 进程上下文信息
void crit_err_hdlr(int sig_num, siginfo_t * info, void * ucontext)
    {
    void * array[50];
    void * caller_address;
    char ** messages;
    int size, i;
    sig_ucontext_t * uc;

    uc = (sig_ucontext_t *)ucontext;
    caller_address = (void *) uc->uc_mcontext.rip;

    fprintf(stderr, "signal %d (%s), address is %p from %p\n",
        sig_num, strsignal(sig_num), info->si_addr,
        (void *)caller_address);

    size = backtrace(array, 50);
    array[1] = caller_address;
    messages = backtrace_symbols(array, size);
    /* 跳过第一个栈帧
    */
    for (i = 1; i < size && messages != NULL; ++i)
    {
        fprintf(stderr, "[bt]: (%d) %s\n", i, messages[i]);
    }

    free(messages);
    exit(EXIT_FAILURE);
}

int crash()
{
    char * p = NULL;
    *p = 0;
    return 0;
} 

int foo4()
{
    crash();
    return 0;
} 

int foo3()
{
    foo4();
    return 0;
}
int foo2()
{
    foo3();
    return 0;
}

int foo1()
{
    foo2();
    return 0;
} 

int main(int argc, char ** argv)
{
    struct sigaction sigact;
    sigact.sa_sigaction = crit_err_hdlr;
    sigact.sa_flags = SA_RESTART | SA_SIGINFO;

    if (sigaction(SIGSEGV, &sigact, (struct sigaction *)NULL) != 0)
    {
        fprintf(stderr, "error setting signal handler for %d (%s)\n",
        SIGSEGV, strsignal(SIGSEGV));
        exit(EXIT_FAILURE);
    }

    foo1();
    exit(EXIT_SUCCESS);
}