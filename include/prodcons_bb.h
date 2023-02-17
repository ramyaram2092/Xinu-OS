extern int arr_q[5];
extern int head, tail, total;
extern sid32 lock;

void consumer_bb(int count, char s[]);
void producer_bb(int count, char s[]);