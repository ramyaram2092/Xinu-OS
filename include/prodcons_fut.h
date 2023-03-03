extern int value;
extern int volatile  flag,end;


void consumer_fut(future_t * f);
void producer_fut(int val,future_t* f);