#include "record.h"

/**
 * print a message 
 */
void print_message(message_t *message)
{
    int i;
     /* record cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }
    printf("ID: %06d\n", message->message_id);
    printf("RID: %06d\n", message->record_id);
    printf("Number of Messages: %d\n", message->message_num);

    for (i = 0; i < message->message_num; i++) {
        /* message cannot be NULL */
        if (message == NULL) {
            fprintf(stderr, "The message is NULL\n");
            exit(0);
        }

        /* print message time */
        printf("Time: %02d/%02d/%04d %02d:%02d\n", message[i].month, message[i].day, 
            message[i].year, message[i].hour, message[i].minute);
        
        /* print message text */
        printf("Text: %s\n", message[i].text);
    }
}

/**
 * print a record 
 */
void print_user(record_t *record) 
{
    int i;
    
    /* record cannot be NULL */
    if (record == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }
    
    /* print user id */
    printf("ID: %06d\n", record->record_id);
    
    /* print user name */
    printf("Name: %s\n", record->name);
    
}
/**
 * print a location
 */
void print_location(location_t *location){
     /* record cannot be NULL */
    if (location == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }

    /* print location id */
    printf("LID: %06d\n", location->location_id);

    /* print user location */
    printf("Location: %s\n", location->location);
}

location_t *read_location(FILE *fp){
     /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    location_t *location = (location_t *)malloc(sizeof(location_t) * 1);
    /* read user id */
    fread(&(location->location_id), sizeof(int), 1, fp);
    /* read user city */
    fread(&(location->location[0]), sizeof(char), TEXT_SHORT, fp);

    return location;
}

/**
 * read a user from a file
 */
record_t *read_user(FILE *fp){
     /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    record_t *record = (record_t *)malloc(sizeof(record_t) * 1);
    /* read user id */
    fread(&(record->record_id), sizeof(int), 1, fp);
    /* read user city */
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);

    return record;
}

/**
 * read a message from a file
 */
message_t *read_message(FILE *fp)
{
    int i;
    message_t *message = (message_t *)malloc(sizeof(record_t));
    
    /* read message id and record id */
    fread(&(message->message_id), sizeof(int), 1, fp);
    fread(&(message->record_id), sizeof(int), 1, fp);
    fread(&(message->message_num), sizeof(int), 1, fp);

    for(i = 0; i < message->message_num; i++) {
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
        fread(&(message[i].text[0]), sizeof(char), TEXT_LONG, fp);
        
        /* read message time */
        fread(&(message[i].year), sizeof(int), 1, fp);
        fread(&(message[i].month), sizeof(int), 1, fp);
        fread(&(message[i].day), sizeof(int), 1, fp);
        fread(&(message[i].hour), sizeof(int), 1, fp);
        fread(&(message[i].minute), sizeof(int), 1, fp);
    }
    return message;
}

/**
 * read a record from a file
 */
allrecord_t *read_record(FILE *fp)
{
    int i;      
    
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* allocate memory for the record */
    allrecord_t *allrecord = (allrecord_t *)malloc(sizeof(allrecord_t));
    
    /* memory error */
    if (allrecord == NULL) {
        fprintf(stderr, "Cannot allocate memory for record.\n");
        exit(0);
    }

    /*allocate record memory */
    allrecord->record = (record_t *)malloc(sizeof(record_t) * 1);
    
    /* read user id */
    fread(&(allrecord->record[0].record_id), sizeof(int), 1, fp);
    
    /* read user name */
    fread(&(allrecord->record[0].name[0]), sizeof(char), TEXT_SHORT, fp);
    
    /* allocate memory to location */
    allrecord->location = (location_t *)malloc(sizeof(location_t) * 1);

    /* read location id */
    allrecord->location[0].location_id = allrecord->record[0].record_id;

    /* read user location */
    fread(&(allrecord->location[0].location), sizeof(char), TEXT_SHORT, fp);

    /* read message number */
    fread(&(allrecord->message_num), sizeof(int), 1, fp);
    
    /* initalize messsages */
    allrecord->message = NULL;
    
    /* allocate memory for messages if the message number is greater than 0 */
    if (allrecord->message_num > 0) {
        
        /*allocate memory */
        allrecord->message = (message_t *)malloc(sizeof(message_t) * allrecord->message_num);
        
        /* memory error */
        if (allrecord->message == NULL) {
            fprintf(stderr, "Cannot allocate memory for messages.\n");
            exit(0);    
        }

        allrecord->message->message_id = allrecord->record[0].record_id;
        allrecord->message->record_id = allrecord->record[0].record_id;

        allrecord->message->message_num = allrecord->message_num;
        
        /* read each message from file */
        for(i = 0; i < allrecord->message->message_num; i++) {
            /* Assume file has been opened */
            if (fp == NULL) {
                fprintf(stderr, "The file stream is NULL\n");
                exit(0);
            }
            
            /* message cannot be NULL */
            if (allrecord->message == NULL) {
                fprintf(stderr, "The message is NULL\n");
                exit(0);
            }
            
            /* read message text */
            fread(&(allrecord->message[i].text[0]), sizeof(char), TEXT_LONG, fp);
            
            /* read message time */
            fread(&(allrecord->message[i].year), sizeof(int), 1, fp);
            fread(&(allrecord->message[i].month), sizeof(int), 1, fp);
            fread(&(allrecord->message[i].day), sizeof(int), 1, fp);
            fread(&(allrecord->message[i].hour), sizeof(int), 1, fp);
            fread(&(allrecord->message[i].minute), sizeof(int), 1, fp);
        }

    }
    
    /* return the record */
    return allrecord;
}

/**
 * free memory of a record
 */
void free_record(allrecord_t *allrecord)
{
    if (allrecord == NULL) {
        return;
    }
 
    /* free message memory */
    if (allrecord->message != NULL) {
        free(allrecord->message);
    }
    
    /* free record memory */
    free(allrecord);
}

