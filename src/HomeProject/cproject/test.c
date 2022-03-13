#include <stdio.h>

#include "sum.h"

int testEq(int test, int expTest)
{
    return (test == expTest) ? 0 : -1;
}


int main()
{
    int rc = testEq(sum(5, 9), 14);
    rc |= testEq(sum(3, 6), 9);
    rc |= testEq(sum(4, 65), 69);
    rc |= testEq(sum(6, 23), 29);
    printf("Test rc=%d\n", rc);
    return rc;
}
