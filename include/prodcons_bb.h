extern int arr_q[5];
extern volatile int total;
extern int head, tail;
extern sid32 lock, complete ;

void consume_bb(int count, int pid);
void produce_bb(int count, int pid);