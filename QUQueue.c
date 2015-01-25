//
//  QUQueue.c
//  Queue
//
//  Created by renwei on 14-5-15.
//  Copyright (c) 2014年 YY. All rights reserved.
//

#include <stdlib.h>
#include "QUQueue.h"

void QUQueueInit(QUQueueContext* queue, int cap)
{
    queue->releaseMethod = NULL;
    queue->retainMethod = NULL;
    queue->autoReleaseMethod = NULL;
    queue->expandedSetp = 8;
    queue->capacity = cap;
    queue->size = 0;
    queue->first = queue->last = (QUQueueQueueBlock*)malloc(sizeof(QUQueueQueueBlock));
    queue->last->data = NULL;
    
    for (int i = 0; i < cap; i++) {
        queue->last->next = (QUQueueQueueBlock*)malloc(sizeof(QUQueueQueueBlock));
        queue->last = queue->last->next;
        queue->last->data = NULL;
    }
    queue->last->next = queue->first;
    queue->last = queue->first;
}

void QUQueueExpandCapacity(QUQueueContext* queue)
{
    QUQueueQueueBlock* temp = queue->last;
    for (int i = 0; i < queue->expandedSetp; i++) {
        temp->next = (QUQueueQueueBlock*)malloc(sizeof(QUQueueQueueBlock));
        temp->data = NULL;
        temp = temp->next;
    }
    temp->next = queue->first;
}

void QUQueueAddObject(QUQueueContext* queue, const void* value)
{
    if (queue->retainMethod && value) {
        queue->retainMethod(queue, value);
    }
    if (queue->last->next == queue->first) {
        QUQueueExpandCapacity(queue);
    }
    queue->last->data = value;
    queue->last = queue->last->next;
    queue->size++;
}

const void* QUQueueRemoveFirstObject(QUQueueContext* queue)
{
    const void* pointer = queue->first->data;
    queue->first->data = NULL;
    queue->first = queue->first->next;
    queue->size--;
    if (queue->autoReleaseMethod && pointer) {
        queue->autoReleaseMethod(queue, pointer);
    }
    return pointer;
}

int QUQueueGetSize(QUQueueContext* queue)
{
    return queue->size;
}

int QUQueueIsEmpty(QUQueueContext* queue)
{
    return queue->first == queue->last;
}

const void* QUQueueGetFirstObject(QUQueueContext* queue)
{
    return queue->first->data;
}

void QUQueueRelease(QUQueueContext* queue)
{
    QUQueueQueueBlock* temp = queue->first;
    QUQueueQueueBlock* temp2 = queue->first;
    
    while (temp->next != queue->first) {
        if (queue->releaseMethod && temp->data) {
            temp->data = queue->releaseMethod(queue, temp->data);
        }
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if (queue->releaseMethod && temp->data) {
        queue->releaseMethod(queue, temp->data);
    }
    free(temp);
    queue->first = NULL;
    queue->last = NULL;
    queue->capacity = 0;
    queue->size  = 0;
    queue->expandedSetp = 0;
}

void QUQueueRemoveAllObject(QUQueueContext* queue)
{
    while (queue->last != queue->first) {
        if (queue->first->data && queue->releaseMethod) {
            queue->first->data = queue->releaseMethod(queue, queue->first->data);
        }
        queue->first = queue->first->next;
    }
    queue->size = 0;
}