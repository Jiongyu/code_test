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

extern int Decrypt(char* buf, int size);

struct image
{
    char magic[MAGIC_LEN];
    char version[VERSION_LEN];
    uint16_t type;
    uint16_t size;
    char *data;
    char end[END_LEN];
} __attribute__((packed));

typedef struct image iamge_t;

// 密匙
uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                    0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };

int main(int argc, char const *argv[])
{
    int ret = 0;
    FILE *fp = NULL;
    iamge_t test;
    char decrypt[ENCRYPT_LEN];
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    fp = fopen("./test.txt", "rb");
    ret = fread(&test.magic, MAGIC_LEN * sizeof(char), 1, fp);
    if(strcmp(test.magic, "1234"))
    {
        printf("magic error [read magic:%s]\n", test.magic);
        goto exit;
    }

    ret = fread(&test.version, VERSION_LEN * sizeof(char), 1, fp);
    if(strcmp(test.version, "102D"))
    {
        printf("version error [read version:%s]\n", test.version);
        goto exit;
    }

    ret = fread(&test.type, sizeof(uint16_t), 1, fp);
    if(5 != test.type)
    {
        printf("type error [read type:%d]\n", test.type);
        goto exit;
    }

    ret = fread(&test.size, sizeof(uint16_t), 1, fp);
    test.data = (char *)malloc(sizeof(char) * (test.size));
    if(NULL == test.data)
    {
        printf("malloc error!\n");
        goto exit;
    }

#if 0
    //ret = fread(test.data, sizeof(char) * test.size, 1, fp);
    int remain_len = test.size;
    char *p = test.data;
    while(remain_len > 0)
    {
        
        if(remain_len >= ENCRYPT_LEN)
        {
            fread(decrypt, ENCRYPT_LEN, 1, fp);
            AES_ECB_decrypt(&ctx, decrypt);
            memcpy(p, decrypt, ENCRYPT_LEN);
            p += ENCRYPT_LEN;
        }
        else
        {
            fread(decrypt, ENCRYPT_LEN, 1, fp);
            AES_ECB_decrypt(&ctx, decrypt);
            memcpy(p, decrypt, remain_len);
        }
        remain_len -= ENCRYPT_LEN;
    }
#else
    fread(test.data, test.size, 1, fp);
    Decrypt(test.data, test.size);
#endif

    ret = fread(&test.end, END_LEN * sizeof(char), 1, fp);
    if(strcmp(test.end, "0xefef"))
    {
        printf("end error [read end:%s]\n", test.end);
        free(test.data);
        goto exit;
    }

    printf("read data:[%s]\n", test.data);

    free(test.data);

exit:
    fclose(fp);
    return 0;
}
