//
//  UIViewWindow.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "EAGLWindow.hpp"

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

d3::EAGLWindow * uiviewwindow_instance = nullptr;
GLint width;
GLint height;

@interface D3EAGLView : UIView {
    CAEAGLLayer * eagl_layer;
    EAGLContext * eagl_context;
    GLuint color_render_buffer;
    GLuint depth_render_buffer;
    GLuint framebuffer;
}

@end

@implementation D3EAGLView
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];

        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
        glGenRenderbuffers(1, &color_render_buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, color_render_buffer);
        [eagl_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eagl_layer];
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_render_buffer);
        

        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
        
        glGenRenderbuffers(1, &depth_render_buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depth_render_buffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_render_buffer);
        
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
        if(status != GL_FRAMEBUFFER_COMPLETE) {
            NSLog(@"failed to make complete framebuffer object %x", status);
        }
    }
    return self;
}

- (void)dealloc {
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)setupLayer {
    eagl_layer = (CAEAGLLayer *)self.layer;
    eagl_layer.opaque = YES;
}

- (void)setupContext {
    eagl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!eagl_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:eagl_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupDisplayLink {
    CADisplayLink * display_link = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [display_link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)render:(CADisplayLink *)display_link {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    uiviewwindow_instance->getApplication()->render();
    uiviewwindow_instance->getApplication()->idle();
    
    glFinish();

    glBindRenderbuffer(GL_RENDERBUFFER, color_render_buffer);
    [eagl_context presentRenderbuffer:GL_RENDERBUFFER];
}

@end

D3EAGLView * eagl_view_instance = nil;
UIWindow * eagl_window_instance = nil;

namespace d3 {
    EAGLWindow::EAGLWindow(Application * application) : Window(application)
    {
        uiviewwindow_instance = this;
        
        /* Create view */
        eagl_view_instance = [[D3EAGLView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        
        /* Create window and attach view through controller */
        eagl_window_instance = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        UIViewController * view_controller = [[UIViewController alloc] init];
        [view_controller setView:eagl_view_instance];
        [eagl_window_instance setRootViewController:view_controller];
    }
    
    void EAGLWindow::setupContext()
    {
        
    }
    
    unsigned EAGLWindow::getWidth()
    {
        return width;
    }
    
    unsigned EAGLWindow::getHeight()
    {
        return height;
    }
    
    float EAGLWindow::getTimerValue()
    {
        return CACurrentMediaTime();
    }
    
    void EAGLWindow::runLoop()
    {
        [eagl_view_instance setupDisplayLink];
    }
    
    void * EAGLWindow::getSystemObject()
    {
        return (__bridge void*)eagl_window_instance;
    }
}