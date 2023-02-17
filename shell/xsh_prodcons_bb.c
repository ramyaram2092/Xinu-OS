#include<xinu.h>
#include<stdio.h>
#include<prodcons_bb.h>
#include<processterminator.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>



bool isnumber(char *s);
 int arr_q[5];
 int head, tail,total;
 sid32 lock;


shellcmd xsh_prodcons_bb(int nargs, char* args[])
{
    /* Initialize the shared array */
    head=0;
    tail=0;

    /* Initialize the semaphore*/
     lock=semcreate(1);

    /* Global variable*/
    total=0;



    int m,n,i,j;

   // check the correctness of input 
   
   //case 1: missing arguments
   if(nargs<5)
   {
        printf("Missing arguments");
        signal(completecmd);
        return 0;

   }

   // case 2: check the correctness of input and assign value
   else
   {
     if(isnumber(args[1]) && isnumber(args[2]) && isnumber(args[3]) && isnumber(args[4]))
     {
         m=atoi(args[1]);
         n=atoi(args[2]);
         i=atoi(args[3]);
         j=atoi(args[4]);
     }
   }
   // case 3: if consumer iterations doesnt match with producer iteration throw error 
   if(m*i!=n*j )
   {
        printf("Iteration Mismatch Error: the number of producer(s) iteration does not match the consumer(s) iteration\n");
        signal(completecmd);
        return 0;
   }

   printf("\n Process Creation Starts ");
   //create m producer process  
   
   for (int k=0;k<m;k++)
   {
     char str[4];
     sprintf(str,"%d",k);
     char s[]="producer_";
     strncat(s,str,4);
    
     resume(create(produce_bb,1024,20,"producer",2,i,s));
   }

   //create n consumer process
  
   for (int k=0;k<n;k++)
   {
     char str[4];
     sprintf(str,"%d",k);
     char s[]="consumer_";
     strncat(s,str,4);
     resume(create(consume_bb,1024,20,"consumer",2,j,s));
   }
  
  int sum=m+n;

  // wait for all process to get over
  while(total<(sum))
  {

  }
  semdelete(lock);

  signal(completecmd);

    return 0;

}

// check if the the string is a valid number 
bool isnumber(char *val)
{
  char *s;
  for(s=val;*s!='\0';s++)
  {
    if(!isdigit(*s))
    {
      return false;
    }
   }
   return true;
}