#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    char name[50] = "ggg";
    int sum = 0;
    int maximum_size = 79;
    for (int i = 0; i < 3; i++) {
        printf("%d\n", name[i]);
         sum += name[i];
    }
    printf("its %d", sum % maximum_size);
    

    return 0;
}
