#include "dyarr.h"

void* _create_arr(size_t initial_cap, size_t data_size) {
    size_t info_size = sizeof(size_t) * INFOS;
    size_t initial_arr_size = initial_cap * data_size;
    size_t* raw = malloc(info_size + initial_arr_size);
    if (!raw) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    
    raw[SIZE] = 0;
    raw[CAP] = initial_cap;
    raw[DATA_SIZE] = data_size;
    
    return (void*) &raw[INFOS];
}

void _free(void* arr) {
    free(arr - (sizeof(size_t) * INFOS));
}

size_t _get_info(void* arr, Info info) {
    size_t* raw = ((size_t*) arr) - INFOS;
    return raw[info];
}

void _set_info(void* arr, Info info, size_t value) {
    size_t* raw = ((size_t*) arr) - INFOS;
    raw[info] = value;
}

void* _resize(void* arr) {
    void* new_arr = _create_arr(_get_info(arr, CAP) * RESIZE_FACTOR, _get_info(arr, DATA_SIZE));
    memcpy(new_arr, arr, _get_info(arr, SIZE) * _get_info(arr, DATA_SIZE));
    _set_info(new_arr, SIZE, _get_info(arr, SIZE));
    _free(arr);
    
    return new_arr;
}

void* _add(void* arr, void* p_data) {
    if (_get_info(arr, SIZE) >= _get_info(arr, CAP)) {
        arr = _resize(arr);
    }
    memcpy(
        arr + _get_info(arr, SIZE) * _get_info(arr, DATA_SIZE), 
        p_data, 
        _get_info(arr, DATA_SIZE)
    );
    _set_info(arr, SIZE, _get_info(arr, SIZE) + 1);
    return arr;
}

void _remove(void* arr, size_t index) {
	if (index < 0 || index >= _get_info(arr, SIZE)) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    
    memmove(
        arr + index * _get_info(arr, DATA_SIZE),
        arr + (index + 1) * _get_info(arr, DATA_SIZE),
        (_get_info(arr, SIZE) - index - 1) * _get_info(arr, DATA_SIZE)
    );
    _set_info(arr, SIZE, _get_info(arr, SIZE) - 1);
}

void _insert(void* arr, size_t index, void* p_data) {
    if (index < 0 || index >= _get_info(arr, SIZE)) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    
    memmove(
        arr + (index + 1) * _get_info(arr, DATA_SIZE),
        arr + index * _get_info(arr, DATA_SIZE),
        (_get_info(arr, SIZE) - index) * _get_info(arr, DATA_SIZE)
    );
    memcpy(
        arr + index * _get_info(arr, DATA_SIZE),
        p_data,
        _get_info(arr, DATA_SIZE)
    );
    _set_info(arr, SIZE, _get_info(arr, SIZE) + 1);
}

void _pop(void* arr, size_t index, void* output) {
    if (index < 0 || index >= _get_info(arr, SIZE)) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    
    memcpy(
        output,
        arr + index * _get_info(arr, DATA_SIZE),
        _get_info(arr, DATA_SIZE)
    );
    memmove(
        arr + index * _get_info(arr, DATA_SIZE),
        arr + (index + 1) * _get_info(arr, DATA_SIZE),
        (_get_info(arr, SIZE) - index) * _get_info(arr, DATA_SIZE)
    );
    _set_info(arr, SIZE, _get_info(arr, SIZE) - 1);
}

void* _shrink_to_fit(void* arr) {
    void* new_arr = malloc(_get_info(arr, SIZE) * _get_info(arr, DATA_SIZE));
    memcpy(new_arr, arr, _get_info(arr, SIZE) * _get_info(arr, DATA_SIZE));
    _set_info(new_arr, SIZE, _get_info(arr, SIZE));
    _set_info(new_arr, CAP, _get_info(arr, SIZE));
    _set_info(new_arr, DATA_SIZE, _get_info(arr, DATA_SIZE));
    _free(arr);
    
    return new_arr;
}

void _clear(void* arr) {
    _set_info(arr, SIZE, 0);
}

int _is_empty(void* arr) {
    return (_get_info(arr, SIZE) == 0);
}
