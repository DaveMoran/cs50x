#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int numOfLetters(string text);
int numOfWords(string text);
int numOfSentences(string text);

// Implement your program in a file called readability.c in a directory called readability.
int main(void)
{
    // Your program must prompt the user for a string of text (using get_string).
    string text = get_string("Text: ");

    // Your program should count the number of letters, words, and sentences in the text.
    // You may assume that a letter is any lowercase character from a to z or any
    // uppercase character from A to Z, any sequence of characters separated by spaces
    // should count as a word, and that any occurrence of a period, exclamation point,
    // or question mark indicates the end of a sentence.

    int letters = numOfLetters(text);
    int words = numOfWords(text);
    int sentences = numOfSentences(text);

    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;

    // printf(" 0.0588 * %f - 0.296 * %f - 15.8", L, S);

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = (int) round(index);


    // If the index number is less than 1, your program should output "Before Grade 1".
    if (grade < 0)
    {
        printf("Before Grade 1\n");
    }
    // If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number.
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    // Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
    else
    {
        printf("Grade %i\n", grade);
    }





}

int numOfLetters(string text)
{
    int textLength = strlen(text);
    int letters = 0;
    for (int i = 0; i < textLength; i++)
    {
        int charCode = (int) text[i];
        if (charCode > 64 && charCode < 91)
        {
            letters++;
        }
        if (charCode > 96 && charCode < 125)
        {
            letters++;
        }
    }

    return letters;
}


int numOfWords(string text)
{
    int textLength = strlen(text);
    int words = 1;
    for (int i = 0; i < textLength; i++)
    {
        int charCode = (int) text[i];
        if (charCode == 32)
        {
            words++;
        }
    }

    return words;
}


int numOfSentences(string text)
{
    int textLength = strlen(text);
    int sentences = 0;
    for (int i = 0; i < textLength; i++)
    {
        int charCode = (int) text[i];
        if (charCode == 46 || charCode == 33 || charCode == 63)
        {
            sentences++;
        }
    }

    return sentences;
}


