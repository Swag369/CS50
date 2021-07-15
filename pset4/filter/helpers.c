#include <stdio.h>
#include <math.h>
#include "helpers.h"

int islegit(int height, int width, int i, int j, int m, int n);
void findandadd(int height, int width, int i, int j, RGBTRIPLE image[height][width], RGBTRIPLE edges[height][width], int valx[3], int valy[3]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            float grey = (blue+green+red)/3.0;
            int intgrey = (blue+green+red)/3;
            if(grey-intgrey>=.5)
            {
                image[i][j].rgbtBlue=intgrey+1;
                image[i][j].rgbtGreen=intgrey+1;
                image[i][j].rgbtRed=intgrey+1;
            }
            else
            {
                image[i][j].rgbtBlue=intgrey;
                image[i][j].rgbtGreen=intgrey;
                image[i][j].rgbtRed=intgrey;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width/2; j++)
        {
            RGBTRIPLE temp = image[i][width-1-j];
            image[i][width-1-j]=image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for(int i =0; i < height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float count = 0;
            float red = 0;
            float blue = 0;
            float green = 0;
            for(int m = -1; m<=1; m++)
            {
                for(int n = -1; n<=1; n++)
                {
                    if(islegit(height, width, i, j, m, n)==0)
                    {
                        blue+=image[i+m][j+n].rgbtBlue;
                        red+=image[i+m][j+n].rgbtRed;
                        green+=image[i+m][j+n].rgbtGreen;
                        count++;
                    }
                }
            }
            if(blue/count-(int)(blue/count)>=.5)
            {
                blurred[i][j].rgbtBlue=blue/count+1;
            }
            else
            {
                blurred[i][j].rgbtBlue=blue/count;
            }
            if(green/count-(int)(green/count)>=.5)
            {
                blurred[i][j].rgbtGreen=green/count+1;
            }
            else
            {
                blurred[i][j].rgbtGreen=green/count;
            }
            if(red/count-(int)(red/count)>=.5)
            {
                blurred[i][j].rgbtRed=red/count+1;
            }
            else
            {
                blurred[i][j].rgbtRed=red/count;
            }
        }
    }
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            image[i][j]=blurred[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            int valx[] = {0, 0, 0};
            int valy[] = {0, 0, 0};
            findandadd(height, width, i, j, image, edges, valx, valy);
            float red = sqrt(valx[0]*valx[0]+valy[0]*valy[0]);
            float blue = sqrt(valx[1]*valx[1]+valy[1]*valy[1]);
            float green = sqrt(valx[2]*valx[2]+valy[2]*valy[2]);

            int redans = (int) red;
            int blueans = (int) blue;
            int greenans = (int) green;

            if(red - redans >=.5)
            {
                redans+=1;
            }
            if(blue - blueans >=.5)
            {
                blueans+=1;
            }
            if(green - greenans >=.5)
            {
                greenans+=1;
            }
            if(blueans >255)
            {
                blueans=255;
            }
            if(greenans >255)
            {
                greenans=255;
            }
            if(redans >255)
            {
                redans=255;
            }
            edges[i][j].rgbtRed=redans;
            edges[i][j].rgbtBlue=blueans;
            edges[i][j].rgbtGreen=greenans;
        }
    }

    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            image[i][j]=edges[i][j];
        }
    }
    return;
}

int islegit(int height, int width, int i, int j, int m, int n)
{
    if(j==0&&n==-1){return 1;}
    else if(j==width-1&&n==1){return 1;}
    else if(i==0&&m==-1){return 1;}
    else if(i==height-1&&m==1){return 1;}
    else{return 0;}
}

void findandadd(int height, int width, int i, int j, RGBTRIPLE image[height][width], RGBTRIPLE edges[height][width], int valx[3], int valy[3])
{

    for(int m = -1; m<=1; m++)
    {
        for(int n = -1; n<=1; n++)
        {
            if((j==0&&n==-1)
                || (j==width-1&&n==1)
                || (i==0&&m==-1)
                || (i==height-1&&m==1))
            {
                continue;
            }

            int Xkernel[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Ykernel[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            valx[0] += (image[i+m][j+n]).rgbtRed*Xkernel[m+1][n+1]; //finding the color values with the weights
            valy[0] += (image[i+m][j+n]).rgbtRed*Ykernel[m+1][n+1];
            valx[1] += (image[i+m][j+n]).rgbtBlue*Xkernel[m+1][n+1];
            valy[1] += (image[i+m][j+n]).rgbtBlue*Ykernel[m+1][n+1];
            valx[2] += (image[i+m][j+n]).rgbtGreen*Xkernel[m+1][n+1];
            valy[2] += (image[i+m][j+n]).rgbtGreen*Ykernel[m+1][n+1];
        }
    }
    return;
}