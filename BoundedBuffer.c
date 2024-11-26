/* Name: Matthew Tran (ID: 113606493), Username: cs141 (cs141@cs141.cs.ourcloud.ou.edu)*/
/* Github Username: Karmalized */
/* OU 4X4: Tran0208 */

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFERSIZE 15

//Pthreads
pthread_t producerThread[1]; //producer thread for producer function
pthread_t consumerThread[1]; //consumer thread for consumer function
pthread_attr_t attribute[1]; //attribute pointer

//SharedBuffer
char charBuffer[BUFFERSIZE]; //Shared Buffer alloted for 15 slots
int head = 0; //head points to where our producer produces a character for the buffer, it is the next free location to place a new item
int tail = 0; //tail points to where our consumer consumes a character for the buffer, it is the next full location to remove an item from

//Semaphores
sem_t full, empty, mutex;

/*Functions to Implement for this Project*/
/*public void *producer(void *param)*/
void *producerFunction(void *param){
	char newChar; //character from file is stored here!
	FILE* readingFile; //implemented file for reading character
	readingFile = fopen("mytest.dat", "r"); //this is the file, mytest.dat that characters will be read from
	while(fscanf(readingFile, "%c", &newChar) != EOF){ // read until file is empty

		sem_wait(&empty); //reduce the number of available spaces by 1
		sem_wait(&mutex); //locks section and gets hold of CPU

		charBuffer[head] = newChar; //adds a character into the shared buffer
		head = (head + 1) % BUFFERSIZE; //increments head pointer to next available spot

		sem_post(&mutex); //unlock critical section
		sem_post(&full); //increases number of taken spaces by 1
	}
	//Once the file is empty the producer inputs the special character * into the buffer to halt the file reading process
	sem_wait(&empty);
		sem_wait(&mutex);

		charBuffer[head] = '*';
		head = (head + 1) % BUFFERSIZE;

		sem_post(&mutex);
		sem_post(&full);
		fclose(readingFile);
}

void *consumerFunction(void *param){
	char obtainedChar; //stores the obtained character from the file
	while(obtainedChar != '*'){ //loops and grabs character from the buffer to output to screen until it finds the * character
	sem_wait(&full); //decreases the number of taken spaces by 1 (since it's consuming a character)
	sem_wait(&mutex); //locks critical section

	sleep(1); //sleep done between character reads since consumer is slower than producer
	obtainedChar = charBuffer[tail]; //reads character from buffer
	if(obtainedChar != '*'){ //if the character happens to be the special character, don't print it!
	printf("%c", obtainedChar); //prints the obtained character
	} else {
		printf("\n");
	}
	fflush(stdout); //and flushes it to the user interface
	tail = (tail+1) % BUFFERSIZE; //increments consumer pointer to next available character to consume

	sem_post(&mutex); //unlocks critical section
	sem_post(&empty); //increases number of free spaces by 1
	}
}
/*public void *consumer(void *param)*/

int main(){

	/*Initialize Semaphores here!*/
	sem_init(&full,0,0); //Semaphore indicating how many full slots in the buffer there are, starts at 0
	sem_init(&empty,0,BUFFERSIZE); //Semaphore indicating how many empty slots in the buffer there are, starts at 15 (available)
	sem_init(&mutex,0,1); //mutex lock to enable or disable availability for a certain buffer slot in the buffer

	fflush(stdout);
	/*Required to schedule thread independently*/
	pthread_attr_init(&attribute[0]);
	pthread_attr_setscope(&attribute[0], PTHREAD_SCOPE_SYSTEM);
	/*End to schedule thread independently*/

	pthread_create(&producerThread[0], &attribute[0], producerFunction, NULL); //create the thread to complete file reading for file!
	pthread_create(&consumerThread[0], &attribute[0], consumerFunction, NULL); //create the thread to print file reading for file!

	//return to main function after function calls
	pthread_join(producerThread[0], NULL);
	pthread_join(consumerThread[0], NULL);

	//destroy semaphores after process completion
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);

	//terminates threads
	pthread_exit(NULL);
	return 0;
}	
