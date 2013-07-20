#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#define mutex1 1
#define mutex2 2
#define mutex3 3
#define bookac 4
#define cnclac 5
#define bookcc 6
#define cnclcc 7
#define booksl 8
#define cnclsl 9
#define check 10
int ac_a=60;
int cc_a=40;
int sl_a=90;
static struct sembuf upmutex1={mutex1,1,0};
static struct sembuf downmutex1={mutex1,-1,0};
static struct sembuf upmutex2={mutex2,1,0};
static struct sembuf downmutex2={mutex2,-1,0};
static struct sembuf upmutex3={mutex2,1,0};
static struct sembuf downmutex3={mutex3,-1,0};
static struct sembuf upbookac={bookac,1,0};
static struct sembuf downbookac={bookac,-1,0};
static struct sembuf upcnclac={cnclac,1,0};
static struct sembuf downcnclac={cnclac,-1,0};
static struct sembuf upbookcc={bookcc,1,0};
static struct sembuf downbookcc={bookcc,-1,0};
static struct sembuf upcnclcc={cnclcc,1,0};
static struct sembuf downcnclcc={cnclcc,-1,0};
static struct sembuf upbooksl={booksl,1,0};
static struct sembuf downbooksl={booksl,-1,0};
static struct sembuf upcnclsl={cnclsl,1,0};
static struct sembuf downcnclsl={cnclsl,-1,0};
static struct sembuf upcheck={check,1,0};
static struct sembuf downcheck={check,-1,0};

void book(int semid,int *ac_avail,int *cc_avail,int *sl_avail)
{
	int c,t;
	printf("Enter the class (1:ac 2:cc 3:sl):");
	scanf("%d",&c);
	switch(c)
	{
		case 1:semop(semid,&downmutex1,1);
		       semop(semid,&downcheck,1);
		       semop(semid,&downcnclac,1);
		       printf("No. of tickets to be booked :");
		       scanf("%d",&t);
		       *ac_avail=*ac_avail-t;
			printf("No. of tickets booked in ac :%d\n",t);
			printf("available :%d",*ac_avail);
			semop(semid,&upmutex1,1);
			semop(semid,&upcheck,1);
			semop(semid,&upcnclac,1);
			break;
		case 2: semop(semid,&downmutex2,1);
			semop(semid,&downcheck,1);
			semop(semid,&downcnclcc,1);
			printf("No. of tickets to be booked :");
		        scanf("%d",&t);
		        *cc_avail=*cc_avail-t;
			printf("No. of tickets booked in cc :%d\n",t);
			semop(semid,&upmutex2,1);
			semop(semid,&upcheck,1);
			semop(semid,&upcnclcc,1);
			break;
		case 3: semop(semid,&downmutex3,1);
			semop(semid,&downcheck,1);
			semop(semid,&downcnclsl,1);
			printf("No. of tickets to be booked :");
		        scanf("%d",&t);
		        *sl_avail=*sl_avail-t;
			printf("No. of tickets booked in sl :%d\n",t);
			semop(semid,&upmutex3,1);
			semop(semid,&upcheck,1);
			semop(semid,&upcnclsl,1);
			break;
		default: printf("No other classes");
			 break;
	}
}
				
void checkall(int semid,int *ac_avail,int *cc_avail,int *sl_avail)
{
	int c,t;
	int count=0;
	printf("Enter the class (1:ac 2:cc 3:sl) :");
	scanf("%d",&c);
	switch(c)
	{
		case 1: semop(semid,&downmutex1,1);
			semop(semid,&downbookac,1);
			semop(semid,&downcnclac,1);
				count++;
			semop(semid,&upmutex1,1);
			printf("No. of tickets available :%d",*ac_avail);
			semop(semid,&downmutex1,1);
				count--;
			if(count==0)
			{
				semop(semid,&upbookac,1);
				semop(semid,&upcnclac,1);
			}
			semop(semid,&upmutex1,1);
			break;
		case 2: semop(semid,&downmutex2,1);
			semop(semid,&downbookcc,1);
			semop(semid,&downcnclcc,1);
				count++;
			semop(semid,&upmutex2,1);
			printf("No. of tickets available :%d",*cc_avail);
			semop(semid,&downmutex2,1);
				count--;
			if(count==0)
			{
				semop(semid,&upbookcc,1);
				semop(semid,&upcnclcc,1);
			}
			semop(semid,&upmutex2,1);
			break;
		case 3: semop(semid,&downmutex3,1);
			semop(semid,&downbooksl,1);
			semop(semid,&downcnclsl,1);
				count++;
			semop(semid,&upmutex3,1);
			printf("No. of tickets available :%d",*sl_avail);
			semop(semid,&downmutex3,1);
				count--;
			if(count==0)
			{
				semop(semid,&upbooksl,1);
				semop(semid,&upcnclsl,1);
			}
			semop(semid,&upmutex3,1);
			break;
		default:printf("No other classes");
			break;
	}
}

void cancel(int semid,int *ac_avail,int *cc_avail,int *sl_avail)
{
	int c,t;
	printf("Enter the class (1:ac 2:cc 3:sl) :");
	scanf("%d",&c);
	switch(c)
	{
		case 1: semop(semid,&downmutex1,1);
			semop(semid,&downcheck,1);
			semop(semid,&downbookac,1);
			printf("No. of tickets to be cancelled :");
		        scanf("%d",&t);
		        *ac_avail=*ac_avail+t;
			if(*ac_avail==60)
			{
				printf("No ticket can be cancelled");	
				break;
			}
			printf("No. of tickets available in cc :%d\n",*ac_avail);
			semop(semid,&upmutex1,1);
			semop(semid,&upcheck,1);
			semop(semid,&upbookac,1);
			break;
		case 2: semop(semid,&downmutex2,1);
			semop(semid,&downcheck,1);
			semop(semid,&downbookcc,1);
			printf("No. of tickets to be cancelled :");
		        scanf("%d",&t);
			if(*cc_avail==40)
			{
				printf("No ticket can be cancelled");	
				break;
			}			
		        *cc_avail=*cc_avail+t;
			printf("No. of tickets available in cc :%d\n",*cc_avail);
			semop(semid,&upmutex2,1);
			semop(semid,&upcheck,1);
			semop(semid,&upbookcc,1);
			break;
		case 3: semop(semid,&downmutex3,1);
			semop(semid,&downcheck,1);
			semop(semid,&downbooksl,1);
			printf("No. of tickets to be cancelled :");
		        scanf("%d",&t);
			if(*sl_avail==90)
			{
				printf("No ticket can be cancelled");	
				break;
			}
		        *sl_avail=*sl_avail+t;
			printf("No. of tickets available in cc :%d\n",*sl_avail);
			semop(semid,&upmutex3,1);
			semop(semid,&upcheck,1);
			semop(semid,&upbooksl,1);
			break;
		default:printf("No other classes");
			break;
	}
}

int main()
{
	int shmid1,shmid2,shmid3;
	int *ac,*sl,*cc;
	int ac_avail,cc_avail,sl_avail;
	int semid,pid;
	char *s,*sh;
	int i=0,c;
	key_t key1,key2,key3,key4;
	key1=1234;
	key2=4567;
	key3=4352;
	key4=9876;
	shmid1=shmget(key1,sizeof(int),IPC_CREAT|0666);
	if(shmid1<0)
	{
		perror("shmget");
		exit(1);
	}
	shmid2=shmget(key3,sizeof(int),IPC_CREAT|0666);
	if(shmid2<0)
	{
		perror("shmget");
		exit(1);
	}
	shmid3=shmget(key4,sizeof(int),IPC_CREAT|0666);
	if(shmid3<0)
	{
		perror("shmget");
		exit(1);
	}
	pid=fork();
	if(pid==0)
	{
		ac=(int *)shmat(shmid1,NULL,0);
		sl=(int *)shmat(shmid2,NULL,0);
		cc=(int *)shmat(shmid3,NULL,0);
		*ac=ac_a;
		*sl=sl_a;
		*cc=cc_a;
		semid=semget(key2,10,IPC_CREAT|0777);
		if(semid<0)
		{
			perror("semid");	
			exit(1);
		}
		semctl(semid,mutex1,SETVAL,1);
		semctl(semid,mutex2,SETVAL,1);
		semctl(semid,mutex3,SETVAL,1);
		semctl(semid,bookac,SETVAL,1);
		semctl(semid,cnclac,SETVAL,1);
		semctl(semid,bookcc,SETVAL,1);
		semctl(semid,cnclcc,SETVAL,1);
		semctl(semid,booksl,SETVAL,1);
		semctl(semid,cnclsl,SETVAL,1);
		semctl(semid,check,SETVAL,1);
		printf("Welcome to the Railway reservation system");
		printf("\nEnter your choice (1:book 2:check 3:cancel 4:quit) :");
		scanf("%d",&c);
		while(c!=4)
		{
		switch(c)
		{
			case 1:book(semid,ac,cc,sl);
				break;
			case 2:checkall(semid,ac,cc,sl);
				break;
			case 3:cancel(semid,ac,cc,sl);
				break;
			default:printf("\nThank You\n");
				exit(0);
		}
		printf("\nEnter your choice (1:book 2:check 3:cancel 4:quit) :");
		scanf("%d",&c);
		}
	}
	else
	{
		wait(NULL);
		printf("Thank You......");
	}
}
