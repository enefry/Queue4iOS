//
//  NSQueue.h
//  Queue
//
//  Created by renwei on 14-5-15.
//  Copyright (c) 2014年 YY. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface NSQueue : NSObject {
}

- (instancetype)initWithCapacity:(int)capacity;

- (void)addObject:(id)obj;

- (id)firstObject;

- (id)removeFirstObject;

- (int)size;

- (BOOL)isEmpty;

- (void)removeAllObject;

@end
