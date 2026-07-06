#include "mp3.h"

Status edit_frame(FILE *fp, char *frame_name, char *new_data)
{
    FILE *temp;
    int size;

    char header[10];
    char frame_id[5];
    unsigned char size_buf[4];
    unsigned char flags[2];

    temp = fopen("temp.mp3", "wb");

    if(temp == NULL)
    {
        return e_failure;
    }

    rewind(fp);

    /* Copy 10-byte ID3 header */
    fread(header, 1, 10, fp);
    fwrite(header, 1, 10, temp);

    /* Read frame id */
    fread(frame_id, 1, 4, fp);
    frame_id[4] = '\0';

    if(strcmp(frame_id, frame_name) == 0)
    {
        /* Write frame id */
        fwrite(frame_id, 1, 4, temp);

        /* Read old size */
        fread(size_buf, 1, 4, fp);

        int old_size;

        old_size = (size_buf[0] << 24) |
                    (size_buf[1] << 16) |
                    (size_buf[2] << 8)  |
                    size_buf[3];

        /* New size */
        size = strlen(new_data) + 1;

        size_buf[0] = (size >> 24) & 0xFF;
        size_buf[1] = (size >> 16) & 0xFF;
        size_buf[2] = (size >> 8)  & 0xFF;
        size_buf[3] = size & 0xFF;

        fread(flags,1,2,fp);
        fwrite(size_buf, 1, 4, temp);
        fwrite(flags,1,2,temp); 

        fputc(0x00, temp);

        fwrite(new_data, 1, strlen(new_data), temp);
        

        fseek(fp, old_size - 1, SEEK_CUR);

        char ch;

        while (fread(&ch, 1, 1, fp) == 1)
        {
            fwrite(&ch, 1, 1, temp);
        }

        //fclose(fp);
        fclose(temp);

        remove("sample.mp3");
        rename("temp.mp3", "sample.mp3");

        return e_success;
    }
}

