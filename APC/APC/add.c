#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry=0;
    //print_list(tail1);
    while(tail1!=NULL || tail2!=NULL){
        int sum=carry;
        if(tail1!=NULL){
            sum+=tail1->data;
            tail1=tail1->prev;
        }
        if(tail2!=NULL){
            sum+=tail2->data;
            tail2=tail2->prev;
        }
        carry=sum/10;
        sum=sum%10;
        insert_first(headR,tailR,sum);
    }
    if(carry){
        insert_first(headR,tailR,carry);
    }
    remove_pre_zeros(headR);

}
