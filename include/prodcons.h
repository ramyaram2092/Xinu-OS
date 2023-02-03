/* Global variable for producer consumer */
extern int n; /* this is just declaration */
extern sid32 prod,cons, complete;
/* Function Prototype */
void consumer(sid32 prod, sid32 cons,sid32 complete, int count);
void producer(sid32 prod, sid32 cons, int count);
