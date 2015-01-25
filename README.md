# Queue4iOS
A Queue For iOS write in c and objective-c

A queue for iOS ,make it easy to use 

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
