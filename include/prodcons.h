/* Global variable for producer consumer */
extern int n; /* this is just declaration */
extern sid32 prod,cons;
/* Function Prototype */
void consumer(int count, sid32 prod, sid32 cons);
void producer(int count, sid32 prod, sid32 cons);
