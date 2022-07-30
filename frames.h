// author   : benggee 
// date     : 2022-07-30
// purpose  : Alloc frames
// notice   : 

#ifndef LIST_FRAMES_H
#define LIST_FRAMES_H

#include "list.h"

// alloc frames
int alloc_frame(List*);
// free frames
int free_frame(List*, int);

#endif //LIST_FRAMES_H
