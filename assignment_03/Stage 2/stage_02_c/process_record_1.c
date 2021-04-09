#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <string.h>

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
    

    char usersfile[1024];
    char locationfile[1024];
    char messagesfile[1024];

    FILE *location = NULL;
    FILE *users = NULL;

    record_t newUsers[2000];
    location_t newLocations[2000];

    record_t temp;
    location_t templ;
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = first_record_id; i <= last_record_id; i++) {
        //  /* open the output file for users */
        // sprintf(usersfile, "user_%06d.dat", i);
        // users = fopen(usersfile, "rb");

        // if (!users)
        // {
        //     fprintf(stderr, "Error opening file %s\n", usersfile);
        //     continue;
        // }

        /* open the output file for location*/
        sprintf(locationfile, "location_%06d.dat", i);
        location = fopen(locationfile, "rb");

        if (!location)
        {
            fprintf(stderr, "\nError opening file\n");
            continue;
        }
        
        /* read the record from the file */
        //record_t *up = read_user(users);
        location_t *lp = read_location(location);
    
        /* =========== start of data processing code ================ */
        if (strstr(lp->location, "Nebraska") != NULL){
           m ++;
        }
        
        
        /* =========== end of data processing code ================ */    
    
        /* free memory */
        //free(rp);
    
        /* close the file */
        //fclose(users);
        fclose(location);
    }    
    
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    printf("\n\n Number of users in Nebraska: %d", m);


    //Process time for stage a is 47.854652 seconds
    //Process time for stage b is 5.381380 seconds 
    //Process time 1.186604 seconds
    
    return 0;
}
