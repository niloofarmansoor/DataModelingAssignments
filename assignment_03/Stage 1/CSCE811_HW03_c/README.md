#Environment
---------------------------------------------------------------------------------------------------------------------------------------------------
Use linux machine to compile and run all these C programs. `gcc` compiler is used to compile the C programs. For each part, compile the C program 
separately and then link them together.

Install the following C library for setting up connection to the MySQL database and executing queries using this MySQL API:
```
sudo apt-get install libmysqlclient libmysqlclient-dev
```

#Compilation
--------------------------------------------------------------------------------------------------------------------------------------------------
Before any further compilation, first compile the record.c file:
```
gcc -c record.c `mysql_config --cflags --libs`
gcc -c process_record.c `mysql_config --cflags --libs`
```

Stage 1_Step a_1: The following commands will compile part 1 of step a:
```
gcc -c process_record_1.c `mysql_config --cflags --libs`
gcc -o process_record_1 record.o process_record_1.o `mysql_config --cflags --libs`
./process_record_1 000000 001999 
```

Stage 1_Step a_2: The following commands will compile part 2 of step a:
```
gcc -c process_record_2.c `mysql_config --cflags --libs`
gcc -o process_record_2 record.o process_record_2.o `mysql_config --cflags --libs`
./process_record_2 000000 001999
```

Stage 1_Step a_3: The following commands will compile part 3 of step a:
```
gcc -c process_record_3.c `mysql_config --cflags --libs`
gcc -o process_record_3 record.o process_record_3.o `mysql_config --cflags --libs`
./process_record_3 000000 001999
```


Stage 1_Step a_4: The following comand lines will compile part 4 of step a:
```
gcc -c process_record_4.c `mysql_config --cflags --libs`
gcc -o process_record_4 record.o process_record_4.o `mysql_config --cflags --libs`
./process_record_4 000000 001999
```


# Setting up database
--------------------------------------------------------------------------------------------------------------------------------------------------
After installing the above libraries in the "Environment section", you need to compile proper c program:
```
gcc -c setup_database.c `mysql_config --cflags --libs`
gcc -o setup_database record.o setup_database.c `mysql_config --cflags --libs`
./setup_database 000000 001999
```
# Take backup from database
--------------------------------------------------------------------------------------------------------------------------------------------------
Run the following command in terminal to take a backup from a database in a `.sql` file:

```
mysqldump -u <database_username> -p <database_name> | gzip > <any_name>.sql.zip
```


