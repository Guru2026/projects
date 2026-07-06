#include "mp3.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    MP3Info info;

    /* HELP */
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        print_help();
        return 0;
    }
    

    /* VIEW OPERATION */
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        
        /* Validate mp3 file */
        if (validate_mp3_file(argv[2]) == e_failure)
        {
            printf("Error: Invalid MP3 file\n");
            return e_failure;
        }

        /* Open mp3 file */
        if (open_mp3_file(argv[2], &fp) == e_failure)
        {
            printf("Error: Unable to open file\n");
            return e_failure;
        }

        /* Read ID3 header */
        if (read_id3_header(fp) == e_failure)
        {
            printf("Error: ID3 header not found\n");

            fclose(fp);

            return e_failure;
        }

        /* Initialize structure */
        memset(&info, 0, sizeof(MP3Info));

        /* Read all frames */
        read_frames(fp, &info);

        /* Display tags */
        display_tags(&info);

        fclose(fp);
    }
    else if(argc==4){
        if(validate_mp3_file(argv[3])==e_failure){
            printf("Error: Invalid MP3 file\n");
            return e_failure;
        }
        fp=fopen(argv[3],"rb+");

        if(fp==NULL){
            printf("Error: Unable to open file\n");
             return e_failure;
        }
        if(read_id3_header(fp)==e_failure){
            printf("Error: ID3 Header not found\n"); 
            fclose(fp); 
            return e_failure;
        }
        if(strcmp(argv[1],"-t")==0){
            edit_frame(fp,TITLE_FRAME,argv[2]);
        }
        else if(strcmp(argv[1],"-a")==0){
            edit_frame(fp,ARTIST_FRAME,argv[2]);
        }
        else if(strcmp(argv[1],"-l")==0){
            edit_frame(fp,ALBUM_FRAME,argv[2]);
        }
        else if(strcmp(argv[1],"-y")==0){
            edit_frame(fp,YEAR_FRAME,argv[2]);
        }
        else if(strcmp(argv[1],"-g")==0){
            edit_frame(fp,GENRE_FRAME,argv[2]);
        }
        else if(strcmp(argv[1],"-c")==0){
            edit_frame(fp,COMPOSER_FRAME,argv[2]);
        }else{
            printf("Invalid Edit Option\n");
        }

        fclose(fp);
        
    }
    else
    {
        printf("Usage:\n");

        printf("./a.out -v <mp3file>\n");
    }

    return e_success;
}