#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
      // Cria uma cópia da imagem original para usar como referência
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Aplica o efeito de desfoque
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Inicializa as variáveis para calcular a média dos valores RGB
            int red = 0, green = 0, blue = 0;
            int count = 0;

            // Percorre a vizinhança de 3x3 ao redor do pixel atual
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Verifica se o pixel vizinho está dentro dos limites da imagem
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Soma os valores RGB dos pixels vizinhos
                        red += copy[ni][nj].rgbtRed;
                        green += copy[ni][nj].rgbtGreen;
                        blue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcula a média dos valores RGB
            image[i][j].rgbtRed = round((float)red / count);
            image[i][j].rgbtGreen = round((float)green / count);
            image[i][j].rgbtBlue = round((float)blue / count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

           float Gx_red = 0, Gy_red = 0, Gx_green = 0, Gy_green = 0, Gx_blue = 0, Gy_blue = 0;

            for(int di = -1; di <= 1; di++){

                for (int dj = -1; dj <= 1; dj++){
                    int ni = i + di;
                    int nj = i + dj;


                    if(ni >= 0 && ni < height && nj >= 0 && nj < width){

                        Gx_red += Gx[di + 1][dj + 1] * copy[ni][nj].rgbtRed;
                        Gy_red += Gy[di + 1][dj + 1] * copy[ni][nj].rgbtRed;
                        Gx_green += Gx[di + 1][dj + 1] * copy[ni][nj].rgbtGreen;
                        Gy_green += Gy[di + 1][dj + 1] * copy[ni][nj].rgbtGreen;
                        Gx_blue += Gx[di + 1][dj + 1] * copy[ni][nj].rgbtBlue;
                        Gy_blue += Gy[di + 1][dj + 1] * copy[ni][nj].rgbtBlue;
                    }
                }
            }

            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            red = red > 255 ? 255 : red;
            green = green > 255 ? 255 : green;
            blue = blue > 255 ? 255 : blue;

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }

    return;
}
