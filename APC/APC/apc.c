#include "apc.h"

// Function definitions
	int is_number(char *str){
		int i=0;
        if(str[0]=='+' || str[0]=='-'){
            i=1;;
        }
		if(str[i]=='\0'){
			return 0;
		}
		while(str[i]!='\0'){
			if(!isdigit(str[i])){
				return 0;
			}
			i++;
		}
		return 1;
	}
	int cla_validation(int argc, char *argv[]){
		if(argc!=4){
            printf("Error : Invalid arguments\n");
			return FAILURE;
		}
        if(strlen(argv[2]) != 1){
            printf("Error : Operator must be single character\n");
            return FAILURE;
        }
		if(!is_number(argv[1]) || !is_number(argv[3])){
            printf("Error : Operand 1 or 2 must contain numeric charactes\n");
			return FAILURE;
		}
		if(argv[2][0]!='+'&& argv[2][0]!='-' && argv[2][0]!='x' && argv[2][0]!='X' && argv[2][0]!='/'){
            printf("Error : Invalid operator '%c'. Supported operators are +, -, x, /.\n", argv[2][0]);
			return FAILURE;
		}
        if(argv[1][0]=='\0'){
            printf("Error : Operand  1 is missing digits\n");
            return FAILURE;
        }
        if(argv[3][0]=='\0'){
            printf("Error : Operand  2 is missing digits\n");
            return FAILURE;   
        }
        return SUCCESS;
	}

//create_list//
void create_list(char *op,node **head,node **tail){
    int i=0;
    if(op[0]=='+' || op[0]=='-'){
        i=1;
    }
    while(op[i]!='\0'){
        insert_last(head,tail,op[i]-'0');
        i++;
    }
}


//insert_first//
int insert_first(node **head, node **tail, int data){
    node *new=malloc(sizeof(node));
    if(new==NULL){
        return FAILURE;
    }
    if(*head==NULL){
        new->data=data;
        new->prev=NULL;
        new->next=NULL;
        *head=new;
        *tail=new;
        return SUCCESS;
    }else{
        new->data=data;
        new->prev=NULL;
        new->next=*head;
        (*head)->prev=new;
        *head=new;
        return SUCCESS;
    }
}

//insert_last//
int insert_last(node **head, node **tail, int data){
    node *new=malloc(sizeof(node));
    if(new==NULL){
        return FAILURE;
    }
    if(*head==NULL){
        new->data=data;
        new->prev=NULL;
        new->next=NULL;
        *head=new;
        *tail=new;
        return SUCCESS;
    }else{
        new->data=data;
        new->next=NULL;
        new->prev=*tail;
        (*tail)->next=new;
        *tail=new;
        return SUCCESS;
    }
}


//delete_first//
int dl_delete_first(node **head, node **tail)
{
    if(*head==NULL){
        return FAILURE;
    }
    if(*head==*tail){
        free(*head);
        *head=NULL;
        *tail=NULL;
        return SUCCESS;
    }else{
        *head=(*head)->next;
        free((*head)->prev);
        (*head)->prev=NULL;
        return SUCCESS;
    }
}


//delete_list//
int delete_list(node **head, node **tail){
        while((*head)!=NULL){
            dl_delete_first(head,tail);
        }
        return SUCCESS;
}

//print_list//
void print_list(node *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
	    }
        printf("\n");
    }
}

//list_len//
int list_len(node *head){
    int count=0;
    while(head!=NULL){
        head=head->next;
        count++;
    }
    return count;
}

//remove_pre_zero//
void remove_pre_zeros(node **head){
    while(*head!=NULL && (*head)->data==0 && (*head)->next!=NULL){
        node *temp=*head;
        *head=(*head)->next;
        (*head)->prev=NULL;
        free(temp);
    }
}

//compare_list//
int compare_list(node *head1, node *head2){
    int list1=list_len(head1);
    int list2=list_len(head2);

    if(list1>list2)
        return OPERAND1;
    if(list1<list2)
        return OPERAND2;
    node *temp1=head1,*temp2=head2;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->data>temp2->data){
            return OPERAND1;
        }
        if(temp2->data>temp1->data){
            return OPERAND2;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    return SAME;
    
}