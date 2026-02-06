#include <stdlib.h>
#include <stdint.h>


#define DEBUG false                             // Debug flag
#define CVECTOR_DEFAULT_CAPACITY 100            // Initial size of array.

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







// cvector_push_back ( pushes one new element and reallocates if needed)

// cvector_shrink_to_size (reduce capacity to size, and free relevant memory)

// cvector_erase_at(X), delete specific element, and reorder the memory?



