#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd;
	/* First open a file */
	fd = open("hello", O_RDWR | O_CREAT, 0666);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	/* read lock the file */
	lock_set(fd, F_RDLCK);
	getchar();
	/* unlock the file */
	lock_set(fd, F_UNLCK);
	close(fd);
	exit(0);
}
