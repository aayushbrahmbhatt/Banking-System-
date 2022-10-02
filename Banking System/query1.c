#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("                      || Reserve Bank Of DA ||                     \n\n");
	printf("**************************** Help Desk *************************\n\n");
    printf("Feel free to ask anything... \n\n");
	int fd;
	char * Path = "/home/ubuntu/Latest/demo.txt";
	mkfifo(Path, 0666);

    char arr1[100], arr2[100];

    while(1)
    {
        fd = open(Path, O_WRONLY);
        fgets(arr2, 100, stdin);
        if(arr2=="Q")
        	system("exit");
        
        write(fd, arr2, strlen(arr2)+1);
        close(fd);

        fd = open(Path, O_RDONLY);
        read(fd, arr1, sizeof(arr1));
        printf("Manager: %s\n", arr1);
        close(fd);

    }
	return 0;	
}
