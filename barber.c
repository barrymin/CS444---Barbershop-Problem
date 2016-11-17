#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>


sem_t mutex,customers,barbers, cutting;
int count = 0;/*The number of customers waiting*/
int n = 5;

void* barber(void *);
void* customer(void *);
void get_haircut();
void cut_hair();
int generate_random_num(int, int);

int main(int argc,char *argv[])
{
	if(argc == 2){
		n = atoi(argv[1]);	
   	}
	printf("Number of waiting chairs is %d\n",n);
	srand(time(NULL));
	pthread_t barbert;
 
	/*Semaphore initialization*/
	sem_init(&mutex,0,1);
	sem_init(&customers,0,0);
	sem_init(&barbers,0,1);
	sem_init(&cutting,0,0);
 
	/*Barber thread initialization*/
	pthread_create(&barbert,NULL,barber,NULL);

	/*Dispatch customer threads*/
	while(1){
		pthread_t customert;
		pthread_create(&customert,NULL,customer,NULL);
		sleep(generate_random_num(0,6));
 	}
	pthread_join(barbert,NULL);
 
	return 0;
}
 
void* barber(void *arg)
{
	while(1)
	{	
		if(count ==0)
			printf("Barber is sleeping..\n");
		sem_wait(&customers);            
		sem_wait(&mutex);
		count--;
		sem_post(&mutex);
		cut_hair(); 
		sem_post(&barbers);  
	}
}
 
void* customer(void *arg)
{
	sem_wait(&mutex);
	printf("Customer Entering\n");
	if(count<n)
	{
		count++;
		printf("Customers waiting = %d\n",count);
		sem_post(&mutex);
		sem_post(&customers);
		sem_wait(&barbers);
		get_haircut();
		printf("Customer got a hair cut and is LEAVING\n");
	}
	else{
		sem_post(&mutex);
		printf("Full chairs..Customer is LEAVING\n");
	}
	return;
}

void cut_hair(){
	printf("Barber cutting hair\n");
	sem_wait(&cutting);
}
void get_haircut(){
	printf("Customer getting hair cut\n");
	sleep(generate_random_num(3,5));
	sem_post(&cutting);
}

int generate_random_num(int a,int b){
	return rand() % b + a;
}

