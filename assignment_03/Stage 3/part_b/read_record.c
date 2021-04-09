#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/times.h>

#include "record.h"
#include "tree.h"

#define TOTAL_STATES 51
#define TOTAL_FILES 2000
#define FAN_OUT_10 10
#define FAN_OUT_200 200
#define TOTAL_MESSAGES 98357

int main(int argc, char **argv)
{
    /* print usage if needed */
    /*if (argc != 2) {
        fprintf(stderr, "Usage: %s fan-out\n", argv[0]);
        exit(0);
    }*/
    
    /* get record number */
    //int fan_out = atoi(argv[1]);

    int i = 0;
    
    /* open the corresponding file */

    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

    char *states[TOTAL_FILES];
    record_t *records[TOTAL_FILES];
    int record_ids[TOTAL_FILES];
    char *states_records[TOTAL_FILES];
    my_message *messages[TOTAL_MESSAGES];
    my_record *my_records[TOTAL_FILES];

    int total_messages = 0;
    int counter_message = 0;
    int k = 0, l = 0, m = 0;
    for(i = 0; i < TOTAL_FILES; i++){
    //for(i = 0; i < 1; i++){

        char filename[1024];
        //sprintf(filename, "record/record_%06d.dat", record_number);
        sprintf(filename, "record/record_%06d.dat", i);
        
        FILE *fp = fopen(filename,"rb");
        
        if (!fp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            exit(0);
        }
        
        /* start time */
        //gettimeofday(&time_start, NULL);
        
        /* read the record from the file */
        record_t *rp = read_record(fp);

        record_t *helper = rp;

        int total_msg = helper->message_num;
        total_messages = total_messages + total_msg;
        

        my_record *record_obj = (my_record*)malloc(sizeof(my_record));
        record_obj->record_id = helper->record_id;
        record_obj->message_num = helper->message_num;
        //record_obj->name = helper->name;
        strcpy(record_obj->name,helper->name);
        /*for(m = 0; m < total_msg; m++){
            printf("our id %d, recordIdMessage %d count %d\n", helper->record_id, helper->message[m].record_id, total_msg);
        }*/

        //printf("my_id %d, message_record_id %d\n", helper->record_id, helper->message[1].record_id);

        for(m = 0; m < total_msg; m++, counter_message++){

            my_message *message_obj = (my_message*)malloc(sizeof(my_message));
            message_obj->message_id = helper->message[m].message_id;
            message_obj->record_id = helper->record_id;
            message_obj->hour = helper->message[m].hour;
            message_obj->minute = helper->message[m].minute;
            messages[counter_message] = message_obj;
            
            record_obj->message_id[m] = message_obj->message_id;

            //printf("messageID %d, recordID %d\n", helper->message[m].message_id, helper->message[m].record_id);
        }

        /*for(l = 0, counter_message; counter_message < TOTAL_MESSAGES; counter_message++, l++){
            my_message *message_obj = (my_message*)malloc(sizeof(my_message));
            message_obj->message_id = helper->message[i].message_id;
            message_obj->record_id = helper->message[i].record_id;
            message_obj->hour = helper->message[i].hour;
            message_obj->minute = helper->message[i].minute;
            messages[counter_message] = message_obj;
            record_obj->message_id[l] = message_obj->message_id;
            //printf("message id: %d\n", helper->message[i].message_id); 
        }*/

        my_records[i] = record_obj;

        records[i] = rp;

        //printf("id %d, name %s, location %s\n", rp->record_id, rp->name, (rp->location)->location);

        states[i] = get_state(rp);
        
        states_records[i] = states[i];
        record_ids[i] = rp->record_id;

        /* free memory */
        free_record(rp);
        
        /* close the file */
        fclose(fp);

    }

    int size_states = sizeof(states)/sizeof(char*);

    int j = 0;

    for(i = 0; i < size_states - 1; i++){
        for(j = 0; j < size_states - 1; j++){

            if(states[j+1] == NULL){
                char *temp = states[j];
                states[j] = states[j+1];
                states[j+1] = temp;
            }
            else if(states[j] != NULL && strcmp(states[j], states[j+1]) > 0){
                //char *temp = states[j];
                //strcpy(states[j], states[j+1]);
                //strcpy(states[j+1], temp);
                char *temp = states[j];
                states[j] = states[j+1];
                states[j+1] = temp;
            }
        }
    }



    char *previous = "";
    int total_states = 0;
    
    char *states_arr[TOTAL_STATES];

    node *tree = NULL;

    for(int i = 2; i < 2000; i++){
        if(strcmp(states[i], previous) == 0){
            previous = states[i];
        }
        else{
            states_arr[total_states] = states[i];
            tree = add_index(states[i], tree, total_states);
            total_states++;
            previous = states[i];
        }
    }

    for(i = 0; i < TOTAL_FILES; i++){
        if(states_records[i] != NULL){
            //printf("%d %s\n ", i, states_records[i]);
            search_index_add_id(tree, states_records[i], record_ids[i]);
        }
    }

    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
    printf("\n\nProcess time %f seconds to build database\n", totaltime);

    FILE *outLocation; 
    FILE *outRecord; 
    FILE *outMessage; 
      
    // open file for writing 
    outLocation = fopen ("indexLocation.dat", "w"); 
    if (outLocation == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
    outRecord = fopen ("indexRecord.dat", "w"); 
    if (outRecord == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
    outMessage = fopen ("indexMessage.dat", "w"); 
    if (outMessage == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 
      
    // write struct to file 
    fwrite (&tree, sizeof(node), 1, outLocation); 
    fwrite (&messages, sizeof(messages), 1, outMessage); 
    fwrite (&my_records, sizeof(my_records), 1, outRecord); 
      
    if(fwrite != 0)  
        printf("contents to file written successfully !\n"); 
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outLocation);
    fclose (outMessage);
    fclose (outRecord);

    return 0;
}
