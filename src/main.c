#include "common.h"

#define STANDARD_OUTPTUP_FILE_NAME "a.bmp"
#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char **argv)
{
    int opt;
    char hdd_file[BUFFER_SIZE];
    bmp_file_t bmp_file;

    IFDEBUG("Starting optarg loop...");

    /* getopt() configured options:
     *        -h  help
     *        -c  copyright and version
     *        -v  verbose
     *        -f  input file
     *        -o  output file
     *        -w  width
     *        -t  height
     *        -a  flip horizontally
     *        -b  flip vertically
     *        -x  rotate clockwise
     *        -y  rotate counter-clockwise
     */
    opterr = 0;
    while((opt = getopt(argc, argv, "vhcfowtabxy:")) != EOF)
        switch(opt)
        {
            case 'h':
                help();
                break;
            case 'c':
                copyr();
                break;
            case 'v':
                verb++;
                break;
            case 'f':
                strcpy(hdd_file, optarg);
                break;
            case 'a':
                break;
            case 'b':
                break;
            case 'x':
                break;
            case 'y':
                break;
            case '?':
            default:
                printf("Type\n\t$man %s\nor\n\t$%s -h\nfor help.\n\n", argv[0], argv[0]);
                return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb);

    IFDEBUG("Starting image creation...");
    
    init_bmp_file(&bmp_file, WIDTH, HEIGHT);
    create_bmp_file(&bmp_file, "standard.bmp");
    get_bmp_file(&bmp_file, "standard.bmp");
    flip_horizontally(&bmp_file);
    create_bmp_file(&bmp_file, "inverted_standard.bmp");

    return EXIT_SUCCESS;
}
