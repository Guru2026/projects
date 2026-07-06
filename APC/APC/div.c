#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    if(head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf("Error : Division by Zero\n");
        return;
    }

    if(compare_list(head1, head2) == OPERAND2)
    {
        insert_last(headR, tailR, 0);
        return;
    }

    node *headopr1 = NULL;
    node *tailopr1 = NULL;
    node *temp = head1;

    /* Find tail of divisor */
    node *tail2 = head2;
    while(tail2->next != NULL)
    {
        tail2 = tail2->next;
    }

    while(temp != NULL)
    {
        /* Bring down next digit */
        insert_last(&headopr1, &tailopr1, temp->data);

        remove_pre_zeros(&headopr1);

        if(headopr1 == NULL)
        {
            insert_last(&headopr1, &tailopr1, 0);
        }
        else
        {
            tailopr1 = headopr1;
            while(tailopr1->next != NULL)
            {
                tailopr1 = tailopr1->next;
            }
        }

        int sub_count = 0;
        int cmp;

        while((cmp = compare_list(headopr1, head2)) == OPERAND1 ||
               cmp == SAME)
        {
            node *headsr = NULL;
            node *tailsr = NULL;

            /* remainder = remainder - divisor */
            subtraction(tailopr1, tail2, &headsr, &tailsr);

            delete_list(&headopr1, &tailopr1);

            headopr1 = headsr;
            tailopr1 = tailsr;

            remove_pre_zeros(&headopr1);

            if(headopr1 == NULL)
            {
                insert_last(&headopr1, &tailopr1, 0);
            }
            else
            {
                tailopr1 = headopr1;
                while(tailopr1->next != NULL)
                {
                    tailopr1 = tailopr1->next;
                }
            }

            sub_count++;
        }

        insert_last(headR, tailR, sub_count);

        temp = temp->next;
    }

    remove_pre_zeros(headR);

    if(*headR == NULL)
    {
        insert_last(headR, tailR, 0);
    }

    delete_list(&headopr1, &tailopr1);
}