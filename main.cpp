#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <fstream>
#include <string>
#include <unistd.h>
 
using namespace std;

void* WriteToFile(void*);
void* ReadFile(void*); 

sem_t r,w; 
ofstream qfwrite;
char filename[] = "./rezult.txt"; 
string str = "";
string buf;



int main(int argc, char **argv) { 
	pthread_t tidW,tidR;
	int n;
	sem_init(&w,0,0);
	sem_init(&r,0,0); 
	sem_post(&w);
	pthread_create(&tidW,NULL,&WriteToFile, (void*)1); 
	pthread_create(&tidR,NULL,&ReadFile, (void*)1); 
	pthread_join(tidW, NULL);
	pthread_join(tidR,NULL);
	sem_destroy(&w); 
	sem_destroy(&r); 
	return 0;
};

void* ReadFile(void *f)
{
	int max = (intptr_t)f;
	while(1)
	{
		sem_wait(&r);
			ifstream qfread(&filename[0]);
				while(getline(qfread, buf, '\n'))
					str = buf;
				cout << str << endl;
			qfread.close();
			usleep(50000);
		sem_post(&w);
	}
	return 0;
};

void* WriteToFile(void *f)
{
	int max = (intptr_t)f;
	qfwrite.open(&filename[0]); 
	while(1)
	{
		sem_wait(&w);
			qfwrite << pthread_self() << " - i=" << max++ << endl; 
			qfwrite << flush;
			cout << "Запись потока': " << endl;
			usleep(50000);
		sem_post(&r);
	}
	qfwrite.close();
	return 0;
};