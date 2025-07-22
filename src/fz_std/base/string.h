#ifndef FZ_STRING_H
#define FZ_STRING_H

// 8 Bit strings
typedef struct String8 {
  u64 size;
  u8* str;
} String8;
#define Str8(s) (String8){sizeof(s)-1, (u8*)(s)}

typedef struct String8_Node {
  struct String8_Node* next;
  String8 value;
} String8_Node;

typedef struct String8_List {
  String8_Node* first;
  String8_Node* last;
  u64 node_count;
  u64 total_size;
} String8_List;

internal String8 string8_new(u64 size, u8* str);
internal String8 string8_range(u8* first, u8* range);
internal String8 string8_concat(Arena* arena, String8 a, String8 b); // TODO(fz): Test this func
internal String8 string8_slice(String8 str, u64 start, u64 end);
internal String8 string8_trim(String8 str);
internal b32     string8_contains(String8 str, String8 substring);
internal b32     string8_find_first(String8 str, String8 substring, u64* index);
internal b32     string8_find_last(String8 str, String8 substring, u64* index); 
internal b32     string8_equal(String8 a, String8 b);
internal void    string8_printf(String8 str);

internal String8_List string8_split(Arena* arena, String8 str, String8 split_character);
internal String8_List string8_list_new(Arena* arena, String8 str);
internal String8      string8_list_pop(String8_List* list);
internal void         string8_list_clear(String8_List* list);
internal void         string8_list_push(Arena* arena, String8_List* list, String8 str);
internal String8      string8_list_join(Arena* arena, String8_List* list);

internal b32     f32_from_string8(String8 str, f32* value);
internal b32     s32_from_string8(String8 str, s32* value);
internal b32     b32_from_string8(String8 str, b32* value);
internal u8*     cstring_from_string8(Arena* arena, String8 str);
internal String8 string8_from_cstring(u8* cstring);

//~ Char Functions
internal b32   char8_is_alpha(u8 c);
internal b32   char8_is_alphanum(u8 c);
internal b32   char8_is_alpha_upper(u8 c);
internal b32   char8_is_alpha_lower(u8 c);
internal b32   char8_is_digit(u8 c);
internal b32   char8_is_symbol(u8 c);
internal b32   char8_is_space(u8 c);
internal u8 char8_to_upper(u8 c);
internal u8 char8_to_lower(u8 c);

#endif // FZ_STRING_H