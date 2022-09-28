/**
 * @file chained_queue.c
 * @author Achiever&
 * @brief Implement chained data structure queues
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "../include/queue_chained.h"

#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


extern int errno;


static inline bool is_empty_queue(struct linkQueue cq);


static inline bool is_empty_queue(struct linkQueue cq)
{
        return (cq.front == cq.rear);
}



/*���ɶ���,��������cqΪ����ָ��Ľṹ��
����˼·��ʹ��βָ�봴��һ���ڵ�ṹ�壬ʹͷβ��ȣ����õ�βָ����ѭ�������µĽڵ�
��Ϊ���ڵ㸳ֵ�봴����Ԫ��д����һ��Ϊ����βָ�벻ָ��β�ڵ㣬��ʱ��p��������һ���ڵ�
���ڵ㸳ֵ���Ǵ�1���ӣ���������

The queue is generated, and cq in the function body is the struct of the queue pointer
The general idea: use the tail pointer to create a node structure that makes the head and tail equal, 
and use the tail pointer to loop to build new nodes
Because assigning a value to a node is written together with the creation of a new element, 
to avoid the tail pointer not pointing to the tail node, p is temporarily used to store the previous node
Assign a value to a node only from 1 overlay, with subsequent changes*/
extern struct linkQueue init_queue(int len)
{
        struct linkQueue cq;
        cq.rear = (struct qnode*)malloc(sizeof(struct qnode));
        cq.front = cq.rear;
        struct qnode* p = cq.rear;
        for (int i = 0; i < len; ++i)
        {
                cq.rear->data = i+1;
                cq.rear->next = (struct qnode*)malloc(sizeof(struct qnode));
                // printf("%d ", i+1);
                p = cq.rear;
                cq.rear = cq.rear->next;
        }
        cq.rear = p;
        cq.rear->next = NULL;   //��βָ���next��ֵΪ��(Assign the next value of the trailing pointer to null)
        return cq;

}



/*����βָ���������µĽڵ㣬����������ֵe���и�ֵ
A new node is created using the tail pointer and the passing value e is assigned*/
extern int enQueue (struct linkQueue cq, elemType e)
{
        cq.rear->next = (struct qnode*)malloc(sizeof(struct qnode));
        cq.rear = cq.rear->next;
        cq.rear->data = e;
        return 1;
}



/*��ͷָ������ƶ������ͷſռ�
Move the head pointer backward and free up space*/
extern void deQueue (struct linkQueue cq)
{
        struct qnode * p;
        p = cq.front;
        if(cq.front->next)
                cq.front = cq.front->next;
        else
                cq.front = NULL;
        free(p);
}



/*ѭ��������ýڵ��ֵ��Ϊ���򳤶ȼ�1������������ȴ���
Loop, if the value of the node is not empty, the length is increased by 1, 
to avoid the error of the empty linked list length*/
extern size_t get_queue_length(struct linkQueue cq)
{
        int i = 0;
        struct qnode* p = cq.front;
        for(; ; )
        {
                if(p->data)
                {
                        i++;
                        p = p->next;
                }
                if(p == NULL)
                {
                        return i;
                }
        }
}




extern elemType get_front_elem(struct linkQueue cq)
{
        return cq.front->data;
}


extern elemType get_back_elem(struct linkQueue cq)
{
        return cq.rear->data;
}


/*ѭ���ͷſռ�
Cycle to free up space*/
extern void clear_chaQueue(struct linkQueue cq)
{
        struct qnode* q = cq.front;
        struct qnode* p;
        do
        {
                p = q->next;
                free(q);
                q = p;
        } while (q->next);

        cq.front = NULL;
        cq.rear = NULL;
        p = NULL;
        q = NULL;
}