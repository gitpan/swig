// ----------------------------------------------------------------------
// List.h
//
// This implements a simple resizable list class.  The list can contain
// any valid Objective-C object.
// ----------------------------------------------------------------------

#import <objc/Object.h>

@interface List : Object {
     int   nitems;                  // Number of items in the list
     int   maxitems;                // Maximum number of items
     id   *items;                   // Array holding the items
}

//-------------------------  List methods --------------------------

// Create a new list
+ new;

// Destroy the list
- free;

// Append a new item to the list
- (void) append: (id) item;

// Insert an item in the list
- (void) insert: (id) item : (int) pos;

// Replace an item in the tree (returns old item)
-  replace: (id) item : (int) pos;

// Delete an item from the list
-  remove: (int) pos;

// Get an item from the list
- get: (int) i;

// Find an item in the list and return its index
- (int) index: obj;

// Get length of the list
- (int) len;

@end

