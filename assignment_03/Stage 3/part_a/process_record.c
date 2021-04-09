#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"


int main(int argc, char **argv)
{
    int i;
    int m = 0;
    /* print usage if needed */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s first_record_id last_record_id\n", argv[0]);
        exit(0);
    }
    
    /* first and last record ids */
    int first_record_id = atoi(argv[1]);
    int last_record_id = atoi(argv[2]);
    

    char filename[1024];
    FILE *fp = NULL;
    FILE *location;
    FILE *users;
    FILE *messages;
    char locationfile[1024];
    char usersfile[1024];
    char messagesfile[1024];
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = first_record_id; i <= last_record_id; i++) {
        /* open the corresponding file */  
        sprintf(filename, "record/record_%06d.dat", i);
    
        fp = fopen(filename,"rb");
    
        if (!fp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            continue;
        }
        /* open the output file for location*/
        sprintf(locationfile, "location/location_%06d.dat", i);
        location = fopen(locationfile, "wb");

        if (location == NULL) 
        { 
            fprintf(stderr, "\nError opend file\n"); 
            exit (1); 
        } 

        /* open the output file for users */
        sprintf(usersfile, "user/user_%06d.dat", i);
        users = fopen(usersfile, "wb");

        if (users == NULL) 
        { 
            fprintf(stderr, "\nError opend file\n"); 
            exit (1); 
        } 

        /* open the output file for users */
        sprintf(messagesfile, "message/message_%06d.dat", i);
        messages = fopen(messagesfile, "wb");

        if (messages == NULL) 
        { 
            fprintf(stderr, "\nError opend file\n"); 
            exit (1); 
        } 

        /* read the record from the file */
        record_t *rp = read_record(fp);
    
        /* =========== start of data processing code ================ */
    
        fwrite(rp->location, sizeof(rp->location), 1, location);

        fwrite(rp, sizeof(rp), 1, users);

        fwrite(rp->message, sizeof(rp->message), rp->message_num, messages);
        
        /* =========== end of data processing code ================ */  

        /* free memory */
        free_record(rp);

        /* close the files */
        fclose(users);
        fclose(location);
        fclose(messages);
        fclose(fp);
        
    }    

    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);

    //Process time 45.628674 seconds
    
    return 0;
}
