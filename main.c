#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>


#pragma pack(1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;


int aplicarGrayscale();
int aplicarInvert();


int main (int argc, char *argv[]) 
{
    if (argc < 2)
    {
        printf("Uso: %s [grayscale|invert]\n");
        return 1;
    }

    DIR *pasta;
    struct dirent *entrada;
    struct stat info;

    pasta = opendir("../imagens");

    if (pasta == NULL)
    {
        puts("Não foi possivel encontrar o diretório");
        return 1;
    }

    while ((entrada = readdir(pasta)) != NULL)
    {
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
        {
            continue;
        }

        char caminho[256];

        strcpy(caminho, "../imagens/");
        strcat(caminho, entrada->d_name);

        if (stat(caminho, &info) == 0)
        {
            if (strcmp(argv[1], "grayscale") == 0)
            {

            }
            else if (strcmp(argv[1], "invert") == 0)
            {

            }
            else
            {
                printf("Opção desconhecida: %s\n", argv[1]);
                return 1;
            }
        }
    }

    closedir(pasta);
    return 0;
}