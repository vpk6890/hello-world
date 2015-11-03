#include "stdio.h"
#include "sys/types.h"
#include "string.h"
#include "dirent.h"
#include "regex.h"    

#define LOOP (100)

void sum (){
    printf("SUM\n");
}

void lcm (){
    printf("lcm");
}

void prime(){
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

int oprStrCmp(char opr[]){
    
     regex_t regex;
     int reti;
     char *c = NULL;
     char msgbuf[100];
     
    /* Compile regular expression */
    reti = regcomp(&regex, "^a[[:alnum:]]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    reti = regexec(&regex, "quit", 0, NULL, 0);
    if (!reti) {
        puts("Match");
        return 1;
    }
    else if (reti == REG_NOMATCH) {
        return 0;
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);
    
}

int oprStrCheck(char oprStr[]){
     
     regex_t regex;
     int reti;
     char *c = NULL;
     char msgbuf[100];
     int i;
     char operations[10][10] = { {"quit"}, {"sum"}, {"lcm"}, {"bprime"} } ;
        
    /* Execute regular expression */
    for ( i = 0 ; i < 4 ; i++ ) {
        oprStrCmp(*(operations + i));
    }
    
}

void main(void){
    
    pid_t pid;
    char userResponse[100];
    pid = fork();
    int strCmpVal = 0;
    
    do {
    
        //if () {
            if ( pid == 0 ){
                childProcess();
                 exit(0);
            }
            else if ( pid > 0) {
            
                int returnStatus;    
                waitpid(pid, &returnStatus, 0);  
                
                if (returnStatus == 0)  // Verify child process terminated without error.  
                {
                    printf("The child process terminated normally.");    
                }

                if (returnStatus == 1)      
                {
                    printf("The child process terminated with an error!.\n");   
                    exit(0);
                }
                parentProcess();
                
            }
            else {
                printf("Child process was not created\n!!!!");
                exit(0);
            }

        printf("user_account $> ");
        gets(userResponse);
        strCmpVal = oprStrCheck(userResponse);
    }while( strCmpVal != 0) ;

}
