#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("MANAGER SIDE CHATBOX:\n\n");
	int fd1;
	char * Path = "/home/ubuntu/Latest/demo.txt";
	mkfifo(Path, 0666);

    char str1[100], str2[100];

    while(1)
    {

        fd1 = open(Path, O_RDONLY);
        read(fd1, str1, 100);
        
        printf("Costumer: %s\n", str1);
        close(fd1);

        fd1 = open(Path, O_WRONLY);
        fgets(str2, 100, stdin);
        if(str2=="Q")
        	system("exit");
        write(fd1, str2, strlen(str2)+1);
        close(fd1);        

    }
	return 0;	
}
