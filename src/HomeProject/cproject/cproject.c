#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    uint8_t arrayTmp[] = {1, 2, 4, 4};

    uint32_t* atPtr = (uint32_t*) arrayTmp;
    printf("Value for var is: %x\n", *atPtr);
}
