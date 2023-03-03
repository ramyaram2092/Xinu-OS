extern int value;
extern  volatile  int flag;


void consumer_fut(future_t * f);
void producer_fut(int val,future_t* f);