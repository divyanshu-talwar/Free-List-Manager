#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFF_SIZE 1024
#define TOKEN_SIZE 128

int pos;
struct node{
	int position;
	int *pointer;
	int size;
	struct node *next;
};

struct Queue{
	struct node *front, *rear;
};

struct Queue * free_list;

int help(){
  printf("Enter malloc <size> or free <allocation request number> or print or exit.\n");
  return 1;
}

struct node * create_node( int position, int size){
	struct node *temp = (struct node *) malloc(sizeof( struct node ));
	temp -> position = position;
	temp -> size = size;
	temp -> next = NULL;
	return temp;
}

struct Queue * initialize_queue(){
	struct Queue *q = (struct Queue*) malloc(sizeof(struct Queue));
	q -> front = q -> rear = NULL;
	return q;
}

void enqueue(struct Queue * q,int position, int size){
	struct node *temp = create_node( position, size);
	if(q -> front == NULL){
		q -> front = q -> rear = temp;
	}
	else{
		q -> rear -> next = temp;
		q -> rear = temp;
	}
}

struct node * dequeue( struct Queue *q){
	if (q -> front == NULL){
		return NULL;
	}
	else{
		struct node *temp = q -> front;
		q -> front = q -> front -> next;
		if( q -> front == NULL){
			q -> rear = NULL;
		}
		return temp;
	}
}

struct node * del_kth_entry( struct Queue *q, int k){
	struct node *temp = q -> front;
	int count = 1;
	if( k == 1){
		return dequeue( q);
	}
	else{
		while( count < k-1 && temp != NULL ){
			count++;
			temp = temp -> next;
		}
		if( temp == NULL || temp -> next == NULL){
			return NULL;
		}
		else {
			struct node *temp1 = temp -> next;
			temp -> next = temp1 -> next;
			temp1 -> next = NULL;
			if (temp -> next == NULL){
				q -> rear = temp;
			}
			return temp1;
		}
	}
}

void print_queue(struct Queue * q){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp = q -> front;
	while(temp != NULL){
		printf("| position = %d, size = %d, pointer addr = %p | --> ",temp -> position, temp -> size, &(temp -> pointer) );
		temp = temp -> next;
	}
	printf("%s","NULL" );
	free(temp);
}

char** split_line (char * line, int *argc){
	int token_buffer_size = TOKEN_SIZE;
	char **tokens = (char **)malloc( token_buffer_size * sizeof(char *));
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
				tokens = (char **)realloc(tokens, token_buffer_size);
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
	else if( strcmp(args[0],"help") == 0){
		help();
	}
	else if( strcmp(args[0],"malloc") == 0){
		if( args[1] != NULL){
			printf("malloc request\n");
			int val = atoi(args[1]);
			pos += 1;
			enqueue( free_list, pos, val);
			free_list -> rear -> pointer = (int * )malloc(val);
			//add an entry to the list and then malloc using the int ptr in the node
		}
		else{
			fprintf(stderr, "%s\n","Illegal malloc request : specify size to malloc!" );
		}
		return 1;
	}
	else if( strcmp(args[0],"free") == 0){
		if( args[1] != NULL){
			printf("free request\n");
			int val = atoi(args[1]);
			if( val > pos){
				fprintf(stderr, "%s\n","Illegal free request" );
			}
			else{
				struct node *temp = del_kth_entry(free_list, val);
				if ( temp != NULL){
					free(temp -> pointer);
					free( temp);
					printf("successful\n");
				}
				else{
					fprintf(stderr, "%s\n","Illegal free request" );

				}
			}
		}
		else{
			fprintf(stderr, "%s\n","Illegal free request : specify the pointer to free!" );
		}
		return 1;
	}
	else if( strcmp(args[0],"print") == 0){
			printf("print request\n");
			print_queue(free_list);
			printf("\n");
			return 1;

	}
	else if( strcmp(args[0],"exit") == 0){
		return 0;
	}
	else{
		printf("%s\n","Not a valid command! Type help for more info!!" );
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
	free_list = initialize_queue();
	pos = 0;
	interface();
	return 0;
}