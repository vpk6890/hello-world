#include "stdio.h"
#include "sys/types.h"
#include "string.h"   
#include "dirent.h"
#include "pthread.h"
#include "stdlib.h"

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
void sum (char command[]){

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
void mul (char command[]){

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
        closedir(d);
    }
}


int oprStrCheck(char oprStr[]){
   
	char *subStrMatch = NULL;
	int i,err;
	pthread_t sumThread, lcmThread, bprimeThread;
	
	if ( strstr(oprStr,"sum") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &sum, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"mul") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &mul, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"sub") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &sub, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"div") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &division, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"gcd") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &gcdFunc, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"lcm") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &lcm, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"ls") == oprStr) {		
		removeChar(oprStr,' ');
		if (strcmp(oprStr,"ls") == 0) {
			err = pthread_create(&sumThread, NULL, &ls, NULL);
			if ( err != 0 ){
				printf("\ncan't create thread :[%s]", strerror(err));
				exit(EXIT_FAILURE);
			}
			pthread_join( sumThread, NULL);
		}
		else {
			printf("No parameter is required for ls command.\n");
		}
	}
	else if ( strstr(oprStr,"bprime") == oprStr) {				
		err = pthread_create(&sumThread, NULL, &bprime, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
	}
	else if ( strstr(oprStr,"sprime") == oprStr) {				
		err = pthread_create(&sumThread, NULL, &sprime, oprStr);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(EXIT_FAILURE);
		}
		pthread_join( sumThread, NULL);
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
    
    do {

#if 0
		*userAccount=getenv("USER");
#endif	
		printf("\n%s $> ", userAccount);
        gets(userResponse);
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
    }while(1) ;
}
