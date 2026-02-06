#include <stdlib.h>

#define CVECTOR_DEFAULT_CAPACITY 100

typedef struct cvector
{
    size_t size;
    size_t capacity;
    size_t elem_size;
    void *ptr;

} cvector;

/*  [ cvector_init ]

    Init function for cvector. 
    Input parameters:
        * cvec = cvector struct
        * el_size = sizeof the relevant data type.

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

*/

#define cvector_reset(cvec)                                             \
do{                                                                     \
    size_t _cvector_saved_elem_size = (cvec).elem_size;                 \
    cvector_free(cvec);                                                 \
    cvector_init(cvec, _cvector_saved_elem_size);                       \
}while (0)


/*  [ cvector_begin ]
    
    Returns pointer to first element of the array

*/
#define cvector_begin(cvec) ((cvec).ptr)

// cvector_push_back ( pushes one new element and reallocates if needed)

// cvector_pop_back, remove the last element. Does not free up capacity.

// cvector_clear(), remove all elements. size = 0. Capactiy the same.

// cvector_shrink_to_size (reduce capacity to size, and free relevant memory)

// cvector_erase_at(X), delete specific element, and reorder the memory?

// cvector_end() <- returns pointer to last element +1

// cvector_begin() returns pointer to first elmeent


