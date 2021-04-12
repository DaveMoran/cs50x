#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // int n = 50;
    // int *p = &n;
    // printf("%i\n", n);

    // // Check address
    // printf("%p\n", &n);

    // // Dereference
    // printf("%i\n", *&n);

    // // Declared pointer to int
    // printf("%p\n", p);

    // Call what's being held to pointer variable
    // printf("%i\n", *p);

    string s = "HI!";
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
}