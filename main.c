#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void aplicarEfeito(const char *efeito, const char *caminho, const char *destino);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s [grayscale|invert]\n", argv[0]);
        return 1;
    }

    DIR *pasta;
    struct dirent *entrada;

    pasta = opendir("../imagens/");
    if (pasta == NULL)
    {
        printf("Não foi possivel abrir pasta de imagens\n");
    }

    while ((entrada = readdir(pasta)) != NULL)
    {
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
        {
            continue;
        }

        char caminho[256];
        snprintf(caminho, sizeof(caminho), "../imagens/%s", entrada->d_name);

        char destino[256];
        if (strcmp(argv[1], "grayscale") == 0)
        {
            snprintf(destino, sizeof(destino), "../imagens_editadas/grayscale/%s", entrada->d_name);
        }
        else if (strcmp(argv[1], "invert") == 0)
        {
            snprintf(destino, sizeof(destino), "../imagens_editadas/invert/%s", entrada->d_name);
        }
        else
        {
            printf("Efeito desconhecido: %s\n", argv[1]);
            closedir(pasta);
            return 1;
        }

        aplicarEfeito(argv[1], caminho, destino);
    }

    return 0;
}

void aplicarEfeito(const char *efeito, const char *caminho, const char *destino)
{
    int largura, altura, canais;
    unsigned char *imagem = stbi_load(caminho, &largura, &altura, &canais, 0);

    if (imagem == NULL)
    {
        printf("Erro ao carregar a imagem %s\n", caminho);
        return;
    }

    printf("Processando imagem: %s\n", caminho);

    for (int i = 0; i < largura * altura * canais; i += canais)
    {
        unsigned char r = imagem[i];
        unsigned char g = imagem[i + 1];
        unsigned char b = imagem[i + 2];

        if (strcmp(efeito, "grayscale") == 0)
        {
            unsigned char gray = (r + g + b) / 3;
            imagem[i] = imagem[i + 1] = imagem[i + 2] = gray;
        }
        else if (strcmp(efeito, "invert") == 0)
        {
            imagem[i] = 255 - r;
            imagem[i + 1] = 255 - g;
            imagem[i + 2] = 255 - b;
        }
    }

    if (stbi_write_jpg(destino, largura, altura, canais, imagem, 100))
    {
        printf("Arquivo editado com sucesso: %s\n", destino);
    }
    else
    {
        printf("Erro ao salvar a imagem %s\n", destino);
    }

    stbi_image_free(imagem);
}
