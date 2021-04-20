#include "helpers.h"
#include "math.h"

int getSepiaRed(int red, int green, int blue);
int getSepiaGreen(int red, int green, int blue);
int getSepiaBlue(int red, int green, int blue);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the width and height of img
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grab RGB values
            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalRed = image[i][j].rgbtRed;

            // Get the avg
            BYTE avg = round((originalBlue + originalGreen + originalRed) / 3.0);

            // Overwrite the existing values with the avg
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the width and height of img
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grab RGB values
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Generate new values
            BYTE sepiaRed =     getSepiaRed(originalRed, originalGreen, originalBlue);
            BYTE sepiaGreen =   getSepiaGreen(originalRed, originalGreen, originalBlue);
            BYTE sepiaBlue =    getSepiaBlue(originalRed, originalGreen, originalBlue);;

            // Overwrite the existing values with the avg
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the width and height of img
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE arrayRow[width];
        for (int j = 0; j < width; j++)
        {
            // Grab RGB values
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Reverse fill the array
            arrayRow[width - j - 1].rgbtRed = originalRed;
            arrayRow[width - j - 1].rgbtGreen = originalGreen;
            arrayRow[width - j - 1].rgbtBlue = originalBlue;
        }

        // Loop through new array and replace values in image
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = arrayRow[k].rgbtRed;
            image[i][k].rgbtGreen = arrayRow[k].rgbtGreen;
            image[i][k].rgbtBlue = arrayRow[k].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageNew[width][height];

    // Loop through the width and height of img
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE box[9];
            int counter = 0;

            // Get first three pixels
            if (i != 0)
            {
                // Top left
                if (j != 0)
                {
                    box[counter] = image[i - 1][j - 1];
                    counter++;
                }

                box[counter] = image[i - 1][j];
                counter++;

                // Top right
                if (j + 1 < width)
                {
                    box[counter] = image[i - 1][j + 1];
                    counter++;
                }
            }

            // Get current row of pixels
            // Mid left
            if (j != 0)
            {
                box[counter] = image[i][j - 1];
                counter++;
            }

            box[counter] = image[i][j];
            counter++;

            // Mid right
            if (j + 1 < width)
            {
                box[counter] = image[i][j + 1];
                counter++;
            }

            // Get last three pixels
            if (i + 1 < height)
            {
                // Bottom left
                if (j != 0)
                {
                    box[counter] = image[i + 1][j - 1];
                    counter++;
                }

                box[counter] = image[i + 1][j];
                counter++;

                // Top right
                if (j + 1 < width)
                {
                    box[counter] = image[i + 1][j + 1];
                    counter++;
                }
            }

            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            for (int k = 0; k < counter; k++)
            {
                sumRed += box[k].rgbtRed;
                sumGreen += box[k].rgbtGreen;
                sumBlue += box[k].rgbtBlue;
            }

            // Add new values to separate RGBTRIPLE
            imageNew[i][j].rgbtRed = round((double)sumRed / counter);
            imageNew[i][j].rgbtGreen = round((double)sumGreen / counter);
            imageNew[i][j].rgbtBlue = round((double)sumBlue / counter);
        }
    }

    // Second loop to add new values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imageNew[i][j].rgbtRed;
            image[i][j].rgbtGreen = imageNew[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imageNew[i][j].rgbtBlue;
        }
    }

    return;
}

// Helper function for sepiaRed
int getSepiaRed(int red, int green, int blue)
{
    double r1 = .393 * red;
    double r2 = .769 * green;
    double r3 = .189 * blue;

    int sepiaRed = round(r1 + r2 + r3);

    if (sepiaRed > 255)
    {
        sepiaRed = 255;
    }

    return sepiaRed;
}

// Helper function for sepiaGreen
int getSepiaGreen(int red, int green, int blue)
{
    double r1 = .349 * red;
    double r2 = .686 * green;
    double r3 = .168 * blue;

    int sepiaGreen = round(r1 + r2 + r3);

    if (sepiaGreen > 255)
    {
        sepiaGreen = 255;
    }

    return sepiaGreen;
}

// Helper function for sepiaBlue
int getSepiaBlue(int red, int green, int blue)
{
    double r1 = .272 * red;
    double r2 = .534 * green;
    double r3 = .131 * blue;

    int sepiaBlue = round(r1 + r2 + r3);

    if (sepiaBlue > 255)
    {
        sepiaBlue = 255;
    }

    return sepiaBlue;
}