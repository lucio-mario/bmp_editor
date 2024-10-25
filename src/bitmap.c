#include "common.h"

void init_bmp_file(bmp_file_t *const ram_file, uint32_t width, uint32_t height)
{
    IFDEBUG("init_bmp_file()");
    uint8_t red, green, blue;
    ram_file->bmp_pd.padding_size = (width * 3) % 4;

    ram_file->bmp_s.file_type[0] = 'B';
    ram_file->bmp_s.file_type[1] = 'M';

    ram_file->bmp_fh.file_size = (width * 3 + ram_file->bmp_pd.padding_size) * height + 54;
    ram_file->bmp_fh.reserved = 0;
    ram_file->bmp_fh.off_bits = 54;

    ram_file->bmp_ih.header_size = 40;
    ram_file->bmp_ih.width = width;
    ram_file->bmp_ih.height = height;
    ram_file->bmp_ih.planes = 1;
    ram_file->bmp_ih.bpp = 24;
    ram_file->bmp_ih.compression = 0;
    ram_file->bmp_ih.image_size = 0;
    ram_file->bmp_ih.xppm = 0;
    ram_file->bmp_ih.yppm = 0;
    ram_file->bmp_ih.clr_used = 0;
    ram_file->bmp_ih.clr_important = 0;
  
    ram_file->bmp_pd.pixels = (pixel_t**)malloc(sizeof(pixel_t*) * height);
    for(register uint32_t i = 0; i < height; ++i)
        ram_file->bmp_pd.pixels[i] = (pixel_t*)malloc(sizeof(pixel_t) * width);
    ram_file->bmp_pd.padding = malloc(sizeof(uint8_t) * ram_file->bmp_pd.padding_size);

    for(register uint32_t y = 0; y < height; ++y)
    {
        for(register uint32_t x = 0; x < width; ++x)
        {
            red = 255 * x / width;
            blue = 255 * y / height;
            green = 255 * x * y / (height * width);

            if(x < width * 0.8 && x > width * 0.2)
                if(y < height * 0.6 && y > height * 0.4)
                {
                    red = 255 * y / height;
                    blue = 255 * x / width;
                }

            ram_file->bmp_pd.pixels[y][x].red = red;
            ram_file->bmp_pd.pixels[y][x].green = green;
            ram_file->bmp_pd.pixels[y][x].blue = blue;
        }
        if(ram_file->bmp_pd.padding_size)
            for(register uint8_t i = 0; i < ram_file->bmp_pd.padding_size; ++i)
                ram_file->bmp_pd.padding[i] = (uint8_t)0;
    }
}

//verify if file exists
void get_bmp_file(bmp_file_t *const ram_file, const char *hdd_file_name)
{
    IFDEBUG("get_bmp_file()");
    FILE *hdd_file = fopen(hdd_file_name, "rb");

    fread(&ram_file->bmp_s, sizeof(ram_file->bmp_s), 1, hdd_file);
    fread(&ram_file->bmp_fh, sizeof(ram_file->bmp_fh), 1, hdd_file);
    fread(&ram_file->bmp_ih, sizeof(ram_file->bmp_ih), 1, hdd_file);
    
    for(register uint32_t i = 0; i < ram_file->bmp_ih.height; ++i)
        free(ram_file->bmp_pd.pixels[i]);
    free(ram_file->bmp_pd.pixels);
    free(ram_file->bmp_pd.padding);

    ram_file->bmp_pd.pixels = (pixel_t**)malloc(sizeof(pixel_t*) * ram_file->bmp_ih.height);
    for(register uint32_t i = 0; i < ram_file->bmp_ih.height; ++i)
        ram_file->bmp_pd.pixels[i] = (pixel_t*)malloc(sizeof(pixel_t) * ram_file->bmp_ih.width);
    ram_file->bmp_pd.padding = malloc(sizeof(uint8_t) * ram_file->bmp_pd.padding_size);

    for(register uint32_t i = 0; i < ram_file->bmp_ih.height; ++i)
    {
        //this line below gives segmentation fault
        fread(ram_file->bmp_pd.pixels[i], sizeof(pixel_t) * ram_file->bmp_ih.width, 1, hdd_file);
        fread(NULL, sizeof(uint8_t) * ram_file->bmp_pd.padding_size, 1, hdd_file);
    }
    for(register uint8_t i = 0; i < ram_file->bmp_pd.padding_size; ++i)
        ram_file->bmp_pd.padding[i] = (uint8_t)0;
}

//verify errors with fopen
void create_bmp_file(const bmp_file_t *const ram_file, const char *name)
{
    IFDEBUG("create_bmp_file()");
    FILE *hdd_file = fopen(name, "wb");

    fwrite(&ram_file->bmp_s, sizeof(ram_file->bmp_s), 1, hdd_file);
    fwrite(&ram_file->bmp_fh, sizeof(ram_file->bmp_fh), 1, hdd_file);
    fwrite(&ram_file->bmp_ih, sizeof(ram_file->bmp_ih), 1, hdd_file);

    for(register uint32_t i = 0; i < ram_file->bmp_ih.height; ++i)
    {
        fwrite(ram_file->bmp_pd.pixels[i], sizeof(pixel_t) * ram_file->bmp_ih.width, 1, hdd_file);
        fwrite(ram_file->bmp_pd.padding, sizeof(uint8_t) * ((ram_file->bmp_ih.width * 3) % 4), 1, hdd_file);
    }

    fclose(hdd_file);
}

void flip_horizontally(bmp_file_t *const ram_file)
{
    IFDEBUG("flip_horizontally()");
    pixel_t temp;

    for(register uint32_t y = 0; y < ram_file->bmp_ih.height; ++y)
        for(register uint32_t x = 0; x < ram_file->bmp_ih.width/2; ++x)
        {
            temp = ram_file->bmp_pd.pixels[y][x]; 
            ram_file->bmp_pd.pixels[y][x] = ram_file->bmp_pd.pixels[y][ram_file->bmp_ih.width -1 - x];
            ram_file->bmp_pd.pixels[y][ram_file->bmp_ih.width - 1 - x] = temp;
        }
}

void flip_vertically(bmp_file_t *const ram_file)
{
    IFDEBUG("flip_vertically()");
    pixel_t temp;

    for(register uint32_t x = 0; x < ram_file->bmp_ih.width; ++x)
        for(register uint32_t y = 0; y < ram_file->bmp_ih.height/2; ++y)
        {
            temp = ram_file->bmp_pd.pixels[y][x]; 
            ram_file->bmp_pd.pixels[y][x] = ram_file->bmp_pd.pixels[ram_file->bmp_ih.height - 1 - y][x];
            ram_file->bmp_pd.pixels[ram_file->bmp_ih.height - 1 - y][x] = temp;
        }
}
