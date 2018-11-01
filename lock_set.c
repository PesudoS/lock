#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/* lock_set() function */
void lock_set(int fd, int type)
{
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	while(1)
	{
		lock.l_type = type;
		/* according to different type lock or unlock file */
		if((fcntl(fd, F_SETLK, &lock)) == 0)
		{
			if(lock.l_type == F_RDLCK)
				printf("read lock set by %d", getpid());
			else if(lock.l_type == F_WRLCK)
				printf("write lock set by %d", getpid());
			else if(lock.l_type == F_UNLCK)
				printf("release lock by %d\n", getpid());
			return;
		}	
		/* judge if file can be locked */
		fcntl(fd, F_GETLK, &lock);
		/* judge why file cannot be locked */
		if(lock.l_type != F_UNLCK)
		{
			/* file has a read lock */
			if(lock.l_type != F_RDLCK)
				printf("read lock already set by %d", lock.l_pid);
			/* file has a write lock */
			else if(lock.l_type == F_WRLCK)
				printf("write lock already set by %d\n", lock.l_pid);
			getchar();
		}
	}
}
