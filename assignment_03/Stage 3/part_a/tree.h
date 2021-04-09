#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_LONG       1024
#define TEXT_SHORT      64

//location
typedef struct{
    int id;
    struct info *next;
}info;

//location
typedef struct{
    int number;
    char *state;
    struct node *next;
    info *data;
}node;

//message
typedef struct {
    int message_id;
    int record_id;
    int hour;                   /* 0 - 23 */
    int minute;               /* 0 - 59 */
} my_message;

//record
typedef struct {
    int record_id;
    char name[TEXT_SHORT];
    int message_num;
    int message_id[TEXT_LONG];
} my_record;

void search_index_add_id(node *head, char *your_state, int your_id);

void add_id_to_state(int id, node *head);

void print_index(node *head);

void print_children(info *head);

int get_size_state(info *head);

node *get_state_query(node *head, char *state);

node *add_index(char *number, node *head, int total_states);

node *add_data(int number, node *head);

node *read_index(FILE *fp);

int get_messages_between_nebraska(info *head, my_message *messages);
