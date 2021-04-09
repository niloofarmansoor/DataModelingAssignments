#Example makefile

#define a variable called CC
CC = gcc 
XML_INCLUDE = -I/usr/include/libxml2
XML_LIB = -lxml2 -lz -lm
ODBC_LIB = -lodbc

#gcc `xml2-config --cflags` unlRSS.c `xml2-config --libs`

# listGames: games.o odbc_utils.o listGames.c
# 	$(CC) $(ODBC_LIB) -o listGames games.o odbc_utils.o listGames.c

process_record: record.o odbc_utils.o process_record_1.c
	$(CC) $(ODBC_LIB) -o PR_1 record.o odbc_utils.o process_record_1.c

odbc_utils.o: odbc_utils.c odbc_utils.h
	$(CC) -c -o odbc_utils.o odbc_utils.c

record.o: record.h record.c
	$(CC) -c -o record.o record.c

clean:
	rm *.o *~ 

