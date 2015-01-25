//
//  NSQueue.m
//  Queue
//
//  Created by renwei on 14-5-15.
//  Copyright (c) 2014年 YY. All rights reserved.
//

#import "NSQueue.h"
#import <objc/message.h>
#include "QUQueue.h"

const void* QUQueueBlockManagerMethod_ObjectiveCRetain(QUQueueContext* queue, const void* value)
{
    CFRetain(value);
    return value;
}
const void* QUQueueBlockManagerMethod_ObjectiveCRelease(QUQueueContext* queue, const void* value)
{
    CFRelease(value);
    return NULL;
}

const void* QUQueueBlockManagerMethod_ObjectiveCAutoRelease(QUQueueContext* queue, const void* value)
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7) {
        CFAutorelease(value);
    } else {
        static SEL autoReleaseSelector = NULL;
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            autoReleaseSelector = NSSelectorFromString(@"autorelease");
        });
        objc_msgSend((__bridge id)(value), autoReleaseSelector);
    }
    return value;
}

@implementation NSQueue {
    QUQueueContext _context;
}
- (instancetype)init
{
    return [self initWithCapacity:16];
}

- (instancetype)initWithCapacity:(int)capacity
{
    if (self = [super init]) {
        QUQueueInit(&_context, capacity);
        _context.releaseMethod = QUQueueBlockManagerMethod_ObjectiveCRelease;
        _context.autoReleaseMethod = QUQueueBlockManagerMethod_ObjectiveCAutoRelease;
        _context.retainMethod = QUQueueBlockManagerMethod_ObjectiveCRetain;
    }
    return self;
}

- (void)addObject:(id)obj
{
    QUQueueAddObject(&_context, ((__bridge void*)obj));
}

- (id)firstObject
{
    return (__bridge id)(QUQueueGetFirstObject(&_context));
}

- (id)removeFirstObject
{
    return (__bridge id)(QUQueueRemoveFirstObject(&_context));
}

- (int)size
{
    return QUQueueGetSize(&_context);
}

- (BOOL)isEmpty
{
    return QUQueueIsEmpty(&_context);
}

- (void)dealloc
{
    QUQueueRelease(&_context);
}
-(void)removeAllObject{
    QUQueueRemoveAllObject(&_context);
}
@end


