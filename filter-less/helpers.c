#include "helpers.h"
#include <stdio.h>

// Helper function to ensure that a color value is capped at 255
int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the rounded average of red, green, and blue values
            int average = (int)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 + 0.5);

            // Set each color channel to the rounded average value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate new color values using sepia formula and round to the nearest integer
            int sepiaRed = cap((int)(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue + 0.5));
            int sepiaGreen = cap((int)(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue + 0.5));
            int sepiaBlue = cap((int)(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue + 0.5));

            // Set the color channels to the new sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels from the left and right sides
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate through pixels
            for (int ni = -1; ni <= 1; ni++)
            {
                for (int nj = -1; nj <= 1; nj++)
                {
                    int newI = i + ni;
                    int newJ = j + nj;

                    // Check if the neighboring pixel is within bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        sumRed += image[newI][newJ].rgbtRed;
                        sumGreen += image[newI][newJ].rgbtGreen;
                        sumBlue += image[newI][newJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average values for the neighboring pixels and round to the nearest integer
            temp[i][j].rgbtRed = (int)((float)sumRed / count + 0.5);
            temp[i][j].rgbtGreen = (int)((float)sumGreen / count + 0.5);
            temp[i][j].rgbtBlue = (int)((float)sumBlue / count + 0.5);
        }
    }

    // Copy the blurred image back to the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
