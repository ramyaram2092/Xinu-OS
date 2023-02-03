#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>
#include<string.h>
#include<ctype.h>
#include<processterminator.h>

/** Global Variables **/ 
int n=0; 
sid32 prod,cons,complete,completecmd;
;

/** prodcons function definition **/
shellcmd xsh_prodcons(int nargs, char *args[])
{
    int count; 
    prod=semcreate(0);
    cons=semcreate(1);
    complete=semcreate(0);
    completecmd=semcreate(-1);

    // check if the argument  passed is a number 
    char *s;    
    if(nargs==2)
    {
        for(s=args[1];*s!='\0';s++)
        {
            if(!isdigit(*s))
            {
                printf("Not a number \n");
                endprocess();
                return 0;
            }
        }
        count=atoi(args[1]);
    }


    // if there are no argument passed 
    else if(nargs==1)
    {
        count=200;
    }

    resume(create(producer,1024,20,"producer",1,count));
    resume(create(consumer,1024,20,"consumer",1,count));
    // wait for the producer/consumer to complete;
    wait(complete);
    
    endprocess();

    return 0;
}


/* signal  the "run" process that  prodcon process is completed */
void endprocess()
{
    signal(completecmd);

}