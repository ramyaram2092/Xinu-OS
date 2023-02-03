/* Global variable for producer consumer */
extern int n; /* this is just declaration */
extern sid32 prod,cons;
/* Function Prototype */
void consumer(sid32 prod, sid32 cons,int count);
void producer(sid32 prod, sid32 cons, int count);
