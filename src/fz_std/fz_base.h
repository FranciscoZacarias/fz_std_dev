#ifndef BASE_H
#define BASE_H

#pragma warning(disable: 4201) // nonstandard extension used: nameless struct/union

#define FZ_STD 1

#define ERROR_MESSAGE_AND_EXIT(...) // TODO(fz): implement proper error handling.

// @Section: *.h
#include "base\context_cracking.h"
#include "base\core.h" 
#include "base\memory.h"
#include "base\math.h"
#include "base\string.h"
#include "base\thread_context.h"
#include "base\command_line.h"
#include "base\entry_point.h"
#include "os\os.h"

// @Section: *.c
#include "base\memory.c"
#include "base\math.c"
#include "base\string.c"
#include "base\thread_context.c"
#include "base\command_line.c"
#include "base\entry_point.c"
#include "os\os.c"

#endif // BASE_H