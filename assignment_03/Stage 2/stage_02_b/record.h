#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdio.h>
#include <stdlib.h>

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
    int message_num;
    char text[TEXT_LONG];       /* text */
    int year;                   /* the send time of the message: */    
    int month;                  /* month/day/year hour:minute */
    int day;
    int hour;                   /* 0 - 23 */
    int minute;                 /* 0 - 59 */
} message_t;


/* record structure */
typedef struct {
    int record_id;                     /* user id */                                      
    char name[TEXT_SHORT];     /* user name */
} record_t;


/* all record structure */
typedef struct {
    record_t *record;
    location_t *location;
    message_t *message;
    int message_num;
} allrecord_t;

/**
 * print a record 
 */
void print_user(record_t *record);

/**
 * read a record from a file
 */
allrecord_t *read_record(FILE *fp);

/**
 * free memory of a record
 */
record_t *read_user(FILE *fp);
void print_message(message_t *message);
void print_location(location_t *location);
message_t *read_message(FILE *fp);
location_t *read_location(FILE *fp);
void free_record(allrecord_t *record);

#endif
