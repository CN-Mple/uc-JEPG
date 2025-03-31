#include "bitmap.h"

struct true_color_with_alpha{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

void save_by_bitmap(char* file_name, unsigned char *src, int width, int height)
{

    FILE* file = fopen(file_name, "wb");

    struct true_color_with_alpha gray_lut[256];

    for (int i = 0; i < 256; i++)
        gray_lut[i] = (struct true_color_with_alpha){(unsigned char)i,(unsigned char)i,(unsigned char)i,(unsigned char)0xFF};


    unsigned char head[54] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 ,\
                        40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32};
    *(int*)(head + 2) = 54 + 4 * width * height;
    *(int*)(head + 18) = width;
    *(int*)(head + 22) = height;
    *(int*)(head + 42) = height * width * 4;
    fwrite(head, 1, 54, file);


    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            unsigned char index = src[x * width + y];
            fwrite(gray_lut + index, 4, 1, file);
        }
    }
    fclose(file);
}
