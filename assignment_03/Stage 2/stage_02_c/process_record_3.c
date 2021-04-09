#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <string.h>

#include "record.h"

int main(int argc, char **argv)
{
    int i, n;
    int m = 0;
    /* print usage if needed */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s first_record_id last_record_id\n", argv[0]);
        exit(0);
    }
    
    /* first and last record ids */
    int first_record_id = atoi(argv[1]);
    int last_record_id = atoi(argv[2]);
    

    char locationfile[1024];
    char file[1024];

    FILE *location = NULL;
    FILE *fp = NULL;
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = first_record_id; i <= last_record_id; i++) {
         /* open the output file for messages */
        sprintf(file, "record_%06d.dat", i);
        fp = fopen(file, "rb");

        if (!fp)
        {
            fprintf(stderr, "Error opening file \n");
            continue;
        }

        /* open the output file for location*/
        sprintf(locationfile, "location_%06d.dat", i);
        location = fopen(locationfile, "rb");

        if (!location)
        {
            fprintf(stderr, "\nError opening file\n");
            continue;
        }
        
        /* read the record from the file */
        allrecord_t *rp = read_record(fp);
        location_t *lp = read_location(location);
    
        /* =========== start of data processing code ================ */
        if (strstr(lp->location, "Nebraska") != NULL){
            for (n = 0; n < rp->message_num; n++){
                if ((&rp->message[n])->hour == 8 || ((&rp->message[n])->hour == 9 && (&rp->message[n])->minute == 00)) {
                    m++;
                    break;
                }
            }
        }
        
        /* =========== end of data processing code ================ */    
    
        /* free memory */
        //free(rp);
    
        /* close the file */
        fclose(fp);
        //fclose(location);
    }    
    
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    printf("\n\n Number of users who sent messages between 8am-9am: %d\n", m);
    
    return 0;
}
