#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes.h"

#define MAX_DATA_SIZE (1024)
#define MAGIC_LEN (8)
#define VERSION_LEN (8)
#define END_LEN (8)

#define ENCRYPT_LEN (16)
#define DNCRYPT_LEN (16)

extern int Encrypt(char* buf, int size);

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
    FILE *fp = NULL;
    iamge_t test;
    char magic[MAGIC_LEN] = "1234";
    memcpy(&(test.magic), magic, sizeof(magic));
    char version[VERSION_LEN] = "102D";
    memcpy(&(test.version), version, sizeof(version));
    test.type = 5;
    char data[MAX_DATA_SIZE] = "asdasdasfdsgdfgfasdasdsadasd哈哈哈哈哈哈哈哈是dgfdgfdgghjhgjgr45546567dfhdfgfdgxcvxcsdfsd";
    printf("write data: [%s]\n", data);

    char encrypt[ENCRYPT_LEN];
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);


    test.data = data;
    test.size = strlen(data);
    if(test.size % ENCRYPT_LEN != 0)
    {
        test.size += (ENCRYPT_LEN - test.size % ENCRYPT_LEN);
    }

    char end[END_LEN] = "0xefef";
    memcpy(&(test.end), end, sizeof(end));

    fp = fopen("./test.txt", "wb");
    fwrite(&(test.magic), MAGIC_LEN * sizeof(char), 1, fp);
    fwrite(&(test.version), VERSION_LEN * sizeof(char), 1, fp);
    fwrite(&(test.type), sizeof(uint16_t), 1, fp);
    fwrite(&(test.size), sizeof(uint16_t), 1, fp);

#if 0
    int total_len = strlen(data);
    int remain_len = total_len;
    char *p = test.data;
    while(remain_len > 0)
    {
        
        if(remain_len >= ENCRYPT_LEN)
        {
            memcpy(encrypt, p, ENCRYPT_LEN);
            p += ENCRYPT_LEN;
            AES_ECB_encrypt(&ctx, encrypt);
            fwrite(encrypt, ENCRYPT_LEN, 1, fp);
        }
        else
        {
            memset(encrypt, 0, ENCRYPT_LEN);
            memcpy(encrypt, p, remain_len);
            p += remain_len;
            AES_ECB_encrypt(&ctx, encrypt);
            fwrite(encrypt, ENCRYPT_LEN, 1, fp);
        }
        remain_len -= ENCRYPT_LEN;
    }
#else
    Encrypt(test.data, test.size);
    fwrite(test.data, test.size, 1, fp);
#endif

    fwrite(&(test.end), END_LEN * sizeof(char), 1, fp);
    fclose(fp);
    return 0;
}
