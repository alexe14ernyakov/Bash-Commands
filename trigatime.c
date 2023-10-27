#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr, "trigatime: incorrect arguments number\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_RDONLY);
	
	if(fd == -1){
		perror("trigatime");
		exit(EXIT_FAILURE);
	}

	unsigned int flags;
	
	if(ioctl(fd, FS_IOC_GETFLAGS, &flags) == -1){
		perror("trigatime");
		close(fd);
		exit(EXIT_FAILURE);
	}

	if(flags & FS_NOATIME_FL){
		flags &= ~FS_NOATIME_FL;
	}
	else{
		flags |= FS_NOATIME_FL;
	}

	if(ioctl(fd, FS_IOC_SETFLAGS, &flags) == -1){
		perror("trigatime");
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);
	
	return 0;
}
