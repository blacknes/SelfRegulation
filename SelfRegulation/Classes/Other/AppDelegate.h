//
//  AppDelegate.h
//  SelfRegulation
//
//  Created by ra on 3/25/16.
//  Copyright © 2016 nill. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

#import "LoginViewController.h"

#define THIS_FILE  "AppDelegate.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;


//

- (BOOL) startNatUA2:(NSString*) peer;

@end

