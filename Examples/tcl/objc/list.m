#import "list.h"

@implementation List

// Create a new list

+new {
  self = [super alloc];
  return [self init];
}

// Initialize the list to a new state

-init {
  int i;
  nitems = 0;
  maxitems = 10;
  items = (id *) malloc(maxitems*sizeof(id));
  for (i = 0; i < maxitems; i++)
    items[i] = 0;
  return self;
}

// Destroy the list.   Does not destroy the objects in the list!

- free {
  free(items);
  [super free];
}

// Expand the list 

-(void) expand {
  int i;
  maxitems = 2*maxitems;
  items = (id *) realloc(items,maxitems*sizeof(id));
};

// Append a new item to the list

-(void) append: (id) item {
  if (nitems == maxitems) [self expand];
  items[nitems] = item;
  nitems++;
}

// Insert a new item to the list

-(void) insert: (id) item : (int) pos {
  int i;
  if (pos < 0) pos = 0;
  if (pos > nitems) pos = nitems;
  if (nitems == maxitems) [self expand];
  for (i = nitems; i > pos; i++) 
    items[i] = items[i-1];
  items[pos] = item;
  nitems++;
}

// Delete an item from the list

-remove: (int) pos {
  int i;
  id  it;
  if (pos < 0) return nil;
  if (pos >= nitems) return nil;
  it = items[pos];
  for (i = pos; i < nitems-1; i++)
    items[i] = items[i+1];
  nitems--;
  return it;
}

// Replace an item in the list. Returns the old item

-replace: (id) item : (int) pos {
  id i;
  i = items[pos];
  items[pos] = item;
  return i;
}

// Get an item from the list

-get: (int) i {
  if (i < 0) return nil;
  if (i >= nitems) return nil;
  return items[i];
}

// Find an item in the list.

-(int) index: obj {
  int i;
  for (i = 0; i < nitems; i++)
    if (items[i] == obj) return i;
  return -1;
}

// Return the length of the list

-(int) len {
  return nitems;
}
@end


