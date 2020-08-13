#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float shade;
    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            // Get average of pixel colours
            shade = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtRed = round(shade);
            image[i][j].rgbtGreen = round(shade);
            image[i][j].rgbtBlue = round(shade);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            // Apply sepia coversion to pixels
            sepiaRed = rint(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = rint(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = rint(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Set values to max if out of range
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns until middle of image
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels with opposite position
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    
    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            float blurRed = 0;
            float blurGreen = 0;
            float blurBlue = 0;
            int pixelCount = 0;

            // Iterate through rows above and below current pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                // Iterate through columns to left and right of current pixel
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // Check if pixel within range
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        // Sum colour values
                        blurRed = blurRed + image[k][l].rgbtRed;
                        blurGreen = blurGreen + image[k][l].rgbtGreen;
                        blurBlue = blurBlue + image[k][l].rgbtBlue;
                        pixelCount++;
                    }
                }
            }
            // Get average for colour values and store in temp image
            tempImage[i][j].rgbtRed = round(blurRed / pixelCount);
            tempImage[i][j].rgbtGreen = round(blurGreen / pixelCount);
            tempImage[i][j].rgbtBlue = round(blurBlue / pixelCount);
        }
    }
    
    // Copy temp image back to main one
    
    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }
    return;
}
