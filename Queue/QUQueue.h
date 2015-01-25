//
//  QUQueue.h
//  Queue
//
//  Created by renwei on 14-5-15.
//  Copyright (c) 2014年 YY. All rights reserved.
//

#ifndef Queue_QUQueue_h
#define Queue_QUQueue_h

typedef struct QUQueueContext QUQueueContext;
typedef struct QUQueueQueueBlock QUQueueQueueBlock;
typedef const void* (*QUQueueBlockManagerMethod)(QUQueueContext* queue, const void*);

/**
 *    队列块
 */
struct QUQueueQueueBlock {
    void* next; /** 下一个块指针 */
    const void* data; /** 存储的值 */
};

/**
 *    队列数据库
 */
struct QUQueueContext {
    QUQueueQueueBlock* first; /** 第一个数据的指针 */
    QUQueueQueueBlock* last; /** 第一个空闲数据的指针 */
    uint32_t capacity; /** 容量 */
    uint32_t size; /** 数据量 */
    uint32_t expandedSetp; /** 容量扩张因子 */
    QUQueueBlockManagerMethod retainMethod; /** 增加对对象的引用 */
    QUQueueBlockManagerMethod releaseMethod; /** 释放对象 */
    QUQueueBlockManagerMethod autoReleaseMethod; /** 自动释放对象 */
};
/**
 *  初始化队列
 *
 *  @param queue    队列
 *  @param capacity 容量
 */
void QUQueueInit(QUQueueContext* queue, int capacity);
/**
 *  向队尾添加数据
 *
 *  @param queue 队列
 *  @param value 数据
 */
void QUQueueAddObject(QUQueueContext* queue, const void* value);
/**
 *  从队列头移除数据
 *
 *  @param queue 队列
 *  @return 数据内容
 */
const void* QUQueueRemoveFirstObject(QUQueueContext* queue);
/**
 *  队列数据量
 *
 *  @param queue 队列
 *
 *  @return 数据量
 */
int QUQueueGetSize(QUQueueContext* queue);
/**
 *  队列是否为空
 *
 *  @param queue 队列
 *
 *  @return 是否为空(空为 1 否则为 0 )
 */
int QUQueueIsEmpty(QUQueueContext* queue);

/**
 *  获取第一个数据,不移除
 *
 *  @param queue 队列
 */
const void* QUQueueGetFirstObject(QUQueueContext* queue);

/**
 *  释放队列
 *
 *  @param queue 队列
 */
void QUQueueRelease(QUQueueContext* queue);

/**
 *  删除队列中的说有数据,容量不变
 *
 *  @param queue 队列
 */
void QUQueueRemoveAllObject(QUQueueContext* queue);

#endif /* ifndef Queue_QUQueue_h */
