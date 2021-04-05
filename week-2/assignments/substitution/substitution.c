#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Implement your program in a file called substitution.c in a directory called substitution.
string encodeString(string text, string cypher);

int main(int argv, string argc[])
{

    // Your program must accept a single command-line argument, the key to use for the substitution.
    // The key itself should be case-insensitive, so whether any character in the key is uppercase
    // or lowercase should not affect the behavior of your program.
    string key = argc[1];

    // If your program is executed without any command-line arguments or with more than one command-line
    // argument, your program should print an error message of your choice (with printf) and return from
    // main a value of 1 (which tends to signify an error) immediately.
    if (argv == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If the key is invalid (as by not containing 26 characters, containing any character that is not an
    // alphabetic character, or not containing each letter exactly once), your program should print an
    // error message of your choice (with printf) and return from main a value of 1 immediately.
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        int charCode = (int) argc[1][i];

        if (charCode < 65 || charCode > 122 || (charCode > 90 && charCode < 97))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    for (int x = 0; x < 26; x++)
    {
        char firstChar = argc[1][x];


        for (int y = x + 1; y < 26; y++)
        {
            char secondChar = argc[1][y];
            // printf("%c = %c\n", firstChar, secondChar);
            if (firstChar == secondChar)
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }

    // Your program must output plaintext: (without a newline) and then prompt the user for a
    // string of plaintext (using get_string).
    string text = get_string("plaintext: ");

    // Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
    printf("ciphertext: %s\n", encodeString(text, argc[1]));

    // Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
    // After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
    return 0;
}

string encodeString(string text, string cipher)
{
    string encodedText = text;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        int charCode = (int) text[i];
        if (charCode > 64 && charCode < 91)
        {
            int alphaPos = charCode - 65;
            text[i] = toupper(cipher[alphaPos]);
        }
        if (charCode > 96 && charCode < 123)
        {
            int alphaPos = charCode - 97;
            text[i] = tolower(cipher[alphaPos]);
        }
    }
    return encodedText;
}
