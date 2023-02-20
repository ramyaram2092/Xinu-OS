extern int arr_q[5];
extern volatile int head, tail, total;
extern sid32 lock, complete ;

void consume_bb(int count, int pid);
void produce_bb(int count, int pid);