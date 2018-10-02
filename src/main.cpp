#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

volatile sig_atomic_t usr1Happened = 1;

void SIGUSR1Handler(int sig);

int main(){
	struct sigaction event;
	event.sa_flags = 0;
	event.sa_handler = SIGUSR1Handler;

	sigemptyset(&event.sa_mask);

	if(sigaction(SIGUSR1, &event, NULL) == -1){
		perror("sigaction");
		exit(1);
	}

	cout << "Running... (" << getpid() << ")" << endl;
	while(usr1Happened);
	cout << "Exiting... (" << getpid() << ")" << endl;
	return 0;
}

void SIGUSR1Handler(int sig){
	cout << "SIGUSR1 processed on " << getpid() << endl;
	usr1Happened = 0;
}
