
/*******************************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 * 
 * Dave Beazley
 * 
 * Department of Computer Science        Theoretical Division (T-11)
 * University of Utah                    Los Alamos National Laboratory
 * Salt Lake City, Utah  84112           Los Alamos, New Mexico  87545
 * beazley@cs.utah.edu                   beazley@lanl.gov
 *
 * Copyright (c) 1995-1997
 * The University of Utah and the Regents of the University of California
 * All Rights Reserved
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that 
 * (1) The above copyright notice and the following two paragraphs
 * appear in all copies of the source code and (2) redistributions
 * including binaries reproduces these notices in the supporting
 * documentation.   Substantial modifications to this software may be
 * copyrighted by their authors and need not follow the licensing terms
 * described here, provided that the new terms are clearly indicated in
 * all files where they apply.
 * 
 * IN NO EVENT SHALL THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, THE 
 * UNIVERSITY OF UTAH OR DISTRIBUTORS OF THIS SOFTWARE BE LIABLE TO ANY
 * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHORS OR ANY OF THE ABOVE PARTIES HAVE BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, AND THE UNIVERSITY OF UTAH
 * SPECIFICALLY DISCLAIM ANY WARRANTIES,INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
 * THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *******************************************************************************/

#include "internal.h"

/*******************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/SWIG/RCS/hash.cxx,v 1.6 1997/07/14 03:57:32 beazley Exp $
 *
 * File : hash.cxx
 *
 * A very simple Hash table class.  Could probably make it more elegant with
 * templates, but templates are pure evil...
 *******************************************************************************/

#define INIT_SIZE   119

// -----------------------------------------------------------------------------
// Hash::Hash()
//
// Constructor.  Creates a new hash table. 
// 
// Inputs : None
//
// Output : New Hash object.
//
// Side Effects : None
// -----------------------------------------------------------------------------

Hash::Hash() {
  int i;
  hashsize = INIT_SIZE;
  hashtable = new Node *[hashsize];
  for (i = 0; i < hashsize; i++) {
    hashtable[i] = 0;
  }
  index = -1;
  current = 0;
}

// -----------------------------------------------------------------------------
// Hash::~Hash()
//
// Destructor.
// 
// Inputs : None
//
// Output : None
//
// Side Effects : Total destruction.
// -----------------------------------------------------------------------------

Hash::~Hash() {
  int   i;
  Node *n,*next;

  for (i = 0; i < hashsize; i++) {
    if (hashtable[i]) {
      n = hashtable[i];
      while (n) {
	next = n->next;
	delete n;
	n = next;
      }
    }
  }
  delete [] hashtable;
}

// -----------------------------------------------------------------------------
// int Hash::h1(const char *key)
// 
// Hashing function.
//
// Inputs : ASCII character string.
//
// Output : Hash table index.
//
// Side Effects : None
// -----------------------------------------------------------------------------

int Hash::h1(const char *key) {
  int h = 0;
  const char *c;

  c = key;
  while (*c) {
    h = (128*h + *c) % hashsize;
    c++;
  }
  return h;
}

// -----------------------------------------------------------------------------
// int Hash::add(const char *k, void *obj)
// 
// Adds a new object to the hash table.
//
// Inputs : 
//          k     = Hash key
//          obj   = Pointer to an object
//
// Output : 0 on success, -1 if item is already in hash table.
//
// Side Effects : 
//          Makes a new hash table entry.
// -----------------------------------------------------------------------------

int Hash::add(const char *k, void *obj) {

  int  hv;
  Node *n,*prev;

  hv = h1(k);                                  // Get hash value
  n = hashtable[hv];
  prev = n;
  while (n) {
    if (strcmp(n->key,k) == 0) return -1;      // Already in hash table
    prev = n;
    n = n->next;
  }

  // Safe to add this to the table

  n = new Node(k,obj,0);
  if (prev) prev->next = n;
  else hashtable[hv] = n;
  return 0;
}

// -----------------------------------------------------------------------------
// int Hash::add(const char *k, void *obj, void (*d)(void *))
// 
// Adds a new object to the hash table.  Allows additional specification of
// a callback function for object deletion.
//
// Inputs :
//          k       = Hash key
//          obj     = Object pointer
//          d       = Deletion function
//
// Output : 0 on success, -1 if item is already in hash table.
//
// Side Effects :
//          Adds an entry to the hash table
// -----------------------------------------------------------------------------

int Hash::add(const char *k, void *obj, void (*d)(void *)) {

  int  hv;
  Node *n,*prev;

  hv = h1(k);                                  // Get hash value
  n = hashtable[hv];
  prev = n;
  while (n) {
    if (strcmp(n->key,k) == 0) return -1;      // Already in hash table
    prev = n;
    n = n->next;
  }

  // Safe to add this to the table

  n = new Node(k,obj,d);
  if (prev) prev->next = n;
  else hashtable[hv] = n;
  return 0;
}

// -----------------------------------------------------------------------------
// void *Hash::lookup(const char *k)
// 
// Looks up a value in the hash table.  Returns a pointer to the object if found.
//
// Inputs : k   = key value
//
// Output : Pointer to object or NULL if not found.
//
// Side Effects : None
// -----------------------------------------------------------------------------

void *Hash::lookup(const char *k) {
  int hv;
  Node *n;

  hv = h1(k);                                // Get hash value
  n = hashtable[hv];

  while (n) {
    if (strcmp(n->key,k) == 0) return n->object;
    n = n->next;
  }

  return 0;
}

// -----------------------------------------------------------------------------
// void Hash::remove(const char *k)
//
// Removes an item from the hash table.  Does nothing if item isn't in the
// hash table to begin with.
// 
// Inputs : k = Key value
//
// Output : None
//
// Side Effects : Deletes item from hash table.
// -----------------------------------------------------------------------------

void Hash::remove(const char *k) {

  int  hv;
  Node *n,*prev;

  hv = h1(k);                                  // Get hash value
  n = hashtable[hv];
  prev = 0;
  while (n) {
    if (strcmp(n->key,k) == 0) {
      // Found it, kill the thing
      if (prev) {
	prev->next = n->next;
      } else {
	hashtable[hv] = n->next;
      }
      delete n;
      return;
    }
    prev = n;
    n = n->next;
  }
}

// -----------------------------------------------------------------------------
// void *Hash::first()
//
// Gets the first item from the hash table or NULL if empty.
// 
// Inputs : None
//
// Output : First object in hash table or NULL if hash table is empty.
//
// Side Effects : Resets an internal iterator variable on the hash table.
// -----------------------------------------------------------------------------

void *Hash::first() {
  index = 0;
  current = 0;

  while (!hashtable[index] && (index < hashsize))
    index++;

  if (index >= hashsize) return 0;
  current = hashtable[index];
  return current->object;
}


// -----------------------------------------------------------------------------
// char *Hash::firstkey()
//
// Gets the first key from the hash table or NULL if empty.
// 
// Inputs : None
//
// Output : First key in hash table or NULL if hash table is empty.
//
// Side Effects : Resets an internal iterator variable on the hash table.
// -----------------------------------------------------------------------------

char *Hash::firstkey() {
  index = 0;
  current = 0;

  while (!hashtable[index] && (index < hashsize))
    index++;

  if (index >= hashsize) return 0;
  current = hashtable[index];
  return current->key;
}

// -----------------------------------------------------------------------------
// void *Hash::next()
// 
// Returns the next item in the hash table or NULL if there are no more entries.
// A call to first() should generally be made before using this function.
//
// Inputs : None
//
// Output : Pointer to next object or NULL if there are no more objects.
//
// Side Effects : Updates an iterator variable private to the hash table.
// -----------------------------------------------------------------------------

void *Hash::next() {
  if (index < 0) return first();
  
  // Try to move to the next entry

  current = current->next;

  if (current) {
    return current->object;
  } else {
    index++;
    while (!hashtable[index] && (index < hashsize))
      index++;
    if (index >= hashsize) return 0;
    current = hashtable[index];
    return current->object;
  }
}


// -----------------------------------------------------------------------------
// char *Hash::nextkey()
// 
// Returns the next key in the hash table or NULL if there are no more entries.
// A call to firstkey() should generally be made before using this function.
//
// Inputs : None
//
// Output : Pointer to next key or NULL if there are no more objects.
//
// Side Effects : Updates an iterator variable private to the hash table.
// -----------------------------------------------------------------------------

char *Hash::nextkey() {
  if (index < 0) return firstkey();
  
  // Try to move to the next entry

  current = current->next;

  if (current) {
    return current->key;
  } else {
    index++;
    while (!hashtable[index] && (index < hashsize))
      index++;
    if (index >= hashsize) return 0;
    current = hashtable[index];
    return current->key;
  }
}

/***********************************************************************
 *
 * -- Revision History
 * $Log: hash.cxx,v $
 * Revision 1.6  1997/07/14 03:57:32  beazley
 * Eliminated use of malloc/free
 *
 * Revision 1.5  1997/05/28 06:13:30  beazley
 * Moved revision history to end.
 *
 * Revision 1.4  1997/01/15 05:45:47  beazley
 * Added firstkey() and nextkey() methods.
 *
 * Revision 1.3  1997/01/06 17:08:17  beazley
 * Cleanup. A few minor modifications
 *
 ***********************************************************************/


