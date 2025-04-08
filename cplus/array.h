#include "oop.h"

#include <stdio.h>

#include "externals/malloc.h"
#include "externals/memcpy.h"
#include "externals/memcmp.h"

#define foreach(array, index, type) for (int index = 0; index < array.size / sizeof(type); index++)
#define foreachptr(array, index) for (int index = 0; index < array->size / array->element_size; index++)

#define array_get(array, index, type) ((type*)array.data)[index]
#define array_getptr(array, index, type) ((type*)array->data)[index]
#define array_element(element, type) (type[]){element}
#define array_elements(type, ...) (type[]){__VA_ARGS__}
#define array_elements_size(array, type) sizeof(array) / sizeof(type)

object array {
    self(array);
    size_t element_size;

    void *data;
    size_t size;

    objectfn_pointer(array, set, void)(selftype array *self, void *data, size_t size);
    objectfn_pointer(array, len, int)(selftype array *self);
    objectfn_pointer(array, append, void)(selftype array *self, void* element);
    objectfn_pointer(array, find, selftype array)(selftype array *self, void* element);
    objectfn_pointer(array, insert, void)(selftype array *self, void* element, int index);
    objectfn_pointer(array, insert_elements, void)(selftype array *self, void* element, int index, int ammout);
    objectfn_pointer(array, subarr, selftype array)(selftype array *self, int start, int finish, int skip);
    objectfn_pointer(array, remove, void)(selftype array *self, int index);
} array;

objectfn(array, find, array)(array *self, void* element);
objectfn(array, subarr, selftype array)(selftype array *self, int start, int finish, int skip);
objectfn(array, remove, void)(selftype array *self, int index);
objectsetup(array)(array *result, size_t type_size);

objectfn(array, set, void)(array *self, void *data, size_t size) {
    if (self->data != NULL) {
        free(self->data);
    }

    self->data = (void*)malloc(size);
    self->size = size;
    my_memcpy(self->data, data, size);
}

objectfn(array, len, int)(selftype array *self) {
    int result = 0;

    foreachptr(self, i)
        result++;

    return result;
}

objectfn(array, append, void)(array *self, void* element) {
    void* new_data = malloc(self->size + self->element_size);
    if (new_data == NULL) {
        return;
    }

    if (self->data != NULL) {
        my_memcpy(new_data, self->data, self->size);
        free(self->data);
    } else {
        my_memcpy((char*)new_data + self->size, element, self->element_size);
        self->data = new_data;
        self->size += self->element_size;
        return;
    }

    my_memcpy((char*)new_data + self->size, element, self->element_size);

    self->data = new_data;
    self->size += self->element_size;
}

objectfn(array, find, array)(array *self, void* element) {
    array result init(array)(&result, sizeof(int));
    result.self = &result;
    
    for (int i = 0; i < self->size / self->element_size; i++)
    {
        if (my_memcmp((char*)self->data + i * self->element_size, element, self->element_size) == 0)
            result.append(result.self, array_element(i, int));
    }
    return result;
}

objectfn(array, insert, void)(array *self, void* element, int index) {
    if (index < 0 || index > (int)(self->size / self->element_size))
        return;

    self->append(self->self, element);

    for (int i = (self->size / self->element_size) - 1; i > index; i--) {
        void* dest = (char*)self->data + i * self->element_size;
        void* src  = (char*)self->data + (i - 1) * self->element_size;
        my_memcpy(dest, src, self->element_size);
    }

    void* insert_at = (char*)self->data + index * self->element_size;
    my_memcpy(insert_at, element, self->element_size);
}

objectfn(array, insert_elements, void)(array *self, void* elements, int index, int ammout) {
    for (int i = 0; i < ammout; i++) {
        void *el = (char*)elements + i * self->element_size;
        self->insert(self->self, el, index + i);
    }
}

objectfn(array, subarr, array)(selftype array *self, int start, int finish, int skip) {
    array result init(array)(&result, self->element_size);

    finish++;
    int len = self->size / self->element_size;

    if (skip == 0)
        return result;

    if (start < 0) start += len;
    if (finish < 0) finish += len;

    if (start < 0) start = 0;
    if (finish < 0) finish = 0;
    if (start > len) start = len;
    if (finish > len) finish = len;

    if (skip > 0) {
        for (int i = start; i < finish; i += skip) {
            void* a = (char*)self->data + i * self->element_size;
            result.append(result.self, a);
        }
    } else {
        for (int i = start; i < finish; i += -skip) {
            void* a = (char*)self->data + (finish - (i - start) + skip) * self->element_size;
            result.append(result.self, a);
        }
    }

    return result;
}

objectfn(array, remove, void)(array *self, int index) {
    if (index < 0 || index >= self->size / self->element_size) {
        // Index is out of bounds, return or handle error.
        return;
    }

    // Create new memory for the array with one less element
    void *newData = malloc(self->size - self->element_size);
    if (!newData) {
        // malloc failed
        return;
    }

    // Copy elements before the index to the new array
    my_memcpy(newData, self->data, index * self->element_size);

    // Copy elements after the index to the new array
    my_memcpy((char*)newData + index * self->element_size, 
              (char*)self->data + (index + 1) * self->element_size, 
              (self->size - (index + 1) * self->element_size));

    // Free the old data
    free(self->data);

    // Update the data pointer to the new array
    self->data = newData;

    // Reduce the size of the array by one element
    self->size -= self->element_size;
}

objectsetup(array)(array *result, size_t type_size) {
    result->self = result;
    result->data = NULL;
    result->element_size = type_size;
    result->size = 0;

    objectfn_setup(result, array, set);
    objectfn_setup(result, array, len);
    objectfn_setup(result, array, append);
    objectfn_setup(result, array, find);
    objectfn_setup(result, array, insert);
    objectfn_setup(result, array, insert_elements);
    objectfn_setup(result, array, subarr);
    objectfn_setup(result, array, remove);
}