#include "mp3.h"
Status read_frames(FILE *fp,MP3Info *info){
    char frame_id[5];
    int size;

    unsigned char size_buf[4];
    char buffer[100];

    /* Move after ID3 header */
    fseek(fp,10,SEEK_SET);

    while(fread(frame_id,1,4,fp)==4){
        frame_id[4]='\0';

        /* Read frame size */
        fread(size_buf,1,4,fp);

        size=(size_buf[0]<<24)|(size_buf[1]<<16)|(size_buf[2]<<8)|size_buf[3];

        /* Skip flags */
        fseek(fp,2,SEEK_CUR);

        /* Skip encoding byte */
        fseek(fp,1,SEEK_CUR);

        /* Prevent overflow */
        if(size <= 1 || size > 99)
        {
            fseek(fp,size-1,SEEK_CUR);
            continue;
        }
        
        /* Read frame data */
        fread(buffer,1,size-1,fp);

        buffer[size-1]='\0';

        /* Compare frame IDs */
        if(strcmp(frame_id,TITLE_FRAME)==0){
            strcpy(info->title,buffer);
        }

        else if(strcmp(frame_id,ARTIST_FRAME)==0){
            strcpy(info->artist,buffer);
        }

        else if(strcmp(frame_id,ALBUM_FRAME)==0){
            strcpy(info->album,buffer);
        }
        else if(strcmp(frame_id,YEAR_FRAME)==0){
            strcpy(info->year,buffer);
        }
        else if(strcmp(frame_id,GENRE_FRAME)==0){
            strcpy(info->genre,buffer);
        }
        else if(strcmp(frame_id,COMPOSER_FRAME)==0){
            strcpy(info->composer,buffer);
        }

        /* Stop if all tags found */
        if(strlen(info->title)&&
            strlen(info->artist)&&
            strlen(info->album)&&
            strlen(info->year)&&
            strlen(info->genre)&&
            strlen(info->composer))
            {
                break;
            }
    }
    return e_success;
}
    void display_tags(MP3Info *info)
    {
        printf("Title    : %s\n", info->title);

        printf("Artist   : %s\n", info->artist);

        printf("Album    : %s\n", info->album);

        printf("Year     : %s\n", info->year);

        printf("Genre    : %s\n", info->genre);

        printf("Composer : %s\n", info->composer);
    }