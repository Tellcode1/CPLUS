#include "oop.h"

#include "overridables.h"
#include "types.h"

#define cp_array_for_each(array, index, type) for (size_t(index) = 0; (index) < array.size / sizeof(type); (index)++)
#define cp_array_for_each_ptr(array, index) for (size_t(index) = 0; (index) < array->size / array->element_size; (index)++)

#define cp_array_get(array, index, type) ((type*)array.data)[index]
#define cp_array_get_ptr(array, index, type) ((type*)array->data)[index]
#define cp_array_element(element, type)                                                                                                              \
    (type[]) { element }
#define cp_array_elements(type, ...)                                                                                                                 \
    (type[]) { __VA_ARGS__ }
#define cp_array_elements_size(array, type) (sizeof(array) / sizeof(type))

object cp_array
{
    self(cp_array);
    size_t element_size;

    void*  data;
    size_t size;

    objectfn_pointer(cp_array, set, void)(selftype cp_array * self, void* data, size_t size);
    objectfn_pointer(cp_array, len, size_t)(selftype cp_array * self);
    objectfn_pointer(cp_array, append, void)(selftype cp_array * self, void* element);
    objectfn_pointer(cp_array, find, selftype cp_array)(selftype cp_array * self, void* element);
    objectfn_pointer(cp_array, insert, void)(selftype cp_array * self, void* element, size_t index);
    objectfn_pointer(cp_array, insert_elements, void)(selftype cp_array * self, void* element, size_t index, size_t ammout);
    objectfn_pointer(cp_array, subarr, selftype cp_array)(selftype cp_array * self, i64 start, i64 finish, i64 skip);
    objectfn_pointer(cp_array, remove, void)(selftype cp_array * self, size_t index);
}
cp_array;

objectfn(cp_array, find, cp_array)(cp_array* self, void* element);
objectfn(cp_array, subarr, selftype cp_array)(selftype cp_array* self, i64 start, i64 finish, i64 skip);
objectfn(cp_array, remove, void)(selftype cp_array* self, size_t index);
objectsetup(cp_array)(cp_array* result, size_t type_size);

objectfn(cp_array, set, void)(cp_array* self, void* data, size_t size)
{
    if (self->data != NULL) { cp_free(self->data); }

    self->data = (void*)cp_calloc(size);
    self->size = size;
    cp_memcpy(self->data, data, size);
}

objectfn(cp_array, len, size_t)(selftype cp_array* self)
{
    size_t result = 0;

    cp_array_for_each_ptr(self, i) result++;

    return result;
}

objectfn(cp_array, append, void)(cp_array* self, void* element)
{
    void* new_data = cp_calloc(self->size + self->element_size);
    if (new_data == NULL) { return; }

    if (self->data != NULL)
    {
        cp_memcpy(new_data, self->data, self->size);
        cp_free(self->data);
    }
    else
    {
        cp_memcpy((char*)new_data + self->size, element, self->element_size);
        self->data = new_data;
        self->size += self->element_size;
        return;
    }

    cp_memcpy((char*)new_data + self->size, element, self->element_size);

    self->data = new_data;
    self->size += self->element_size;
}

objectfn(cp_array, find, cp_array)(cp_array* self, void* element)
{
    cp_array result init(cp_array)(&result, sizeof(size_t));
    result.self = &result;

    for (size_t i = 0; i < self->size / self->element_size; i++)
    {
        if (cp_memcmp((char*)self->data + i * self->element_size, element, self->element_size) == 0)
        {
            /* Append the index where we found it to the list */
            result.append(result.self, cp_array_element(i, size_t));
        }
    }
    /* Return the list containing the indices of every element in self that is equal to element */
    return result;
}

objectfn(cp_array, insert, void)(cp_array* self, void* element, size_t index)
{
    if (index > (self->size / self->element_size)) return;

    self->append(self->self, element);

    for (size_t i = (self->size / self->element_size) - 1; i > index; i--)
    {
        void* dest = (char*)self->data + i * self->element_size;
        void* src  = (char*)self->data + (i - 1) * self->element_size;
        cp_memcpy(dest, src, self->element_size);
    }

    void* insert_at = (char*)self->data + index * self->element_size;
    cp_memcpy(insert_at, element, self->element_size);
}

objectfn(cp_array, insert_elements, void)(cp_array* self, void* elements, size_t index, size_t ammout)
{
    for (size_t i = 0; i < ammout; i++)
    {
        void* elem = (char*)elements + i * self->element_size;
        self->insert(self->self, elem, index + i);
    }
}

/**
 * Python.
 * @param skip The indices of the elements skipped while adding elements to the array.
 */
objectfn(cp_array, subarr, cp_array)(selftype cp_array* self, i64 start, i64 finish, i64 skip)
{
    cp_array result init(cp_array)(&result, self->element_size);

    finish++;
    i64 len = (i64)(self->size / self->element_size);

    if (skip == 0) return result;

    /*
     * Wrap around the array if the start or end is negative
     */
    if (start < 0) start += len;
    if (finish < 0) finish += len;

    if (start < 0) start = 0;
    if (finish < 0) finish = 0;
    if (start > len) start = len;
    if (finish > len) finish = len;

    if (skip > 0)
    {
        for (size_t i = start; i < finish; i += skip)
        {
            void* a = (char*)self->data + i * self->element_size;
            result.append(result.self, a);
        }
    }
    else
    {
        for (size_t i = start; i < finish; i -= skip)
        {
            void* a = (char*)self->data + (finish - (i - start) + skip) * self->element_size;
            result.append(result.self, a);
        }
    }

    return result;
}

objectfn(cp_array, remove, void)(cp_array* self, size_t index)
{
    if (index >= (self->size / self->element_size))
    {
        // Index is out of bounds, return or handle error.
        return;
    }

    // Create new memory for the array with one less element
    void* newData = cp_calloc(self->size - self->element_size);
    if (newData == NULL)
    {
        // alloc failed
        return;
    }

    // Copy elements before the index to the new array
    cp_memcpy(newData, self->data, index * self->element_size);

    // Copy elements after the index to the new array
    cp_memcpy(
        (char*)newData + index * self->element_size,
        (char*)self->data + (index + 1) * self->element_size,
        (self->size - (index + 1) * self->element_size));

    // free the old data
    cp_free(self->data);

    // Update the data pointer to the new array
    self->data = newData;

    // Reduce the size of the array by one element
    self->size -= self->element_size;
}

objectsetup(cp_array)(cp_array* result, size_t type_size)
{
    result->self         = result;
    result->data         = NULL;
    result->element_size = type_size;
    result->size         = 0;

    objectfn_setup(result, cp_array, set);
    objectfn_setup(result, cp_array, len);
    objectfn_setup(result, cp_array, append);
    objectfn_setup(result, cp_array, find);
    objectfn_setup(result, cp_array, insert);
    objectfn_setup(result, cp_array, insert_elements);
    objectfn_setup(result, cp_array, subarr);
    objectfn_setup(result, cp_array, remove);

    return result;
}
