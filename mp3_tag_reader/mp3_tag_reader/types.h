#ifndef TYPES_H
#define TYPES_H
#include<stdio.h>

/* Status values */
typedef enum{
    e_success,
    e_failure
}Status;

/* MP3 tag information structure */
typedef struct{
    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char genre[50];
    char composer[100];
}MP3Info;

/* Frame header structure */
typedef struct{
    char frame_id[5];
    int frame_size;
    char flags[3];
}Frameheader;

#endif