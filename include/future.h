


typedef enum{
    FUTURE_EMPTY,
    FUTURE_WAITING,
    FUTURE_READY
}future_state_t;

typedef enum{
    FUTURE_EXCLUSIVE,
    FUTURE_SHARED,
    FUTURE_MODE
}future_mode_t;


typedef struct future_t{
    void * data;
    uint size;
    future_state_t state;
    future_mode_t mode;
    pid32 pid;
}future_t;



extern future_t *f1,f2 ;

future_t* future_alloc (future_mode_t mode, uint size,uint nelems);
syscall future_free(future_t*);
syscall future_get(future_t* f, void* out);
syscall future_set(future_t* f, void* in);