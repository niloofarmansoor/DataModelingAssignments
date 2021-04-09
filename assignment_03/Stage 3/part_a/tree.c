#include "tree.h"

void search_index_add_id(node *head, char *your_state, int your_id){

	node *aux = head;

	while(aux != NULL){
		if(strcmp(aux->state, your_state) == 0){
			add_id_to_state(your_id, aux);
			aux = NULL;
		}
		else{
			aux = aux->next;
		}
	}
}

void add_id_to_state(int id, node *head){

	info *my_info = (info*)malloc(sizeof(info));
	my_info->id = id;

	if(head->data == NULL){	
		my_info->next = NULL;
		head->data = my_info;	
	}
	else{
		my_info->next = head->data;
		head->data = my_info;
	}
}

void print_index(node *head){
	node *aux = head;

	while(aux != NULL){

		printf("index: %d %s\n", aux->number, aux->state);
		print_children(aux->data);
		printf("size: %d\n", get_size_state(aux->data));
		aux = aux->next;
	}	
}

int get_size_state(info *head){

	if(head == NULL)
		return 0;

	info *aux = head;
	int counter = 0;
	while(aux != NULL){
		counter++;
		aux = aux->next;
	}
	return counter;
}

void print_children(info *head){

	info *aux = head;

	while(aux != NULL){

		printf("\t%d", aux->id);
		aux = aux->next;
	}	
	printf("\n");
}

node *add_index(char *value, node *head, int id){

	node *aux = head;
	node *item = (node*)malloc(sizeof(node));
	item->next = NULL;
	item->data = NULL;
	item->state = value;
	item->number = id;

	if(head != NULL){
		while(aux->next != NULL)
			aux = aux->next;

		aux->next = item;
	}
	else{
		head = item;
	}

	return head;
}

node *add_data(int number, node *head){
	return add_index(number, head, 0);
}

node *read_index(FILE *fp){
	int i;      
    
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* allocate memory for the record */
    node *index = (node *)malloc(sizeof(node));
    //index->data = (info*)malloc(sizeof(info) * 1);
    
    /* memory error */
    if (index == NULL) {
        fprintf(stderr, "Cannot allocate memory for record.\n");
        exit(0);
    }
    
    /* read id */
    fread(&(index->number), sizeof(int), 1, fp);

    /* read user name */
    fread(&(index->state), sizeof(char), 1, fp);

    return index;
}

node *get_state_query(node *head, char *state){

	node *aux = head;
	node *my_return;
	while(aux != NULL){
		if(strcmp(aux->state, state) == 0){
			my_return = aux;
			aux = NULL;
		}
		else
			aux = aux->next;
	}

	return my_return;
}

int get_messages_between_nebraska(info *head, my_message *messages){

	info *aux = head;

	int arr[37];
	int has[37];

	int count = 0;
	while(aux != NULL){
		arr[count] = aux->id;
		printf("%d, ", arr[count]);
		aux = aux->next;
		count++;
	}

	int i = 0, k = 0;

	for(i = 0; i < 98357; i++){
		for(k = 0; k < 37; k++){
			printf("%d\n", messages[i].record_id);
			/*if(messages[i].record_id == arr[k]){
				has[k] = 1;
				k = 37;
			}*/
		}
	}
	
	int counter_nebraska = 0;
	for(i = 0; i < 37; i++){
		if(has[i] == 1){
			counter_nebraska++;
		}
	}

	return counter_nebraska;
}