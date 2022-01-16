#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "aes.h"

#define MAX_DATA_SIZE (1024)
#define MAGIC_LEN (8)
#define VERSION_LEN (8)
#define END_LEN (8)

#define ENCRYPT_LEN (16)
#define DNCRYPT_LEN (16)

// 密匙
extern uint8_t key[];

int Decrypt(char* buf, int size)
{
    struct AES_ctx ctx;
    char *p = buf;
    char decrypt[ENCRYPT_LEN];
    AES_init_ctx(&ctx, key);

    if(NULL == buf)
    {
        printf("buf is null\n");
    }

    while(size > 0)
    {
        AES_ECB_decrypt(&ctx, p);
        p += ENCRYPT_LEN;
        size -= ENCRYPT_LEN;
    }
}

int Encrypt(char* buf, int size)
{
    struct AES_ctx ctx;
    char *p = buf;
    char encrypt[ENCRYPT_LEN];

    AES_init_ctx(&ctx, key);

    if(NULL == buf)
    {
        printf("buf is null\n");
    }

    while(size > 0)
    {
        AES_ECB_encrypt(&ctx, p);
        p += ENCRYPT_LEN;
        size -= ENCRYPT_LEN;
    }
}
