#include <iostream>

struct IMAGE
{
    uint16_t magic;
    uint16_t version;
    uint8_t type;
    uint8_t size[3];
    uint8_t *data;
    uint8_t end[3];
} __attribute__((packed));;

bool verifyImage(char * image, unsigned int length)
{
    if(nullptr == image)
    {
        return false;
    }
    if

}

int main(int argc, char const *argv[])
{
    std::cout << sizeof(IMAGE) << std::endl;
    std::cout << sizeof(uint16_t) << std::endl;
    std::cout << sizeof(uint8_t*) << std::endl;

    return 0;
}
