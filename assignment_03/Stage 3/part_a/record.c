#include "record.h"

/**
 * print messages 
 */
void print_messages(record_t *record)
{
    int i;

    /* message cannot be NULL */
    if ((&record->message[i]) == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    /* print message id */
    printf("ID: %06d\n", (record->message)->message_id);

    /* print record id */
    printf("RID: %06d\n", (record->message)->record_id);

    for (i = 0; i < record->message_num; i++){
        /* print message time */
        printf("Time: %02d/%02d/%04d %02d:%02d\n", (&record->message[i])->month, (&record->message[i])->day, 
        (&record->message[i])->year, (&record->message[i])->hour, (&record->message[i])->minute);
        
        /* print message text */
        printf("Text: %s\n", (&record->message[i])->text);
    }
}

/**
 * print location
 */

void print_location(location_t *location){
    printf("location \n");

    /* location cannot be NULL */
    if (location == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    /* print location id */
    printf("ID: %06d\n", location->location_id);

    /* print city */
    printf("Location: %s\n", location->location);

    // /* print state */
    // printf("State: %s\n", location->state);
}

/**
 * get state
 */

char *get_state(record_t *record){
    if (record == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }

    record_t *aux = record;

    char *token;
    char *str = (aux->location)->location;
    char *split = ",";

    token = strtok((aux->location)->location, split);
    token = strtok(NULL, split);

    return token;
    //return (record->location)->location;
    //printf("location: %s\n", (record->location)->location);
}

/**
 * print a record 
 */
void print_record(record_t *record) 
{
    int i;
    
    /* record cannot be NULL */
    if (record == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }
    
    /* print user id */
    //printf("ID: %06d\n", record->record_id);
    
    /* print user name */
    printf("Name: %s\n", record->name);
    
    /* print user location */
    //printf("LID: %06d\n", (record->location)->location_id);
    //printf("LID: %s\n", (record->location)->location);
    //printf("location: %s\n", (record->location)->location);

    int size_message = record->message_num;
    //printf("Number messages: %d\n", size_message);

    for(i = 0; i < size_message; i++){
        /* print the number of messages */
        //printf("Number of Messages: %s\n", record->message[i].text);
    }

    
}

/**
 * read a message
 */

void read_message(message_t *message, FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }
    
    /* read message text */
    fread(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
    
    /* read message time */
    fread(&(message->year), sizeof(int), 1, fp);
    fread(&(message->month), sizeof(int), 1, fp);
    fread(&(message->day), sizeof(int), 1, fp);
    fread(&(message->hour), sizeof(int), 1, fp);
    fread(&(message->minute), sizeof(int), 1, fp);
}

/**
 * read a location
 */

void read_location(location_t *location, FILE *fp){
    //char *token = NULL;
     /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }

    /* read user city */
    fread(&(location->location[0]), sizeof(char), TEXT_SHORT, fp);

    // /* read user state */
    //fread(&(location->state[0]), sizeof(char), 16, fp);
}

/**
 * read a record from a file
 */
record_t *read_record(FILE *fp) 
{
    int i;      
    
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* allocate memory for the record */
    record_t *record = (record_t *)malloc(sizeof(record_t));
    record->location = (location_t*)malloc(sizeof(location_t) * 1);
    
    /* memory error */
    if (record == NULL) {
        fprintf(stderr, "Cannot allocate memory for record.\n");
        exit(0);
    }
    
    /* read user id */
    fread(&(record->record_id), sizeof(int), 1, fp);

    /*set location id*/
    record->location->location_id = record->record_id;

    /* read user name */
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);

    /*read location*/
    read_location(&(record->location[0]), fp);
    
    /* read message number */
    fread(&(record->message_num), sizeof(int), 1, fp);
    
    
    /* allocate memory for messages if the message number is greater than 0 */
    if (record->message_num > 0) {
        
        /*allocate memory */
        record->message = (message_t *)malloc(sizeof(message_t) * 
                                               record->message_num);

        /*set message id*/
        record->message->message_id = record->record_id;
        record->message->record_id = record->record_id;
        
        /* memory error */
        if (record->message == NULL) { 
            fprintf(stderr, "Cannot allocate memory for messages.\n");
            exit(0);    
        }
        
        /* read each message from file */
        for(i = 0; i < record->message_num; i++) {
            read_message(&(record->message[i]), fp);
        }
    }
    
    /* return the record */
    return record;
}

/**
 * free memory of a record
 */
void free_record(record_t *record)
{
    if (record == NULL) {
        return;
    }
    
    /* free record memory */
    free(record);
}