#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024

/* location structure */
typedef struct {
    int location_id;
    char location[TEXT_SHORT];
} location_t;

/* message structure */
typedef struct {
    int message_id;
    int record_id;
    char text[TEXT_LONG];       /* text */
    int year;                   /* the send time of the message: */    
    int month;                  /* month/day/year hour:minute */
    int day;
    int hour;                   /* 0 - 23 */
    int minute;               /* 0 - 59 */
} message_t;

/* recor structure */
typedef struct {
    int record_id;
    char name[TEXT_SHORT];
    int message_num;
    location_t *location;
    message_t *message;
} record_t;

/**
 * print a record 
 */
void print_record(record_t *record);

/**
 * read a record from a file
 */
record_t *read_record(FILE *fp);

/**
 * free memory of a record
 */
void free_record(record_t *record);

void print_messages(record_t *record);

void print_location(location_t *location);

#endif