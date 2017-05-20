        // DECLARATIONS
typedef void (*new_handler)();
class bad_alloc;
class nothrow_t;
extern const nothrow_t nothrow;

        // FUNCTIONS
new_handler set_new_handler(new_handler pnew) throw();

        // OPERATORS
void operator delete(void *ptr) throw();  // REPLACEABLE
void operator delete(void *, void *) throw();
void operator delete(void *ptr,  // REPLACEABLE
    const nothrow_t&) throw();
void operator delete[](void *ptr) throw();  // REPLACEABLE
void operator delete[](void *, void *) throw();
void operator delete[](void *ptr,  // REPLACEABLE
    const nothrow_t&) throw();
void *operator new(size_t count)  // REPLACEABLE
    throw(bad_alloc);
void *operator new(size_t count,  // REPLACEABLE
    const nothrow_t&) throw();
void *operator new(size_t count, void *ptr) throw();
void *operator new[](size_t count)  // REPLACEABLE
    throw(bad_alloc);
void *operator new[](size_t count,  // REPLACEABLE
    const nothrow_t&) throw();
void *operator new[](size_t count,
    void *ptr) throw();
        // END OF DECLARATIONS
