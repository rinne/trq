$Id: README,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $

This is efficient deque and list handling library.  You can use this
to store structures that have space for one pointer to be used by the
routines.  The struct member that is used as a pointer store is given
in the initialization of the deque (or list) structure.  Be warned
that single item can be only stored to several deques (lists) at the
same time, if all the lists use different member of the structure to
store the pointer.

Theory behind the deque with only one next pointer on storage unit is
based on the fact that (x ^ y) ^ x == y.  We store pointers to the
`last' and the `first' item in the deque.  Whenever new item is stored
into the list we xor the next pointer in the old last item with the
pointer to the new item, store pointer to the old last item into the
next pointer of the new last and update the last pointer in the deque
struct.  Now when we are removing an item from the deque we just need
to store the pointer to the item removed and xor the next pointer in
the item now becoming the last in the deque with the pointer to the
removed item and update the deque structuture.  Beauty of this system
is that we can add and remove stuff into and from the both ends of the
deque with virtually identical functions and we only need one next
pointer within the structures stored into the deque.  This is
important if we have a predefined system structure that we can't
change.

List is implemented so that in the list struct there are two deques
int the list structure.  These lists stand for items before and after
the list pointer.  In between there is one additional pointer standing
for `current item' pointed by the list pointer.  If the list pointer
is invalid, then this additional item is NULL and list have to be
rewinded before operations that require list pointer can be used.

This code is copyright 1995-2001 by Timo J. Rinne <tri@iki.fi>.  
All rights reserved.  See file COPYRIGHT for details.
