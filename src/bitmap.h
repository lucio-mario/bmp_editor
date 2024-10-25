#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef struct bmp_signature_st
{
    char file_type[2];
} bmp_signature_t;

typedef struct bmp_file_header_st
{
    uint32_t file_size;
    uint32_t reserved;
    uint32_t off_bits;
} bmp_file_header_t;

typedef struct bmp_image_header_st
{
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t image_size;
    uint32_t xppm;
    uint32_t yppm;
    uint32_t clr_used;
    uint32_t clr_important;
} bmp_image_header_t;

typedef struct pixel_st
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} pixel_t;

typedef struct bmp_pixel_data_st
{
    pixel_t **pixels;
    uint8_t *padding;
    uint8_t padding_size;
} bmp_pixel_data_t;

typedef struct bmp_file_st
{
    bmp_signature_t bmp_s;
    bmp_file_header_t bmp_fh;
    bmp_image_header_t bmp_ih;
    bmp_pixel_data_t bmp_pd;
} bmp_file_t;

void copyr(void);

void get_bmp_file(bmp_file_t *const ram_file, const char *hdd_file_name);
void init_bmp_file(bmp_file_t *const ram_file, uint32_t width, uint32_t height);
void create_bmp_file(const bmp_file_t *const ram_file, const char *name);
void print_file_info(const bmp_file_t *const ram_file);

void flip_horizontally(bmp_file_t *const file);
void flip_vertically(bmp_file_t *const file);
//void rotate_counter_clockwise();
//void rotate_clockwise();

#endif //__BITMAP_H__
