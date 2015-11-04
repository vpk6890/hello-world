#include "stdio.h"
#include "sys/types.h"
#include "string.h"   
#include "dirent.h"
#include "pthread.h"

#define LOOP (100)

void RemoveSpaces(char* source)
{
	char* i = source;
	char* j = source;
	while(*j != 0)
	{
		*i = *j++;
		if(*i != ' ')
		i++;
	}
	*i = 0;
}

void sum (char command[]){
	
	char temp1[100] ;
	char *temp2 = NULL;
    printf("CAME\n");
	if ( strstr(command,"(") != NULL && strstr(command,")") != NULL && strstr(command,",") != NULL ){
		temp2 = strrchr (command, '(');
		//memmove(temp1, temp2, strlen(temp2));
		printf("the arguments is %s \n",temp1);
	} 
	else {
		printf("Please enter proper parameters: sum(num1, num2, ... ) \n");
	} 
}

void lcm (char command[]){
    printf("lcm");
}

void prime(char command[]){
    printf("prime");
}

void ls(){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\t", dir->d_name);
        }
        closedir(d);
    }
}

void childProcess(void){
    int i;
    for ( i = 0; i < LOOP; i++){
        printf("Child is running i is %d\n",i);
    }
    printf("Child Process is done\n");
}

void parentProcess(void){
    int i;
    for ( i = 0; i < LOOP; i++){
        printf("parent is running i is %d\n",i);
    }
    printf("parent Process is done\n");
}

int oprStrCmp( char *oprStr1, char *oprStr2 ){
	
	int strMatch = 0;
	while( *oprStr1 != '\0' ){
		if( *oprStr2 != ' ') {		
			if ( *oprStr2 == *oprStr1 ) {
				strMatch++;
			}
			else {
				break;
			}
			oprStr1++;		
		}
		oprStr2++;
	}
	
	if (strMatch == strlen(oprStr1)) {
		return 1;
	} 
	return 0;
}

int oprStrCheck(char oprStr[]){
   
	char *subStrMatch = NULL;
	int i,err;
	pthread_t sumThread, lcmThread, bprimeThread;
	
	if ( strstr(oprStr,"sum") == oprStr) {		
		err = pthread_create(&sumThread, NULL, &sum, NULL);
		if ( err != 0 ){
			printf("\ncan't create thread :[%s]", strerror(err));
			exit(0);
		}
		pthread_join( sumThread, NULL);
		printf("Matched\n");
	}
	// else if () {
	
	// }
	// else if () {
	
	// }
	else {
		printf("Unavailable command. Please enter correct command.\n");
	}
    
    // for ( i = 0 ; i < 4 ; i++ ) {
		// if (oprStrCmp(opertions[i],optStr))
		// {	
			// *subStrMatch = opertions[i];
			// printf("String match %s\n",optStr);
			// return 1;
		// }
	// }
	
	
	return 0;
    
}

void main(void){
    
    pid_t pid;
    char userResponse[100];
       
    do {
		printf("user_account $> ");
        gets(userResponse);
		RemoveSpaces(userResponse);
		
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
				//childProcess();
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
