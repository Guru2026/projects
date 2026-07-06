#ifndef MP3_H
#define MP3_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "types.h"

/* Frame IDs */
#define TITLE_FRAME    "TIT2"
#define ARTIST_FRAME   "TPE1"
#define ALBUM_FRAME    "TALB"
#define YEAR_FRAME     "TYER"
#define GENRE_FRAME    "TCON"
#define COMPOSER_FRAME "COMM"

/* Function Prototypes */

/* Validate mp3 file */
Status validate_mp3_file(char *filename);

 /* HELP */
 void print_help();

/* Open mp3 file */
Status open_mp3_file(char *filename, FILE **fptr);

/* Read ID3 header */
Status read_id3_header(FILE *fp);

/* Read all frames */
Status read_frames(FILE *fp, MP3Info *info);


/* Display all tag details */
void display_tags(MP3Info *info);

/* Convert syncsafe integer */
int syncsafe_to_int(unsigned char *size);

/* Extract frame content */
//Status extract_frame_data(FILE *fp, int size, char *buffer);

/* Edit frame */
Status edit_frame(FILE *fp, char *frame_name, char *new_data);

#endif