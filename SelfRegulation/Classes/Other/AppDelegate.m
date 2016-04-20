//
//  AppDelegate.m
//  SelfRegulation
//
//  Created by ra on 3/25/16.
//  Copyright © 2016 nill. All rights reserved.
//

#import "AppDelegate.h"

#import <pjlib.h>
#import <pjsua.h>
#import <pj/log.h>
#include "pjsua_app.h"
#include "nill_acc_config.h"
#include "pjsua_app_config.h"


#define KEEP_ALIVE_INTERVAL 600


@interface AppDelegate ()


@end

@implementation AppDelegate

extern pj_bool_t app_restart;

int app_setId(char *pj_optarg);
int app_setRegistrar(char *pj_optarg);
int app_setProxy(char *pj_optarg);
int app_setUserName(char *pj_optarg);
int app_setPassword(char *pj_optarg);

static pjsua_app_cfg_t  app_cfg;
static bool             isShuttingDown;

static char           **restartArgv;
static int              restartArgc;


static void displayMsg(const char *msg)
{
    NSString *str = [NSString stringWithFormat:@"%s", msg];
    dispatch_async(dispatch_get_main_queue(),^{
        
        NSLog(@"---displayMsg----%@",str);
        
    });
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    
    // You should change 192.168.43.106 to the IP of your own Mac
//    startPjsip("10005", "192.168.12.122");
//    makeCall("sip:192.168.12.126:5080");
    
    
    return YES;
}

- (BOOL) startNatUA2:(NSString*) peer
{
    // Start pjsua thread
    [NSThread detachNewThreadSelector:@selector(startAppPJSua:) toTarget:self withObject:peer];
    return true;
}


// pjsua start
- (void)startAppPJSua:(id) arg
{
    
    pj_status_t status;
    const char **argv = pjsua_app_def_argv;
    int argc = PJ_ARRAY_SIZE(pjsua_app_def_argv) -1;
    
    if (restartArgc) {
        app_cfg.argc = restartArgc;
        app_cfg.argv = restartArgv;
    } else {
        app_cfg.argc = argc;
        app_cfg.argv = (char**)argv;
    }
    
    app_default_cfg();
    
    NSString *callerId = [NSString stringWithFormat:@"sip:%@@%@",@"1004",@"192.168.12.122"];
    app_setId((char *) [callerId UTF8String]);
    
    app_setRegistrar((char *) [@"192.168.12.122" UTF8String]);
    app_setProxy((char *)[@"192.168.12.122" UTF8String]);
    app_setUserName((char *)[@"1004" UTF8String]);
    app_setPassword((char *)[@"123456" UTF8String]);
    
    
    isShuttingDown = false;
    displayMsg("Starting..");
    
    
    while (!isShuttingDown) {
        status = pjsua_app_init(&app_cfg);
        if (status != PJ_SUCCESS) {
            char errmsg[PJ_ERR_MSG_SIZE];
            pj_strerror(status, errmsg, sizeof(errmsg));
            displayMsg(errmsg);
            pjsua_app_destroy();
            return;
        }
        
        status = pjsua_app_run(PJ_TRUE);
        if (status != PJ_SUCCESS) {
            char errmsg[PJ_ERR_MSG_SIZE];
            pj_strerror(status, errmsg, sizeof(errmsg));
            displayMsg(errmsg);
        }
        
    }
    
   
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    
    // keep pjsua thread alive
    [[UIApplication sharedApplication] setKeepAliveTimeout:KEEP_ALIVE_INTERVAL handler: ^{
        //[app performSelectorOnMainThread:@selector(keepAlive) withObject:nil waitUntilDone:YES];
        [self keepAlive];
    }];
    
}

// keep alive
- (void)keepAlive {
    static pj_thread_desc a_thread_desc;
    static pj_thread_t *a_thread;
    int i;
    
    if (!pj_thread_is_registered()) {
        pj_thread_register("ipjsua", a_thread_desc, &a_thread);
    }
    
    /* Since iOS requires that the minimum keep alive interval is 600s,
     * application needs to make sure that the account's registration
     * timeout is long enough.
     */
    for (i = 0; i < (int)pjsua_acc_get_count(); ++i) {
        if (pjsua_acc_is_valid(i)) {
            pjsua_acc_set_registration(i, PJ_TRUE);
        }
    }
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    // Saves changes in the application's managed object context before the application terminates.
    [self saveContext];
}

#pragma mark - Core Data stack

@synthesize managedObjectContext = _managedObjectContext;
@synthesize managedObjectModel = _managedObjectModel;
@synthesize persistentStoreCoordinator = _persistentStoreCoordinator;

- (NSURL *)applicationDocumentsDirectory {
    // The directory the application uses to store the Core Data store file. This code uses a directory named "com.rhoads.SelfRegulation" in the application's documents directory.
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

- (NSManagedObjectModel *)managedObjectModel {
    // The managed object model for the application. It is a fatal error for the application not to be able to find and load its model.
    if (_managedObjectModel != nil) {
        return _managedObjectModel;
    }
    NSURL *modelURL = [[NSBundle mainBundle] URLForResource:@"SelfRegulation" withExtension:@"momd"];
    _managedObjectModel = [[NSManagedObjectModel alloc] initWithContentsOfURL:modelURL];
    return _managedObjectModel;
}

- (NSPersistentStoreCoordinator *)persistentStoreCoordinator {
    // The persistent store coordinator for the application. This implementation creates and returns a coordinator, having added the store for the application to it.
    if (_persistentStoreCoordinator != nil) {
        return _persistentStoreCoordinator;
    }
    
    // Create the coordinator and store
    
    _persistentStoreCoordinator = [[NSPersistentStoreCoordinator alloc] initWithManagedObjectModel:[self managedObjectModel]];
    NSURL *storeURL = [[self applicationDocumentsDirectory] URLByAppendingPathComponent:@"SelfRegulation.sqlite"];
    NSError *error = nil;
    NSString *failureReason = @"There was an error creating or loading the application's saved data.";
    if (![_persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:storeURL options:nil error:&error]) {
        // Report any error we got.
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        dict[NSLocalizedDescriptionKey] = @"Failed to initialize the application's saved data";
        dict[NSLocalizedFailureReasonErrorKey] = failureReason;
        dict[NSUnderlyingErrorKey] = error;
        error = [NSError errorWithDomain:@"YOUR_ERROR_DOMAIN" code:9999 userInfo:dict];
        // Replace this with code to handle the error appropriately.
        // abort() causes the application to generate a crash log and terminate. You should not use this function in a shipping application, although it may be useful during development.
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
    
    return _persistentStoreCoordinator;
}


- (NSManagedObjectContext *)managedObjectContext {
    // Returns the managed object context for the application (which is already bound to the persistent store coordinator for the application.)
    if (_managedObjectContext != nil) {
        return _managedObjectContext;
    }
    
    NSPersistentStoreCoordinator *coordinator = [self persistentStoreCoordinator];
    if (!coordinator) {
        return nil;
    }
    _managedObjectContext = [[NSManagedObjectContext alloc] initWithConcurrencyType:NSMainQueueConcurrencyType];
    [_managedObjectContext setPersistentStoreCoordinator:coordinator];
    return _managedObjectContext;
}

#pragma mark - Core Data Saving support

- (void)saveContext {
    NSManagedObjectContext *managedObjectContext = self.managedObjectContext;
    if (managedObjectContext != nil) {
        NSError *error = nil;
        if ([managedObjectContext hasChanges] && ![managedObjectContext save:&error]) {
            // Replace this implementation with code to handle the error appropriately.
            // abort() causes the application to generate a crash log and terminate. You should not use this function in a shipping application, although it may be useful during development.
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
    }
}

@end
