/* This is Tutano's simple queue data structure. 
 * Copyright (C) 2020 Felipe V. Calderan <fvcalderan@gmail.com>
 * Copyright (C) 2020 Natália V. Calderan <nvcalderan@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include "queue.h"
// this is a standard implementation of an array queue (not linked list)
// it supports VECTOR2 as data type for the items

void q_initialize(QUEUE *queue)
{
	queue->front = -1;
	queue->rear = -1;
	queue->size = -1;
}

int q_isempty(QUEUE *queue)
{
    return queue->size<0;
}

int q_isfull(QUEUE *queue)
{
    return queue->size == QUEUESIZE;
}

void q_push(QUEUE *queue, VECTOR2 value)
{
    if(queue->size < QUEUESIZE)
    {
        if(queue->size < 0)
        {
            queue->queue[0] = value;
            queue->front = queue->rear = 0;
            queue->size = 1;
        }
        else if(queue->rear == QUEUESIZE - 1)
        {
            queue->queue[0] = value;
            queue->rear = 0;
            queue->size++;
        }
        else
        {
            queue->queue[queue->rear+1] = value;
            queue->rear++;
            queue->size++;
        }
    }
}

VECTOR2 q_pop(QUEUE *queue)
{
    if (queue->size >= 0)
    {
        queue->size--;
        queue->front++;
        return queue->queue[queue->front-1];
    }
    VECTOR2 nil; nil.x = 0; nil.y = 0;
    return nil;
}

VECTOR2 q_front(QUEUE *queue)
{
    return queue->queue[queue->front];
}

// debugging only
void q_display(QUEUE *queue)
{
    int i;
    if(queue->rear >= queue->front)
    {
        for(i = queue->front; i <= queue->rear; i++)
        {
            printf("(%d, %d)\n",queue->queue[i].x, queue->queue[i].y);
        }
    }
    else
    {
        for(i = queue->front; i < QUEUESIZE; i++)
        {
            printf("(%d, %d)\n",queue->queue[i].x, queue->queue[i].y);
        }
        for(i = 0; i <= queue->rear; i++)
        {
            printf("(%d, %d)\n",queue->queue[i].x, queue->queue[i].y);
        }
    }
}
