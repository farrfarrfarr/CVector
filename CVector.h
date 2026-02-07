#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>


#define DEBUG false                           // Debug flag
#define CVECTOR_DEFAULT_CAPACITY 4            // Initial size of array.
#define GROWTH_MULTIPLIER 2                   // Growth multiplier of allocated memory when size become == capacity.

/*  typedef struct cvector

    size        = number of used elements.
    capacity    = number of allocated elements in memory
    elem_size   = size of each element.
    *ptr        = pointer to be used as dynamic array.

*/

typedef struct cvector
{
    size_t size;
    size_t capacity;
    size_t elem_size;
    void *ptr;

} cvector;

/*  [ cvector_init ]

    Init function for cvector. Input parameters:
        cvec    = cvector struct
        el_size = sizeof the relevant data type.

    Example usage:
        cvector vec;
        cvector_init(vec,sizeof(int));

*/
#define cvector_init(cvec, el_size)                                     \
do{                                                                     \
        (cvec).size = 0;                                                \
        (cvec).capacity = CVECTOR_DEFAULT_CAPACITY;                     \
        (cvec).elem_size = el_size;                                     \
        (cvec).ptr = malloc(((cvec).capacity)*((cvec).elem_size));      \
}while (0)

/*  [ cvector_free ]
    
    Function to free memory on the heap, 
    for the pointer used in the given struct.

    Example usage:
        cvector vec;
        cvector_init(vec,sizeof(int));

        cvector_free(vec);

*/
#define cvector_free(cvec)                                              \
do{                                                                     \
    free( (cvec).ptr);                                                  \
    (cvec).ptr = NULL;                                                  \
    (cvec).size = 0;                                                    \
    (cvec).capacity = 0;                                                \
    (cvec).elem_size = 0;                                               \
}while (0)


/*  [ cvector_reset ]
    
    Function to fully reset- and re-initalise cvector

    Example usage:
        cvector vec;
        cvector_init(vec,sizeof(int));

        cvector_reset(vec);

*/
#define cvector_reset(cvec)                                             \
do{                                                                     \
    size_t _cvector_saved_elem_size = (cvec).elem_size;                 \
    cvector_free(cvec);                                                 \
    cvector_init(cvec, _cvector_saved_elem_size);                       \
}while (0)


/*  [ cvector_begin ]
    
    Returns pointer to first element of the array

    Example usage:
            cvector vec;
            cvector_init(vec,sizeof(int));

            int *p   = cvector_begin(vec);
            int *end = (int*)cvector_end(vec);

                for (; p != end; ++p) 
                {
                    printf("%d\n", *p);
                }

*/
#define cvector_begin(cvec) ((cvec).ptr)

/*  [ cvector_end ]
    Returns pointer to last element + 1

    Example usage:
        cvector vec;
        cvector_init(vec,sizeof(int));

        int *p   = cvector_begin(vec);
        int *end = (int*)cvector_end(vec);

            for (; p != end; ++p) 
            {
                printf("%d\n", *p);
            }
*/
#define cvector_end(cvec) ((uint8_t*)(cvec).ptr + ((cvec).elem_size * (cvec).size))

/*  [ cvector_pop_back ]

    Removes the last element. Does not free up capacity.
    Example usage:
        [MISSING]
*/
#define cvector_pop_back(cvec)                          \
do{                                                     \
    if ((cvec).size > 0)                                \
    {                                                   \
        (cvec).size -= 1;                               \
    }                                                   \
}while (0)                                          

/*  [cvector_clear]

    Removes all elements in vector. 
    Sets size = 0, does not change capacity.

    Example usage:
        cvector vec;
        cvector_init(vec,sizeof(int));

        cvector_clear(cvec);
*/
#define cvector_clear(cvec)                             \
do{                                                     \
        (cvec).size = 0;                                \
}while (0)  

/*  [ cvector_push_back ]

    Appends one element at element position size+1.
    Auto-expand allocated memory by GROWTH_MULTIPLIER if size becomes == capacity.

    Parameters:
        cvec = vector to append value to
        type = datatype of the new element
        element = value to append

    Example usage:
    cvector vec;
    cvector_init(vec,sizeof(int));

    cvector_push_back(cvec, int, 433);

    int a = 42;
    cvector_push_back(cvec, int, a);
*/
#define cvector_push_back(cvec, type,element)                                                   \
do{                                                                                             \
    assert(cvec.ptr != NULL);                                                                   \
    assert(cvec.elem_size == sizeof(type));                                                     \
                                                                                                \
    bool __cvector_valid_push_back = true;                                                      \
    if ((cvec).size == (cvec).capacity)                                                         \
    {                                                                                           \
        const size_t NEW_CAPACITY = (GROWTH_MULTIPLIER * (cvec).capacity);                      \
        void *__cvector_void_ptr = realloc((cvec).ptr, NEW_CAPACITY * (cvec).elem_size);        \
                                                                                                \
        if (__cvector_void_ptr != NULL)                                                         \
        {                                                                                       \
             (cvec).ptr = __cvector_void_ptr;                                                   \
             (cvec).capacity = NEW_CAPACITY;                                                    \
        }                                                                                       \
        else                                                                                    \
        {                                                                                       \
            __cvector_valid_push_back = false;                                                  \
        }                                                                                       \
    }                                                                                           \
    if (__cvector_valid_push_back)                                                              \
    {                                                                                           \
        type __cvector_tmp = element;                                                           \
        memcpy(cvector_end((cvec)), &__cvector_tmp, sizeof(type));                              \
        (cvec).size += 1;                                                                       \
    }                                                                                           \
}while(0)   

/*  [ cvector_reserve ]

    Reservs nr_of_elements amount of elements as total capacity, and allocates necessary memory.

    Parameters:
        cvec = cvector to be updated with new capacity.
        nr_of_elements = will be new capacity for cvector.

    Example usage:
        cvector cvec;
        cvector_init(cvec,sizeof(int));

        cvector_reserve(cvec, 200);

*/
#define cvector_reserve(cvec, nr_of_elements)                                                   \
do{                                                                                             \
    if((nr_of_elements) > (cvec).capacity)                                                      \
    {                                                                                           \
        void *__cvector_void_ptr = realloc((cvec).ptr, (nr_of_elements) * (cvec).elem_size);    \
        if (__cvector_void_ptr != NULL)                                                         \
        {                                                                                       \
             (cvec).ptr = __cvector_void_ptr;                                                   \
             (cvec).capacity = (nr_of_elements);                                                \
        }                                                                                       \
    }                                                                                           \
}while(0)

/*  [ cvector_grow_capacity ]

    Makes room for 'N' more pushes. 
    Grows cvector by x elements, on top of existing size.

    Parameters:
        cvec = cvector to be updated with new capacity.
        nr_of_elements_to_grow = elements to be added on top of existing capacity

     Example usage:
        cvector cvec;
        cvector_init(cvec,sizeof(int));

        cvector_grow_capacity(cvec,20);   
*/
#define cvector_grow_capacity(cvec, nr_of_elements_to_grow)                                     \
do{                                                                                             \
    if((nr_of_elements_to_grow) > 0)                                                            \
    {                                                                                           \
        cvector_reserve((cvec), ((cvec).size + (nr_of_elements_to_grow)));                      \
    }                                                                                           \
}while(0)

// cvector_shrink_to_size (reduce capacity to size, and free relevant memory)

// cvector_erase_at(X), delete specific element, and reorder the memory?



