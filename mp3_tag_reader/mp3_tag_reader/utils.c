#include "mp3.h"

/* Validate mp3 file */
Status validate_mp3_file(char *filename)
{
    if (strstr(filename, ".mp3") != NULL)
    {
        return e_success;
    }

    return e_failure;
}

/* Open mp3 file */
Status open_mp3_file(char *filename, FILE **fptr)
{
    *fptr = fopen(filename, "rb");

    if (*fptr == NULL)
    {
        return e_failure;
    }

    return e_success;
}

/* Read ID3 Header */
Status read_id3_header(FILE *fp)
{
    char header[4];

    rewind(fp);

    fread(header, 1, 3, fp);

    header[3] = '\0';

    if (strcmp(header, "ID3") == 0)
    {
        return e_success;
    }

    return e_failure;
}

/* Convert syncsafe integer to normal integer */
int syncsafe_to_int(unsigned char *size)
{
    return ((size[0] & 0x7F) << 21) |
           ((size[1] & 0x7F) << 14) |
           ((size[2] & 0x7F) << 7)  |
           (size[3] & 0x7F);
}


/* MP3 Tag Reader*/
void print_help()
{
    printf("          MP3 TAG READER\n");

    printf("EDIT OPERATIONS\n\n");
    printf("-t  Edit Title\n");
    printf("-a  Edit Artist\n");
    printf("-l  Edit Album\n");
    printf("-y  Edit Year\n");
    printf("-g  Edit Genre\n");
    printf("-c  Edit Composer\n\n");

    printf("Examples:\n\n");


    printf("./a.out -a \"Anirudh\" sample.mp3\n");
}