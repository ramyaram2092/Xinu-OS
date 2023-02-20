#include<xinu.h>
#include<stdio.h>
#include<prodcons_bb.h>
#include<processterminator.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>



bool isnumber(char *s);
 int arr_q[5];
 volatile int head, tail,total;
 sid32 lock,complete;


shellcmd xsh_prodcons_bb(int nargs, char* args[])
{
    /* Initialize the shared array */
    head=-1;
    tail=-1;

    /* Initialize the semaphore*/
     lock=semcreate(0);
     complete=semcreate(1);

    /* Global variable*/
    total=0;



    int m,n,i,j;

   // check the correctness of input 
   
   //case 1: missing arguments
   if(nargs<5)
   {
        printf("Missing arguments\n");
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
  //  if(m*i!=n*j )
  //  {
  //       printf("Iteration Mismatch Error: the number of producer(s) iteration does not match the consumer(s) iteration\n");
  //       signal(completecmd);
  //       return 0;
  //  }

  //  printf("\n Process Creation Starts ");
   //create m producer process  
   
   for (int k=0;k<m;k++)
   {
    //  wait(lock);
     
     printf("Initiating producer_%d\n",k);
     resume(create(produce_bb,1024,20,"producer_bb",2,i,k));
    //  signal(lock);

   }

   //create n consumer process
  
  //  for (int k=0;k<n;k++)
  //  {
  //     // wait(lock);
  //    char str[4];
  //    sprintf(str,"%d",k);
  //    char s[]="consumer_";
  //    strncat(s,str,4);
  //   //  printf("Initiating %s\n",s);
  //    resume(create(consume_bb,1024,20,"consumer_bb",2,j,s));
  //   //  signal(lock);

  //  }

  
  int sum=m+n;
  printf("Sum : %d, total : %d",sum,total);
     signal(lock);

  // wait for all process to get over
  while(total<(sum))
  {
  //  printf("Savu : %d\n",total);
  }
  printf(" after while total : %d\n",total);

  semdelete(lock);
  semdelete(complete);

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