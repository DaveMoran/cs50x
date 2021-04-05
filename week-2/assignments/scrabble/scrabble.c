#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players, make them lowercase
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    printf("%i, %i\n", score1, score2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int wordLength = strlen(word);
    int score = 0;
    for (int i = 0; i < wordLength; i++)
    {
        int charCode = (int) word[i];
        if (charCode > 64 && charCode < 91)
        {
            score = score + POINTS[charCode - 65];
        }
        if (charCode > 96 && charCode < 125)
        {
            score = score + POINTS[charCode - 97];
        }
    }

    return score;
}
