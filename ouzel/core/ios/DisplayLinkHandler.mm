// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#import "DisplayLinkHandler.h"
#include "utils/Log.hpp"

@implementation DisplayLinkHandler

-(id)initWithRenderDevice:(ouzel::graphics::RenderDevice*)initRenderDevice andVerticalSync:(bool)initVerticalSync
{
    if (self = [super init])
    {
        rendererDevice = initRenderDevice;
        verticalSync = initVerticalSync;
        running = true;

        if (verticalSync)
        {
            displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(draw:)];
            if (!displayLink)
            {
                ouzel::Log(ouzel::Log::Level::ERR) << "Failed to create display link";
                return nil;
            }
            [displayLink setFrameInterval:1.0f];
        }

        runLock = [[NSConditionLock alloc] initWithCondition:0];
        renderThread = [[NSThread alloc] initWithTarget:self selector:@selector(runThread) object:nil];
        [renderThread setName:@"Render"];
        [renderThread start];
    }

    return self;
}

-(void)dealloc
{
    [runLock lockWhenCondition:1];
    [runLock unlock];
    [runLock release];
    [displayLink invalidate];
    [displayLink release];
    [renderThread release];
    [super dealloc];
}

-(void)draw:(__unused CADisplayLink*)sender
{
    @autoreleasepool
    {
        rendererDevice->process();
    }
}

-(void)runThread
{
    [runLock lock];

    if (verticalSync)
    {
        runLoop = [NSRunLoop currentRunLoop];
        [displayLink addToRunLoop:runLoop forMode:NSDefaultRunLoopMode];
        [runLoop run];
    }
    else
    {
        while (running) [self draw:nil];
    }

    [runLock unlockWithCondition:1];
}

-(void)stop
{
    running = false;
    if (runLoop) CFRunLoopStop([runLoop getCFRunLoop]);
}

@end
