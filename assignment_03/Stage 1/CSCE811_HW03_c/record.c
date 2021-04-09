#include <string.h>
#include <mysql.h>

#include "record.h"

#define STRING_SIZE 55

#define DB_SEREVR  "localhost"
#define DB_PORT    3306
#define DB_NAME    "csce811_hw3_group_6"
#define DB_USER    "root" 
#define DB_PASS    ""


/**
 * print a message 
 */
void print_message(message_t *message)
{
    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    /* print message time */
    printf("Time: %02d/%02d/%04d %02d:%02d\n", message->month, message->day, 
           message->year, message->hour, message->minute);
    
    /* print message text */
    printf("Text: %s\n", message->text);
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
    printf("ID: %06d\n", record->id);
    
    /* print user name */
    printf("Name: %s\n", record->name);
    
    /* print user location */
    printf("Location: %s\n", record->location);
    
    /* print message if the message number is greater than 0 */
    for (i = 0; i < record->message_num; i++) {
        print_message(&(record->messages[i]));
    }
}

/**
 * read a message from a file
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
    
    /* memory error */
    if (record == NULL) {
        fprintf(stderr, "Cannot allocate memory for record.\n");
        exit(0);
    }
    
    /* read user id */
    fread(&(record->id), sizeof(int), 1, fp);
    
    /* read user name */
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    /* read user location */
    fread(&(record->location[0]), sizeof(char), TEXT_SHORT, fp);
    
    /* read message number */
    fread(&(record->message_num), sizeof(int), 1, fp);
    
    /* initalize messsages */
    record->messages = NULL;
    
    /* allocate memory for messages if the message number is greater than 0 */
    if (record->message_num > 0) {
        
        /*allocate memory */
        record->messages = (message_t *)malloc(sizeof(message_t) * 
                                               record->message_num);
        
        /* memory error */
        if (record->messages == NULL) {
            fprintf(stderr, "Cannot allocate memory for messages.\n");
            exit(0);    
        }
        
        /* read each message from file */
        for(i = 0; i < record->message_num; i++) {
            read_message(&(record->messages[i]), fp);
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
 
    /* free message memory */
    if (record->messages != NULL) {
        free(record->messages);
    }
    
    /* free record memory */
    free(record);
}

/**
 * Create table "Locations"
 */
int createLocationsTable()
{
    MYSQL mysql;

    char create_table[1000];

    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection!\n");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, NULL, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }


    if (mysql_query(&mysql, "CREATE DATABASE IF NOT EXISTS csce811_hw3_group_6")) 
	{
	      fprintf(stderr, "%s\n", mysql_error(&mysql));
	      mysql_close(&mysql);
	      exit(1);
	  }


    printf("\nLogged on to database sucessfully...\n");

    strcpy(create_table, "CREATE TABLE IF NOT EXISTS csce811_hw3_group_6.Locations( ");
    strcat(create_table, "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ");
    strcat(create_table, "city VARCHAR(55), ");
    strcat(create_table, "state VARCHAR(55) )");
    //strcat(create_table, ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci; ");

    if( mysql_query(&mysql, create_table) == 0 )    /* success */
    {
        printf( "'Locations' table is Created!\n");
    }
    else
    {
        printf( "Failed to create table 'Locations': Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    /* Close connection to the database */ 
    printf("Closing database connection...\n");
    mysql_close(&mysql);

    return 1;

}

/**
 * Create table "Records"
 */ 
int createRecordsTable()
{   
    MYSQL mysql;
    char create_table[1000];

    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    if (mysql_real_connect( &mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) )
    {
        printf("Logged on to database sucessfully...\n");
    }

    strcpy(create_table, "CREATE TABLE IF NOT EXISTS Records( ");
    strcat(create_table, "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ");
    strcat(create_table, "name VARCHAR(55), ");
    strcat(create_table, "Lid INT NOT NULL, ");
    strcat(create_table, "message_num INT, ");
    strcat(create_table, "FOREIGN KEY (Lid) REFERENCES Locations(id) ON DELETE CASCADE ");
    strcat(create_table, ")");

    if( mysql_query(&mysql, create_table) == 0 )    /* success */
    {
        printf( "\nTable 'Records' is Created!\n");
    }
    else
    {
        printf( "Failed to create table 'Records': Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    /* Close connection to the database */ 
    printf("Closing database connection...\n");
    mysql_close(&mysql);

    return 1;
}

/**
 * Create table "Messages"
 */ 
int createMessagesTable()
{
    MYSQL mysql;
    char create_table[1000];

    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    if (mysql_real_connect( &mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) )
    {
        printf("Logged on to database sucessfully...\n");
    }

    strcpy(create_table, "CREATE TABLE IF NOT EXISTS Messages( ");
    strcat(create_table, "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ");
    strcat(create_table, "rid INT NOT NULL, ");
    strcat(create_table, "m_date DATE, ");
    strcat(create_table, "m_time TIME, ");
    strcat(create_table, "text TEXT, ");
    strcat(create_table, "FOREIGN KEY (rid) REFERENCES Records(id) ON DELETE CASCADE)");

    if( mysql_query(&mysql, create_table) == 0 )    /* success */
    {
        printf( "\nTable 'Messages' is Created!\n");
    }
    else
    {
        printf( "Failed to create table 'Messages': Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    /* Close connection to the database */ 
    printf("Closing database connection...\n");
    mysql_close(&mysql);

    return 1;
}

/**
 * Insert a new record into "Locations" table
 * Source: https://dev.mysql.com/doc/refman/5.7/en/mysql-stmt-execute.html
 */ 
int addLocation(char *city, char *state, size_t size)
{
    int locID = 0;
    MYSQL mysql;
    
    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection!\n");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    
    //printf("\nLogged on to database sucessfully...\n");

    char *insert_location = "INSERT INTO Locations (city, state) VALUES (?, ?);";

    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);

    if(!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }

    if ( mysql_stmt_prepare(stmt, insert_location, strlen(insert_location)) )
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
	//1
    //fprintf(stdout, " prepare, INSERT successful\n");

    /* Get the parameter count from the statement */
    int param_count;
    param_count = mysql_stmt_param_count(stmt);
   //2
// fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

    if (param_count != 2) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    MYSQL_BIND bind[2];

    /* STRING PARAM */
    //size_t str_length = strlen(city);
    /* This setup is for city which is a string type parameter, 
    then there is a need to specify the buffer_length */
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)city;
    bind[0].buffer_length = size + 1;
    //bind[0].buffer_length = STRING_SIZE;
    bind[0].is_null = 0;
    bind[0].length = &size;

    /* STRING PARAM */
    size_t str_length = strlen(state);
    /* String type parameter for state */
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)state;
    bind[1].buffer_length = str_length + 1;
    bind[1].is_null = 0;
    bind[1].length = &str_length;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Execute the INSERT statement - 2*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    locID = mysql_insert_id(&mysql);

    /* Get the total rows affected */
    unsigned long int affected_rows= mysql_stmt_affected_rows(stmt);
    fprintf(stdout, " total affected rows (inserted): %lu\n", (unsigned long) affected_rows);

    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL.\n");
        exit(0);
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement.\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    mysql_close(&mysql);
    return locID;
}


/**
 * Retrieve the id of a location, city and state, from "Locations" table
 * Source: https://gist.github.com/hoterran/6365915
 * Source: https://dev.mysql.com/doc/refman/8.0/en/c-api-multiple-queries.html
 */ 
int getLocationIdByCityState(char *city, char *state)
{
    int retrieved_id = 0;

    MYSQL mysql;
    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection!\n");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    
    printf("\nLogged on to database sucessfully...\n");

    char *get_query = "SELECT id FROM Locations WHERE city = ? AND state = ?;";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);

    if(!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }

    if ( mysql_stmt_prepare(stmt, get_query, strlen(get_query)) )
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    fprintf(stdout, " prepare, SELECT successful\n");

    /* Get the parameter count from the statement */
    int param_count;
    param_count = mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

    if (param_count != 2) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    MYSQL_BIND bind[2];

    /* STRING PARAM "city" */
    size_t str_length = strlen(city);
    /* This setup is for city varibale which is a string type parameter 
    and passed to the function, therefore there is a need to specify the buffer_length */
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)city;
    bind[0].buffer_length = str_length + 1;
    bind[0].is_null = 0;
    bind[0].length = &str_length;

    /* STRING PARAM "state" */
    str_length = strlen(state);
    /* This setup is for state varibale which is a string type parameter 
    and passed to the function, therefore there is a need to specify the buffer_length */
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)state;
    bind[1].buffer_length = str_length + 1;
    bind[1].is_null = 0;
    bind[1].length = &str_length;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Bind the result to a buffer */
    MYSQL_BIND  result[1];
    int out_put; // Result of executing the select query

    memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer= (char *)&out_put;
    mysql_stmt_bind_result(stmt, result);

    out_put = 0;
    /* Execute the INSERT statement - 2*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    // mysql_stmt_store_result(stmt); 
    while(!mysql_stmt_fetch(stmt)) {
        printf("Retrieved id is: %d \n", out_put);
        retrieved_id = out_put; 
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    /* Close connection to the database */ 
    mysql_close(&mysql);

    return retrieved_id;

}


/**
 * Insert a new record into "Records" table
 * Source: https://dev.mysql.com/doc/refman/5.7/en/mysql-stmt-execute.html
 * Source: https://dev.mysql.com/doc/refman/8.0/en/c-api-prepared-statement-date-handling.html
 */ 
int addRecord(char *name, int Lid, int message_num)
{
    int RecID = 0;
    MYSQL mysql;

    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection!\n");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    
    printf("\nLogged on to database sucessfully...\n");

    char *insert_location = "INSERT INTO Records (name, Lid, message_num) VALUES (?, ?, ?);";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);

    if(!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }

    if ( mysql_stmt_prepare(stmt, insert_location, strlen(insert_location)) )
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    fprintf(stdout, " prepare, INSERT successful\n");

    /* Get the parameter count from the statement */
    int param_count;
    param_count = mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

    if (param_count != 3) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    MYSQL_BIND bind[3];   

    /* STRING PARAM */
    size_t str_length = strlen(name);
    /* This setup is for name of the user which is a string type parameter, 
    then there is a need to specify the buffer_length */
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)name;
    bind[0].buffer_length = str_length + 1;
    bind[0].is_null = 0;
    bind[0].length = &str_length;

    /* INTEGER PARAM */
    /* This is a number type, then there is no need to specify buffer_length */
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = (char *)&Lid;
    bind[1].is_null = 0;
    bind[1].length = 0;

    /* INTEGER PARAM */
    /* This is a number type, then there is no need to specify buffer_length */
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = (char *)&message_num;
    bind[2].is_null = 0;
    bind[2].length = 0;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Execute the INSERT statement - 2*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute,failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    /* Get inserted record ID */
    RecID = mysql_insert_id(&mysql);

    /* Get the total rows affected */
    unsigned long int affected_rows= mysql_stmt_affected_rows(stmt);
    fprintf(stdout, " total affected rows(inserted): %lu\n", (unsigned long) affected_rows);

    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        exit(0);
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    mysql_close(&mysql);
    return RecID;
}

/**
 * Retrieve a record from "Records" table by state name
 */ 
// record_t *getRecordByState(char *state, SQLHANDLE handle);

// /**
//  * Retrieve a record from "Records" table by city name
//  */ 
// record_t *getRecordByCity(char *city, SQLHANDLE handle);

// /**
//  * Retrieve a record from "Records" table by user's name
//  */ 
// record_t *getRecordByUserName(char *userName, SQLHANDLE handle);

// /**
//  * Insert a new message into the "Messages" table
//  */ 
int addMessage(int rid, int year, int month, int day, int hour, int minute, char *text)
{
    MYSQL mysql;

    if( mysql_init(&mysql) == NULL )
	{
		printf("\nFailed to initate MySQL connection!\n");
		exit(0);
	}

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "csce811_group");
    
    if (!mysql_real_connect(&mysql, DB_SEREVR, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(0);
    }
    
    printf("\nLogged on to database sucessfully...\n");

    char *insert_message = "INSERT INTO Messages (rid, m_date, m_time, text) VALUES (?, ?, ?, ?);";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);

    if(!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }

    if ( mysql_stmt_prepare(stmt, insert_message, strlen(insert_message)) )
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    fprintf(stdout, " prepare, INSERT successful\n");

    /* Get the parameter count from the statement */
    int param_count;
    param_count = mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in INSERT query is: %d\n", param_count);

    if (param_count != 4) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    MYSQL_BIND bind[4];  

    /* INTEGER PARAM */
    /* This is a number type (record id from table "Records"), then there is no need to specify buffer_length */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&rid;
    bind[0].is_null = 0;
    bind[0].length = 0;

    /* DATE PARAM */
    // Source: https://www.gymzn.cz/ivt/mysql-help/Help%20Oficial/apis.html
    // Source: https://dev.mysql.com/doc/refman/8.0/en/c-api-prepared-statement-date-handling.html

    MYSQL_TIME ts_date;
    /* This setup is for Date of the message which is a string type parameter, 
        then there is a need to specify the buffer_length */
    bind[1].buffer_type = MYSQL_TYPE_DATE;
    bind[1].buffer = (char *)&ts_date;
    bind[1].is_null = 0;
    bind[1].length = 0;

    ts_date.year = year;
    ts_date.month = month;
    ts_date.day = day;

    // Convert time to string
    char time[12];
    strcpy(time, "'");

    char h[3]; char m[3]; char s[3];
    snprintf(h, 3, "%d", hour);
    strcat(time, h); strcat(time, ":");

    snprintf(m, 3, "%d", minute);
    strcat(time, m); strcat(time, ":");

    snprintf(s, 3, "%d", 00);
    strcat(time, s); strcat(time, "'");
    printf("Converted time to string: %s\n", time);

    /* TIME PARAM */
    MYSQL_TIME ts_time;
    /* This setup is for Time of the message which is a string type parameter, 
        then there is a need to specify the buffer_length */
    bind[2].buffer_type = MYSQL_TYPE_TIME;
    bind[2].buffer = (char *)&ts_time;
    bind[2].is_null = 0;
    bind[2].length = 0;

    //ts_time.day = 0;
    ts_time.hour = hour;
    ts_time.minute = minute;
    ts_time.second = 0;

    /* STRING PARAM */
    size_t str_length = strlen(text);
    /* This setup is for text, the content of a message record which is a string type parameter, 
        then there is a need to specify the buffer_length */
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)text;
    bind[3].buffer_length = str_length + 1;
    bind[3].is_null = 0;
    bind[3].length = &str_length;
    

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Execute the INSERT statement - 2*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Get the total rows affected */
    unsigned long int affected_rows= mysql_stmt_affected_rows(stmt);
    fprintf(stdout, " total affected rows(insert 2): %lu\n", (unsigned long) affected_rows);

    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        exit(0);
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    mysql_close(&mysql);
    return 1;
}

// /**
//  * Retrieve all messages from "Messages" table by record id
//  */ 
// message_t *getMessageByRID(int rid, SQLHANDLE handle);
