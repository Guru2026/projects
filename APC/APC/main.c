#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;


    // Validation
	if(cla_validation(argc,argv)==FAILURE){
		printf("Error : Usage - ./a.out <oprand1> <operator> <operand2>\n");	
		return FAILURE;
	}

    // Create 2 lists 	of operands

	create_list(argv[1],&head1,&tail1);
	create_list(argv[3],&head2,&tail2);


    // Remove pre zeros

    char oper = argv[2][0];
	int sign1=1,sign2=1;
	if(argv[1][0]=='-'){
		sign1=-1;
	}
	if(argv[3][0]=='-'){
		sign2=-1;
	}

    switch(oper)
    {
	case '+':
	{
		if(sign1==sign2){
			if(sign1==-1){
				printf("-");
			}
	    addition(tail1, tail2, &headR, &tailR);
		print_list(headR);
		}else{
			int oder=compare_list(head1,head2);
			if(oder==SAME){
				printf("0\n");
			}
			else if(oder==OPERAND1){
				if(sign1==-1){
					printf("-");
				}
				subtraction(tail1,tail2,&headR,&tailR);
				print_list(headR);
			}else if(oder==OPERAND2){
				if(sign2==-1){
					printf("-");
				}
				subtraction(tail2,tail1,&headR,&tailR);
				print_list(headR);
			}
		}
		break;
	}
	
	case '-':
	{
	if(sign1!=sign2){
		if(sign1==-1){
			printf("-");
		}
		addition(tail1,tail2,&headR,&tailR);
		print_list(headR);
	}else{
			int oder=compare_list(head1,head2);
			if(oder==SAME){
				printf("0\n");
			}
			else if(oder==OPERAND1){
				if(sign1==-1){
					printf("-");
				}
				subtraction(tail1,tail2,&headR,&tailR);
				print_list(headR);
			}else if(oder==OPERAND2){
				if(sign1==1){
					printf("-");
				}
				subtraction(tail2,tail1,&headR,&tailR);
				print_list(headR);
			}
		}
		break;
	}
	case 'x':
	case 'X':
	{
		multiplication(tail1,tail2,&headR,&tailR);
		remove_pre_zeros(&headR);
		if(sign1!=sign2){
			printf("-");
		}
		print_list(headR);
	    break;
	}
	case '/':
	{
		remove_pre_zeros(&head1);
		remove_pre_zeros(&head2);
		division(head1,head2,&headR,&tailR);
		if(sign1!=sign2){
			printf("-");
		}
		print_list(headR);
	    break;
	}
	default:
	    printf("Invalid operator\n");
    }
}

