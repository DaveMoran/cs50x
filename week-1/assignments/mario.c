#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // Step 1: Get height
    int height = get_int("Height:");

    // Step 2: Make sure height is in valid range
    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }

    char p[125] = "";
    int i;
    int x;
    int y;
    // Step 3: Begin printing out pyramid
    for (i = 1; i <= height; i = i + 1)
    {
        // First loop, print out space, then hash
        for (x = 0; x < height; x = x + 1)
        {
            if (height - x > i)
            {
                strcat(p, " ");
            }
            else
            {
                strcat(p, "#");
            }
        }

        // Add gutter
        strcat(p, "  ");

        // Second loop, add hashes, then new line
        for (y = 0; y < height; y = y + 1)
        {
            if (i > y)
            {
                strcat(p, "#");
            }
        }
        strcat(p, "\n");
    }

    printf("%s", p);
}