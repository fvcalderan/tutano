/* This is Tutano's header for simple queue data structure. 
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

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include "customtypes.h"

#define QUEUESIZE MAPSIZE*MAPSIZE

typedef struct {
    VECTOR2 queue[QUEUESIZE];
    int front;
    int rear;
    int size;
} QUEUE;

void q_initialize(QUEUE *queue);
int q_isempty(QUEUE *queue);
int q_isfull(QUEUE *queue);
void q_push(QUEUE *queue, VECTOR2 value);
VECTOR2 q_pop(QUEUE *queue);
VECTOR2 q_front(QUEUE *queue);
void q_display(QUEUE *queue);

#endif
