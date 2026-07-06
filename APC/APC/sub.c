#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1=tail1,*temp2=tail2;
    int barrow=0;
    int digit1,digit2;
    while(temp1!=NULL){
        digit1=temp1->data-barrow;
        if(temp2!=NULL){
            digit2=temp2->data;
            temp2=temp2->prev;
        }else{
            digit2=0;
        }
        if(digit1<digit2){
            digit1+=10;
            barrow=1;
        }else{
            barrow=0;
        }
        insert_first(headR,tailR,digit1-digit2);
        temp1=temp1->prev;
        //temp2=temp2->prev;
    }
        remove_pre_zeros(headR);
}
