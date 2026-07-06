#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2=tail2;
    int count=0;
    while(temp2!=NULL){
        node *headar1=NULL;
        node *tailar1=NULL;

        node *temp1=tail1;
        int carry=0;
        while(temp1!=NULL){
            int mul=temp1->data * temp2->data+carry;
            carry=mul/10;
            insert_first(&headar1,&tailar1,mul%10);

            temp1=temp1->prev;
        }
        if(carry){
            insert_first(&headar1,&tailar1,carry);
        }
        for(int i=0;i<count;i++){
            insert_last(&headar1,&tailar1,0);
        }
        if(*headR==NULL){
            *headR=headar1;
            *tailR=tailar1;
        }else{
            node *headar2=NULL;
            node *tailar2=NULL;

            addition(*tailR,tailar1,&headar2,&tailar2);

            *headR=headar2;
            *tailR=tailar2;
        }
        temp2=temp2->prev;
        count++;
    }

}
