#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"

int main(int argc, char const *argv[])
{
    // 密匙
    uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                      0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
   
    // 加密对象
    uint8_t name[] = "dsfsdfsdfdsfasdsdsfsddfsdfdsdsf";
    printf("%s\n", name);

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    // 加密
    AES_ECB_encrypt(&ctx, name);
    printf("%s\n", name);

    // 解密
    AES_ECB_decrypt(&ctx, name);
    printf("%s\n", name);



    return 0;
}
