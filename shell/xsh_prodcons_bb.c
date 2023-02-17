#include<xinu.h>
#include<stdio.h>
#include<prodcons_bb.h>
#include<processterminator.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>



bool isnumber(char *s);

shellcmd xsh_prodcons_bb(int nargs, char* args[])
{
    /* Initialize the shared array */
    int arr_q[5];
    int head=0, tail=0;

    /* Initialize the semaphore*/
    sid32 lock=semcreate(1);

    /* Global variable*/
    int total=0;



    int m,n,i,j;

   // check the correctness of input 
   
   //case 1: missing arguments
   if(nargs<5)
   {
        printf("Missing arguments");
        return 0;

   }

   // case 2: check the correctness of input and assign value
   else
   {
     if(isnumber(args[1]) && isnumber(args[2]) && isnumber(args[3]) && isnumber(args[4]))
     {
         m=count(args[1]);
         n=count(args[2]);
         i=count(args[3]);
         j=count(args[4]);
     }
   }
   // case 3: if consumer iterations doesnt match with producer iteration throw error 
   if(m*i!=n*j )
   {
        printf("Iteration Mismatch Error: the number of producer(s) iteration does not match the consumer(s) iteration\n");
        return 0;
   }

   //create m producer process  
   
   for (int i=0;i<m;i++)
   {
     char str[2];
     sprintf(str,"%d",i);
     char s[]="producer_";
     strcat(s,str);
    
     resume(create(producer_bb,1024,20,"producer",2,i,s));
   }

   //create n consumer process
  
   for (int i=0;i<n;i++)
   {
     char str[2];
     sprintf(str,"%d",i);
     char s[]="consumer_";
     strcat(s,str);
     resume(create(consumer_bb,1024,20,"consumer",2,j,s));
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