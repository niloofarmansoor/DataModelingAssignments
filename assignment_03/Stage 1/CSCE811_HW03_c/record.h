#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024

/* message structure */
typedef struct {
    char text[TEXT_LONG];       /* text */
    int year;                   /* the send time of the message: */    
    int month;                  /* month/day/year hour:minute */
    int day;
    int hour;                   /* 0 - 23 */
    int minute;                 /* 0 - 59 */
} message_t;


/* record structure */
typedef struct {
    int id;                     /* user id */                                      
    char name[TEXT_SHORT];      /* user name */
    char location[TEXT_SHORT];  /* user location */
    int message_num;            /* number of send message */
    message_t *messages;        /* messages */
} record_t;

/**
 * read a message from a file
 */
void read_message(message_t *message, FILE *fp);

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

/**
 * Create table "Locations"
 */
int createLocationsTable();

/**
 * Create table "Records"
 */ 
int createRecordsTable();

/**
 * Create table "Messages"
 */ 
int createMessagesTable();

/**
 * Insert a new location into the Locations table
 */ 
int addLocation(char *city, char *state, size_t size);

/**
 * Insert a new record into the Records table
 */
int addRecord(char *name, int Lid, int message_num);

/**
 * Retrieve a location id by its city name and state
 */
int getLocationIdByCityState(char *city, char *state); 

/**
 * Retrieve a record from "Records" table by state name
 */ 
// record_t *getRecordByState(char *state, SQLHANDLE handle);

/**
 * Retrieve a record from "Records" table by city name
 */ 
// record_t *getRecordByCity(char *city, SQLHANDLE handle);

/**
 * Retrieve a record from "Records" table by user's name
 */ 
// record_t *getRecordByUserName(char *userName, SQLHANDLE handle);

/**
 * Insert a new message into the "Messages" table
 */ 
int addMessage(int rid, int year, int month, int day, int hour, int minute, char *text);
// int addMessage(int id, int rid, int year, int month, int day, char *m_time, char *text);

/**
 * Retrieve all messages from "Messages" table by record id
 */ 
// message_t *getMessageByRID(int rid, SQLHANDLE handle);


#endif
