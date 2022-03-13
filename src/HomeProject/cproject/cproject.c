#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sum.h"

int main()
{
    const int rc = sum(4, 5);
    return (9 == rc) ? 0 : -1;
}
