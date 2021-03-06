#include "stdio.h"
#include "sys/types.h"
#include "string.h"   
#include "dirent.h"
#include "pthread.h"
#include "stdlib.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>


static char (*historyArray)[100];
static char *RawUserResponse;
static int  *ArrayIndex;
static int *ValidCommand; 

void removeChar(char *str, char charTobeRem ) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != charTobeRem) dst++;
    }
    *dst = '\0';
}

int getArgs(char *str, double args[]){
	int noOfArgs = 0, i = 0;
	char *token = strtok(str, ",");
    while(token) {
		args[i] = atof(token);
		noOfArgs++;
		i++;
        token = strtok(NULL, ",");
    }
	return noOfArgs;
}

int getArgsInt(char *str, long int args[]){
	int noOfArgs = 0, i = 0;
	char *token = strtok(str, ",");
    while(token) {
		args[i] = (long int) atoi(token);
		noOfArgs++;
		i++;
        token = strtok(NULL, ",");
    }
	return noOfArgs;
}


/* sum function*/
void *sum (char command[], int *ValidCmd){
   
	char *temp1 = NULL;
	double sum = 0;
	double args[1000]; 
	int i, noOfParam = 0;
   
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){

		temp1 = strrchr (command, '(');  // Getting substring which contains arguments.
		removeChar(temp1,'('); 			 // Removing '('
		removeChar(temp1,')'); 			 // Removing ')'
		noOfParam = getArgs(temp1,args); // Getting number of arguments.
		
		if ( noOfParam > 1 ){
			for( i = 0; i < noOfParam; i++) {
				sum = sum + args[i];
			}
			printf("%lf\n",sum);
			*ValidCommand = 1;
			return ;
		} 
		else{
			printf("Please enter proper parameters: sum(num1, num2, ... ) \n");
			return ;
		}
	} 
	else {
		printf("Please enter proper parameters: sum(num1, num2, ... ) \n");
		return ;
	} 
}

/* Multiply function*/
void *mul (char command[]){

	char *temp1 = NULL;
	double mul = 1;
	double args[1000]; 
	int i, noOfParam = 0;
   
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		
		temp1 = strrchr (command, '(');  // Getting substring which contains arguments.
		removeChar(temp1,'('); 			 // Removing '('
		removeChar(temp1,')'); 			 // Removing ')'
		noOfParam = getArgs(temp1,args); // Getting number of arguments.
		
		if ( noOfParam > 1 ){
			for( i = 0; i < noOfParam; i++) {
				mul = mul * args[i];
			}
			printf("%lf\n",mul);
			*ValidCommand = 1;
			return ;
		} 
		else{
			printf("Please enter proper parameters: mul(num1, num2, ... ) \n");
			return ;
		}
	} 
	else {
		printf("Please enter proper parameters: mul(num1, num2, ... ) \n");
		return ;
	} 
}

/* Subtract function*/
void sub (char command[]){

	char *temp1 = NULL;
	double sub = 0;
	double args[1000]; 
	int i, noOfParam = 0;
   
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		
		temp1 = strrchr (command, '(');  // Getting substring which contains arguments.
		removeChar(temp1,'('); 			 // Removing '('
		removeChar(temp1,')'); 			 // Removing ')'
		noOfParam = getArgs(temp1,args); // Getting number of arguments.
		
		if ( noOfParam > 1 ){
			for( i = 1; i < noOfParam; i++) {
				sub = args[0] - args[i];
				printf("%lf\n",sub);
			}
			*ValidCommand = 1;
			return ;
		} 
		else{
			printf("Please enter proper parameters: sub(num1, num2, ... ) \n");
			return ;
		}
	} 
	else {
		printf("Please enter proper parameters: sub(num1, num2, ... ) \n");
		return ;
	} 
}


long int lcmOpr(long int a, long int b){
    long int temp = a;
    do{
         if(temp % b == 0 && temp % a == 0){
			break;
		 }
         temp++;
    }while(1);
   return temp;
}

void lcm(char command[]){
	
	char *temp1 = NULL;
	long int lcm = 0;
	long int args[1000]; 
	int i, noOfParam = 0;
	
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgsInt(temp1,args);  // Getting number of arguments.
		
		if ( noOfParam > 1 ){
		
			lcm = args[0]; 
			i = 1;
			while( i < noOfParam){
				if (lcm > args[i]) {
					lcm = lcmOpr(lcm,args[i]);
				}
				else {
					lcm = lcmOpr(args[i],lcm);
				}
				i++;
			}
			printf("%li\n",lcm);
			*ValidCommand = 1;
			return ;
		} 
		else{
			printf("lcm should have minimum two parameters. Ex:- lcm(num1, num2, ... ) \n");
			return ;
		}
	}
	else{
		printf("lcm should have minimum two parameters. Ex:- lcm(num1, num2, ... ) \n");
		return ;
	}
}

/* bprime function is for finding biggest prime number */
void bprime(char command[])
{
	char *temp1 = NULL;
	int i,noOfParam = 0;
	long int args[1000];
	int var, primeCheck, bprime = 0;
	
	
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgsInt(temp1,args);  // Getting number of arguments.
			
		if (noOfParam > 0) {
			for (i = 0; i < noOfParam; i++) { 
				primeCheck = 1;
				for ( var = 2 ; var <= (args[i] - 1) ; var++ )
				{ 
					if ( (args[i]%var) == 0 ) {
						primeCheck = 0;
						break;
					}
				}
				if (primeCheck) {
					if (bprime < args[i]) {
						bprime = args[i];
					}
				} 
			}
			if (bprime != 0) {
				*ValidCommand = 1;
				printf("%d\n",bprime);
			} 
			else {
				printf("None of the arguments are prime number!!!!\n");
			}
		}
		else {
			printf("bprime must have atleat one parameter!!! For example bprime(num1, num2, ... )\n");
			return;
		}
	}
	else {
		printf("bprime must have atleat one parameter!!! For example bprime(num1, num2, ... )\n");
		return;
	}
}

/* sprime function is for finding smallest prime number */
void sprime(char command[])
{
	char *temp1 = NULL;
	int i,noOfParam = 0;
	long int args[1000];
	int var, primeCheck, sprime = -1;
	
	
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgsInt(temp1,args);  // Getting number of arguments.
			
		if (noOfParam > 0) {
			for (i = 0; i < noOfParam; i++) { 
				primeCheck = 1;
				for ( var = 2 ; var <= (args[i] - 1) ; var++ )
				{ 
					if ( (args[i]%var) == 0 ) {
						primeCheck = 0;
						break;
					}
				}
				if (primeCheck) {
					if ( sprime == -1) {
						sprime = args[i];
					} else {
						if (sprime > args[i]) {
							sprime = args[i];
						}
					} 
				
				} 
			}
			if (sprime != 0) {
				*ValidCommand = 1;
				printf("%d\n",sprime);
			} 
			else {
				printf("None of the arguments are prime number!!!!\n");
			}
		}
		else {
			printf("sprime must have atleat one parameter!!! For example sprime(num1, num2, ... )\n");
			return;
		}
	}
	else {
		printf("sprime must have atleat one parameter!!! For example sprime(num1, num2, ... )\n");
		return;
	}
}

/* Division function */
void division(char command[])
{
	char *temp1 = NULL;
	int i,noOfParam = 0;
	double args[1000];
		
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL){
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgs(temp1,args);  // Getting number of arguments.
		if (noOfParam == 2) {
			if (args[1] == 0) {
				printf("Division by zero! Aborting!!!\n");
				return;
			}
			else {
				printf("%G\n", args[0]/args[1]);
				ValidCommand = 1;
				return;
			}
		}
		else if ( noOfParam < 2) {
			printf("Div must have exactly have two parameters!!! For example div(num1, num2)\n");
			return;
		}
		else {
			printf("Div must have exactly have two parameters!!! For example div(num1, num2)\n");
			return;
		}
	}
	else {
		printf("Div must have exactly have two parameters!!! For example div(num1, num2)\n");
		return;
	}
	
}

/* GCD function */
int gcd(int x, int y)
{
    int r;

    if (x <= 0 || y <= 0) return(0);
    while ((r = x % y) != 0)
    {
        x = y;
        y = r;
    }
    return(y);
}

void gcdFunc(char command[])
{
	char *temp1 = NULL;
	int i,noOfParam = 0;
	long int args[1000];
	int g;
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL ){
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgsInt(temp1,args);  // Getting number of arguments.
		if (noOfParam > 1) {
			g = args[0];
			for (i = 1; i < noOfParam; i++)
				g = gcd(g, args[i]);
			printf("%d\n",g);
			*ValidCommand = 1;
			return;
		}
		else {
			printf("gcd must have minimum two number. For example gcd(num1, num2, ... )\n");
			return;
		}
	}
	else {
		printf("gcd must have minimum two number. For example gcd(num1, num2, ... )\n");
		return;
	}
}

void collatzSubFunc(int Number) {
	printf("%d",Number);
	do{
		if ( (Number%2) == 0) {
			Number = Number/2;
		} else{
			Number = (Number*3)+1;
		}
		printf(", %d",Number);
	}while(Number != 1);
	printf("\n");
}

void collatz(char command[])
{
	char *temp1 = NULL;
	int i,noOfParam = 0;
	long int args[1000];
	
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL ){
		temp1 = strrchr (command, '(');      // Getting substring which contains arguments.
		removeChar(temp1,'('); 			     // Removing '('
		removeChar(temp1,')'); 			     // Removing ')'
		noOfParam = getArgsInt(temp1,args);  // Getting number of arguments.
		if (noOfParam > 0) {
			
			for (i = 0; i < noOfParam; i++)
			{	
				collatzSubFunc(args[i]);
			}
			*ValidCommand = 1;
			return;
		}
		else {
			printf("collatz must atleast have one parameter. For example gcd(num1,... )\n");
			return;
		}
	}
	else {
		printf("collatz must atleast have one parameter. For example gcd(num1,... )\n");
		return;
	}
}

void ls(void){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\t", dir->d_name);
        }
		printf("\n");
		*ValidCommand = 1;
        closedir(d);
    }
}

void history(void){

	int Counter;
	for ( Counter = 0; Counter < *ArrayIndex; Counter++){
		printf("%s\n",historyArray[Counter]);
	}
}

int oprStrCheck(char oprStr[]){
   
	char *subStrMatch = NULL;
	int i,err;
	pthread_t sumThread, mulThread, SubThread, divThread, gcdThread, lcmThread, lsThread, bprimeThread, sprimeThread, historyThread;
	
	
		if ( strstr(oprStr,"sum") == oprStr) {	
			err = pthread_create(&sumThread, NULL, &sum, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( sumThread, NULL);
			if ( ValidCommand == 1) {
				
			}
		}
		else if ( strstr(oprStr,"mul") == oprStr) {		
			err = pthread_create(&mulThread, NULL, &mul, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( mulThread, NULL);
		}
		else if ( strstr(oprStr,"sub") == oprStr) {		
			err = pthread_create(&SubThread, NULL, &sub, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( SubThread, NULL);
		}
		else if ( strstr(oprStr,"div") == oprStr) {		
			err = pthread_create(&divThread, NULL, &division, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( divThread, NULL);
		}
		else if ( strstr(oprStr,"gcd") == oprStr) {		
			err = pthread_create(&gcdThread, NULL, &gcdFunc, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( gcdThread, NULL);
		}
		else if ( strstr(oprStr,"lcm") == oprStr) {		
			err = pthread_create(&lcmThread, NULL, &lcm, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( lcmThread, NULL);
		}
		else if ( strstr(oprStr,"ls") == oprStr) {		
			removeChar(oprStr,' ');
			if (strcmp(oprStr,"ls") == 0) {
				err = pthread_create(&lsThread, NULL, &ls, NULL);
				if ( err != 0 ){
					printf("\ncan't create thread :[%s]", strerror(err));
					exit(EXIT_FAILURE);
				}
				pthread_join( lsThread, NULL);
			}
			else {
				printf("No parameter is required for ls command.\n");
			}
		}
		else if ( strstr(oprStr,"bprime") == oprStr) {				
			err = pthread_create(&bprimeThread, NULL, &bprime, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( bprimeThread, NULL);
		}
		else if ( strstr(oprStr,"sprime") == oprStr) {				
			err = pthread_create(&sprimeThread, NULL, &sprime, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( sprimeThread, NULL);
		}
		else if ( strstr(oprStr,"collz") == oprStr) {				
			err = pthread_create(&sprimeThread, NULL, &collatz, oprStr);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( sprimeThread, NULL);
		}
		else if ( strstr(oprStr,"history") == oprStr) {		printf("CAME \n");		
			err = pthread_create(&historyThread, NULL, &history, NULL);printf("historyArray is %s ----------->\n",historyArray[0]); printf("historyArray is %s ----------->\n",historyArray[1]);	
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( historyThread, NULL);
		}
		else {
			printf("Unavailable command. Please enter correct command.\n");
		}
		
		return 0;
}

void main(void){
    
    pid_t pid;
    char userResponse[100];
	char userAccount[100] = "user_account";
	int getValidCommand = 0;
    
	/* Assigning the shared memory to variables */
	historyArray = (char (*)[100])mmap(NULL, (sizeof (historyArray) * 100 * 100), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	RawUserResponse = (char *) mmap(NULL, (sizeof (RawUserResponse) * 100), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	ArrayIndex =  (int *) mmap(NULL, sizeof (ArrayIndex), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	ValidCommand = (int *) mmap(NULL, sizeof (ValidCommand), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	*ValidCommand = 0;
	*ArrayIndex = 0;

    do {

		printf("\n%s $> ", userAccount);
        gets(userResponse);
		strcpy(RawUserResponse, userResponse);printf("RawUserResponse is %s\n",RawUserResponse);
		removeChar(userResponse,' '); // Removing whitespace.
		
		
		if ( strstr(userResponse,"quit") != NULL) {
			if (strcmp(userResponse,"quit") == 0) {
				printf("bye\n");
				break;
			}
			else {
				printf("Unavailable command. Please enter correct command.\n");
			}
		} 
		else 
		{	
			pid = fork();
			if ( pid == 0 ){
				oprStrCheck(userResponse);
				exit(0);
			}
			else if ( pid > 0) {
			
				int returnStatus;    
				waitpid(pid, &returnStatus, 0);  
				
				if (returnStatus == 1)      
				{
					printf("The child process terminated with an error!.\n");   
					exit(0);
				}
			}
			else {
				printf("Child process was not created\n!!!!");
				exit(0);
			}
		}
		
		if ( *ValidCommand == 1) {
				strcpy(historyArray[(*ArrayIndex)], RawUserResponse);
				(*ValidCommand) = 0;
				(*ArrayIndex) = (*ArrayIndex)+1;
		}
				
		*ValidCommand = 0;
		
    }while(1) ;
}
