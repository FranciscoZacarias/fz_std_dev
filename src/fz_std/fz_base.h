#ifndef BASE_H
#define BASE_H

#define FZ_STD 1

// @Section: *.h
#include "base\context_cracking.h"
#include "base\core.h" 
#include "base\memory.h"
#include "base\math.h"
#include "base\string.h"
#include "base\thread_context.h"
#include "base\command_line.h"
#include "os\os.h"

// @Section: *.c
#include "base\memory.c"
#include "base\math.c"
#include "base\string.c"
#include "base\thread_context.c"
#include "base\command_line.h"
#include "os\os.c"

#endif // BASE_H