#ifndef FZ_MEMORY_H
#define FZ_MEMORY_H

#ifndef ARENA_RESERVE_SIZE
# define ARENA_RESERVE_SIZE Gigabytes(1)
#endif
#ifndef ARENA_COMMIT_SIZE
# define ARENA_COMMIT_SIZE Kilobytes(64)
#endif

typedef struct Arena {
  U64 reserved;      // Reserved memory
  U64 commited;      // Commited memory
  U64 commit_size;   // Size for each commit on this arena
  U64 position;      // Current position of the arena
  U64 align;         // Arena's memory alignment
} Arena;

#define ARENA_HEADER_SIZE AlignPow2(sizeof(Arena), memory_get_page_size())

internal Arena* arena_init();
internal Arena* arena_init_sized(U64 reserve, U64 commit);

internal void* arena_push(Arena* arena, U64 size);
internal void* arena_push_no_zero(Arena* arena, U64 size);
internal void  arena_pop(Arena* arena, U64 size);
internal void  arena_pop_to(Arena* arena, U64 pos);
internal void  arena_clear(Arena* arena);
internal void  arena_free(Arena* arena);

internal void print_arena(Arena *arena, const U8* label);

#define ArenaPush(arena, type, count)       (type*)arena_push((arena), sizeof(type)*(count))
#define ArenaPushNoZero(arena, type, count) (type*)arena_push_no_zero((arena), sizeof(type)*(count))

typedef struct Arena_Temp {
  Arena* arena;
  U64 temp_position;
} Arena_Temp;

internal Arena_Temp arena_temp_begin(Arena* arena);
internal void       arena_temp_end(Arena_Temp* temp);

#endif // FZ_MEMORY_H