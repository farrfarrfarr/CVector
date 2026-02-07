typedef struct cvector        \n
{                            
    size_t size;
    size_t capacity;
    size_t elem_size;
    void *ptr;

} cvector;

Supports:
#define cvector_init(cvec, el_size)
#define cvector_free(cvec) 
#define cvector_reset(cvec) 
#define cvector_begin(cvec) 
#define cvector_end(cvec)
#define cvector_pop_back(cvec)  
#define cvector_clear(cvec)  \n
#define cvector_push_back(cvec, type,element)   \n 
#define cvector_reserve(cvec, nr_of_elements)  \n
#define cvector_grow_capacity(cvec, nr_of_elements_to_grow)
#define cvector_shrink_to_size(cvec) 
#define cvector_erase_at(cvec, index_to_delete)  
