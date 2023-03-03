#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>
/**
 * @brief The producer_fut function writes the value into the future
 * 
 * @param val 
 * @param f 
 */
void producer_fut(int val, future_t *f)
{
    int v = val;
     wait(print);
    int res = future_set(f, &v);
    printf("Producing %d\n", v);
    signal(print);

    if (res == -1)
    {
        wait(print);
        printf("future_set failed\n");
        signal(print);
    }

    flag += 1;
}