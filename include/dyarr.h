#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFOS 3
#define INITIAL_CAP 2
#define RESIZE_FACTOR 2

typedef enum {
    SIZE,
    CAP,
    DATA_SIZE
} Info;

void* _create_arr(size_t initial_cap, size_t data_size);
void _free(void* arr);
size_t _get_info(void* arr, Info info);
void _set_info(void* arr, Info info, size_t value);
void* _resize(void* arr);
void* _add(void* arr, void* p_data);
void _remove(void* arr, size_t index);
void _insert(void* arr, size_t index, void* p_data);
void _pop(void* arr, size_t index, void* output);
void* _shrink_to_fit(void* arr);
void _clear(void* arr);
int _is_empty(void* arr);

#define DA_Create(type) _create_arr(INITIAL_CAP, sizeof(type))
#define DA_Free(arr) _free(arr)
#define DA_Add(arr, x) \
    do {\
        __auto_type temp = x;\
        arr = _add(arr, &temp);\
    } while (0)

#define DA_Insert(arr, i, x) \
    do {\
        __auto_type temp = x;\
        _insert(arr, i, &temp);\
    } while (0)

#define DA_Find(arr, x, output) \
	int output = -1;\
    do {\
        for (int i = 0; i < (int) _get_info(arr, SIZE); i++) {\
            if (arr[i] == x) {\
                output = i;\
                break;\
            }\
        }\
    } while (0)

#define DA_Remove(arr, i) _remove(arr, i);
#define DA_Pop(arr, i, o) _pop(arr, i, &o)
#define DA_Fit_Shrink(arr) arr = _shrink_to_fit(arr)
#define DA_Clear(arr) _clear(arr)
#define DA_Print(arr, format, start, end) \
    do {\
        for (size_t i = start; i < end; i++) {\
            printf(format, arr[i]);\
        }\
    } while (0)

#define DA_Is_Empty(arr) _is_empty(arr)
#define DA_Size(arr) _get_info(arr, SIZE)
#define DA_Cap(arr) _get_info(arr, CAP)
#define DA_Data_Size(arr) _get_info(arr, DATA_SIZE)
