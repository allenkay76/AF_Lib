#include "AF_Window_Cocoa.h"
#include <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@property (strong, nonatomic) NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
    NSLog(@"Create OSX Window\n");

    NSRect frame = NSMakeRect(0, 0, 800, 600);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
    self.window = [[NSWindow alloc] initWithContentRect:frame
                                               styleMask:style
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];
    [self.window setTitle:@"AF_Lib OSX"];
    [self.window makeKeyAndOrderFront:nil];
    [self.window setDelegate:self];
    // Set the background color to white
    [self.window setBackgroundColor:[NSColor whiteColor]];
    
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end

@implementation AF_Window_Cocoa

+ (void)CreateOSXWindow {
    AppDelegate *delegate = [[AppDelegate alloc] init];
    NSApplication *app = [NSApplication sharedApplication];
    [app setDelegate:delegate];
    [app run];
}

@end
