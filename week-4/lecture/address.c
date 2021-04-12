#include <stdio.h>

int main(void)
{
    int n = 50;
    printf("%i\n", n);

    // Check address
    printf("%p\n", &n);

    // Dereference
    printf("%i\n", *&n);
}