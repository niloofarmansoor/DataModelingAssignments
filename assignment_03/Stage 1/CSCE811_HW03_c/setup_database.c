#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <sys/times.h>
#include <mysql/mysql.h>

#include "record.h"

#define TEXT_SHORT      64

int find_state(char *location, char *state);
int find_city(char *location, char *city);
char **strsplit(const char* str, const char* delim, size_t* numtokens);
char *copyString(const char *string);

int main(int argc, char **argv)
{

    // Create table "Locations"
    int clt = createLocationsTable();

    // Create table "Records"
    int crt = createRecordsTable();

    // Create table "Messages"
    int cmt = createMessagesTable();


    // setlocale(LC_ALL, "en_US.utf8");
    int i;
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
    
    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = first_record_id; i <= last_record_id; i++) {
        /* open the corresponding file */  
        sprintf(filename, "data/record_%06d.dat", i);
    
        fp = fopen(filename, "rb");
    
        if (!fp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            continue;
        }
        
        /* read the record from the file */
        record_t *rp = read_record(fp);
    
        /* =========== start of data processing code ================ */
        char **location;
        size_t numtokens;
        int locID;

        // add a location
        size_t strl = strlen(rp->location);

        if(strl != 0){
            location = strsplit(rp->location, ",", &numtokens);

            char *city = copyString(location[0]);
            char *state = copyString(location[1]);

	    size_t str_length = strlen(city);


            locID = getLocationIdByCityState(city, state);
            if(locID == 0){
                locID = addLocation(city, state, str_length);
            }
        }else{
            locID = addLocation("Unknown", "Unknown", 0);
        }

        // Add a record
        char *sender_name = copyString(rp->name);
        int rid = addRecord( sender_name, locID, rp->message_num);

        // Add the messages of this user here
        int i;
        for(i = 0; i < rp->message_num; i++)
        {
            printf("Time: %d:%d\n", rp->messages[i].hour, rp->messages[i].minute);
            addMessage(rid, rp->messages[i].year, rp->messages[i].month, rp->messages[i].day, rp->messages[i].hour, rp->messages[i].minute, rp->messages[i].text);
        }

        // print_record(rp);

        /* =========== end of data processing code ================ */    
    
        /* free memory */
        free_record(rp);
        
        /* close the file */
        fclose(fp);
    }
    
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}

/* A function that finds the state of a sender in the location string */
int find_state(char *location, char *state)
{
    char **result;
    size_t numtokens;
    int check = 0;
    result = strsplit(location, ",", &numtokens);

    char *st = result[1];
    if(strcmp(st, state) == 0){
        check = 1;
        printf("-> State: %s\n", st);
    }
    return check;
}

/* A function that finds the city of a sender in the location string */
int find_city(char *location, char *city)
{
    char **result;
    size_t numtokens;
    int found = 0;
    result = strsplit(location, ",", &numtokens);

    char *st = result[0];
    if(strcmp(st, city) == 0){
        printf("-> City: %s\n", st);
        found = 1;
    }

    return found;
}


char **strsplit(const char* str, const char* delim, size_t* numtokens) {
    // copy the original string so that we don't overwrite parts of it.
    char *s = strdup(str);
    // these three variables are part of a very common idiom to
    // implement a dynamically-growing array
    size_t tokens_alloc = 1;
    size_t tokens_used = 0;
    char **tokens = calloc(tokens_alloc, sizeof(char*));
    char *token, *strtok_ctx;

    for (token = strtok_r(s, delim, &strtok_ctx);
            token != NULL;
            token = strtok_r(NULL, delim, &strtok_ctx)) {
        // check if we need to allocate more space for tokens
        if (tokens_used == tokens_alloc) {
            tokens_alloc *= 2;
            tokens = realloc(tokens, tokens_alloc * sizeof(char*));
        }
        tokens[tokens_used++] = strdup(token);
    }
    // cleanup
    if (tokens_used == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        tokens = realloc(tokens, tokens_used * sizeof(char*));
    }
    *numtokens = tokens_used;
    free(s);
    return tokens;
}


/*This function makes a copy of a given string.*/
char *copyString(const char *string)
{
	//1.create a new string
	//1.a.comput the length of string
    int size = strlen(string) + 1;
	//1.b.use malloc to create a new string
	char *copy = NULL;
	copy = (char*)malloc(size*sizeof(char));
	//2.copy string to the new string
	strcpy(copy, string);
	//3.return the new string
	return(copy);
}
