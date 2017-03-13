#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFF_SIZE 1024
#define TOKEN_SIZE 128

struct node{
	int position;
	char data[1000];
	 pointer_addr;
	int size;
	struct node *next;
};

struct Queue{
	struct node *start, *end;
};

struct Queue * free_list;

int help(char **args){
  printf("Enter malloc <size> or free <allocation request number> or print or exit.\n");
  return 1;
}

struct node * create_node(char *line){
	struct node *temp = (struct node *) malloc(sizeof( struct node ));
	strcpy(temp -> data,line);
	temp -> next = NULL;
	return temp;
}

struct Queue * initialize_queue(){
	struct Queue *q = (struct Queue*) malloc(sizeof(struct Queue));
	q -> start = q -> end = NULL;
	return q;
}

void enqueue(struct Queue * q,char *line){
	struct node *temp = create_node(line);
	if(q -> start == NULL){
		q -> start = q -> end = temp;
	}
	else{
		q -> end -> next = temp;
		q -> end = temp;
	}
}

struct Queue * dequeue( struct Queue *q, char *line){
	if (q -> start == NULL){
		return NULL;
	}
	else{
		struct node *temp = q -> start;
		q -> start = q -> start -> next;
		if( q -> start == NULL){
			q -> end = NULL;
		}
		return temp;
	}
}

void print_queue(struct Queue * q){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp = q -> start;
	while(temp -> next != NULL){
		printf("%s\n",temp -> data );
		temp = temp -> next;
	}
}

char** split_line (char * line, int *argc){
	int token_buffer_size = TOKEN_SIZE;
	char **tokens = malloc( token_buffer_size * sizeof(char *));
	char *token;

	if( !tokens){
		fprintf(stderr, "allocation error\n" );
		exit(0);
	}

	else{
		token = strtok(line," ");
		int pos = 0;
		while(token != NULL){
			tokens[pos] = token;
			pos ++;

			if(pos > token_buffer_size){
				token_buffer_size += TOKEN_SIZE;
				tokens = realloc(tokens, token_buffer_size);
				if(!tokens){
					fprintf(stderr, "allocation error\n");
					exit(0);
				}
			}

			if(token[strlen(token)-1] == '\n'){
				token[strlen(token)-1] = '\0';
			}
			token = strtok(NULL," ");
		}

		tokens[pos] = NULL;
		*argc = pos;
		return tokens;
	}
}

int execute(char **args){

	if(args == NULL){
		return 1;
	}
	if(args[0] == NULL){
		return 1;
	}
	if( strcmp(args[0],"malloc") == 0){
		
	}
	else if( strcmp(args[0],"free") == 0){

	}
	else if( strcmp(args[0],"print") == 0){

	}
	else if( strcmp(args[0],"exit") == 0){
		return 1;
	}
}

void interface(){
	char *line;
	char **args;
	char ***args_arr;
	int argc = 0;
	int status;

	do{
		line = readline("$ > ");
		if(line == NULL){
			printf("exit\n");
			break;
		}

		args = split_line(line,&argc);
		status = execute(args);
		free(line);
		free(args);

		argc = 0;

	}while(status);

}

int main(int argc, char const *argv[]){
	interface();
	return 0;
}