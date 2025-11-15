#include "helpers.h"
#include <math.h>

int calred_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width]);
int calgreen_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width]);
int calblue_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //find average all red green and blue
            int colour_average = round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue / 3.0);
            
            image[i][j].rgbtRed = colour_average;
            image[i][j].rgbtGreen = colour_average;
            image[i][j].rgbtBlue = colour_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

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
    RGBTRIPLE temp;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
        
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    RGBTRIPLE image_copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int Red_average = calred_average(i, j, height, width, image_copy);
            int Green_average = calgreen_average(i, j, height, width, image_copy);
            int Blue_average = calblue_average(i, j, height, width, image_copy);

            image[i][j].rgbtRed = Red_average;
            image[i][j].rgbtGreen = Green_average;
            image[i][j].rgbtBlue = Blue_average;
        }
    }
}


int calred_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width])
{
    int Red_sum = 0;
    float valid_pixels = 0;
    for(int h = -1; h < 2; h++)
    {
        if(i + h < 0 || i + h > height - 1)
        {
            continue;
        }
        for(int w = -1; w < 2; w++)
        {
            if(i + w < 0 || i + w > width - 1)
            {
                continue;
            }
            Red_sum += image_copy[i + h][j + w].rgbtRed;
            valid_pixels++;
        }
    }
    int Red_average = round(Red_sum / valid_pixels);
    return Red_average;
}

int calgreen_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width])
{
    int Green_sum = 0;
    float valid_pixels = 0;
    for(int h = -1; h < 2; h++)
    {
        if(i + h < 0 || i + h > height - 1)
        {
            continue;
        }
        for(int w = -1; w < 2; w++)
        {
            if(i + w < 0 || i + w > width - 1)
            {
                continue;
            }
            Green_sum += image_copy[i + h][j + w].rgbtGreen;
            valid_pixels++;
        }
    }
    int Green_average = round(Green_sum / valid_pixels);
    return Green_average;
}

int calblue_average(int i, int j, int height, int width, RGBTRIPLE image_copy[height][width])
{
    int Blue_sum = 0;
    float valid_pixels = 0;
    for(int h = -1; h < 2; h++)
    {
        if(i + h < 0 || i + h > height - 1)
        {
            continue;
        }
        for(int w = -1; w < 2; w++)
        {
            if(i + w < 0 || i + w > width - 1)
            {
                continue;
            }
            Blue_sum += image_copy[i + h][j + w].rgbtBlue;  
            valid_pixels++;
        }
    }
    int Blue_average = round(Blue_sum / valid_pixels);
    return Blue_average; 
}