#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdbool.h>
#include <string.h>


bool is_valid_length(string value)
{
    if (strlen(value) == 15 || strlen(value) == 16 || strlen(value) == 13)
    {
        return true;
    }
    return false;
}

bool passes_algo(string value)
{
    char str_copy[100] = "";

    strcpy(str_copy, value);

    int val1 = 0;
    int val2 = 0;

    if (strlen(value) == 16)
    {
        for (int i = 0; i < strlen(value); i = i + 1)
        {
            int new_num = str_copy[i] - '0';

            if (i % 2 == 0)
            {
                int val1b = (new_num * 2);
                if (val1b >= 10)
                {
                    val1 = val1 + (val1b / 10) + (val1b % 10);
                }
                else
                {
                    val1 = val1 + val1b;
                }
            }
            else
            {
                val2 = val2 + new_num;
            }
        }
    }
    else
    {
        for (int i = 0; i < strlen(value); i = i + 1)
        {
            int new_num = str_copy[i] - '0';

            if (i % 2 == 1)
            {
                int val1b = (new_num * 2);
                if (val1b >= 10)
                {
                    val1 = val1 + (val1b / 10) + (val1b % 10);
                }
                else
                {
                    val1 = val1 + val1b;
                }
            }
            else
            {
                val2 = val2 + new_num;
            }
        }
    }

    int final_val = val1 + val2;

    if (final_val % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string cc_type(string value)
{
    char str_copy[100] = "";
    strcpy(str_copy, value);

    int first_as_int = str_copy[0] - '0';

    char first_two[] = "";
    strncat(first_two, &str_copy[0], 1);
    strncat(first_two, &str_copy[1], 1);

    int first_two_i = atoi(first_two);

    // Check if the card is a VISA card
    if (str_copy[0] == '4' && (strlen(value) == 16 || strlen(value) == 13))
    {
        return "VISA\n";
    }
    // Check if the card is a MASTERCARD
    else if (strlen(value) == 16 && (first_two_i > 50 && first_two_i < 56))
    {
        return "MASTERCARD\n";
    }
    // Check if the card is an AMEX card
    else if (strlen(value) == 15 && (first_two_i == 34 || first_two_i == 37))
    {
        return "AMEX\n";
    }

    // If the card didn't pass the vibe checks, it's invalid
    return "INVALID\n";

}


int main(void)
{
    // Step 1a: Get number
    long long cc_number = get_long("Number: ");

    // Step 1b: Turn to string to do easier comparisons
    char cc_as_string[256];
    sprintf(cc_as_string, "%lld", cc_number);

    // Step 2: Check if number has the right amount of numbers (15 or 16)
    if (!is_valid_length(cc_as_string))
    {
        printf("INVALID\n");
    }
    else
    {
        // Step 3: Check if the numbers pass Luhns Algorithm
        if (!passes_algo(cc_as_string))
        {
            printf("INVALID\n");
        }
        else
        {
            printf("%s", cc_type(cc_as_string));
        }
    }
}