#ifndef FZ_STRING_H
#define FZ_STRING_H

// 8 Bit strings
typedef struct String8 {
  U64  size;
  U8* str;
} String8;
#define Str8(s) (String8){sizeof(s)-1, (U8*)(s)}

typedef struct String8_Node {
  struct String8_Node* next;
  String8 value;
} String8_Node;

typedef struct String8_List {
  String8_Node* first;
  String8_Node* last;
  U64 node_count;
  U64 total_size;
} String8_List;

internal String8 string8_new(U64 size, U8* str);
internal String8 string8_format(Arena* arena, String8 fmt, ...);
internal String8 string8_range(U8* first, U8* range);
internal String8 string8_concat(Arena* arena, String8 a, String8 b); // TODO(fz): Test this func
internal String8 string8_slice(String8 str, U64 start, U64 end);
internal String8 string8_trim(String8 str);
internal B32     string8_contains(String8 str, String8 substring);
internal B32     string8_find_first(String8 str, String8 substring, U64* index);
internal B32     string8_find_last(String8 str, String8 substring, U64* index); 
internal B32     string8_equal(String8 a, String8 b);
internal void    string8_printf(String8 str);

internal String8_List string8_split(Arena* arena, String8 str, String8 split_character);
internal String8_List string8_list_new(Arena* arena, String8 str);
internal String8      string8_list_pop(String8_List* list);
internal void         string8_list_clear(String8_List* list);
internal void         string8_list_push(Arena* arena, String8_List* list, String8 str);
internal String8      string8_list_join(Arena* arena, String8_List* list);

internal B32     f32_from_string8(String8 str, F32* value);
internal B32     s32_from_string8(String8 str, S32* value);
internal B32     b32_from_string8(String8 str, B32* value);
internal U8*     cstring_from_string8(Arena* arena, String8 str);
internal String8 string8_from_cstring(U8* cstring);

// 16 Bit strings
typedef struct String16 {
  U64 size;
  U16* str;
} String16;
#define Str16(s) (String16{sizeof(s)-1, (U16*)(s)};

internal String8  string8_from_string16(Arena* arena, String16 str16);
internal String16 string16_from_string8(Arena *arena, String8 str8);
internal wchar_t* wcstr_from_string16(Arena *arena, String16 str16); // TODO(fz): This is a windows only function.

//~ Char Functions
internal B32   char8_is_alpha(U8 c);
internal B32   char8_is_alphanum(U8 c);
internal B32   char8_is_alpha_upper(U8 c);
internal B32   char8_is_alpha_lower(U8 c);
internal B32   char8_is_digit(U8 c);
internal B32   char8_is_symbol(U8 c);
internal B32   char8_is_space(U8 c);
internal U8 char8_to_upper(U8 c);
internal U8 char8_to_lower(U8 c);

#endif // FZ_STRING_H