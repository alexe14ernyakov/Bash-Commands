#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stddef.h>

#define _GNU_SOURCE

struct linux_dirent {
	unsigned long  d_info;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};

int main(int argc, char** argv){
	const char* dir;
	const int buf_size = 1024;

	if(argc > 2){
		fprintf(stderr, "ls: invalid argument number\n");
		exit(1);
	}

	if(argc == 2){
		dir = argv[1];
	}
	else{
		dir = ".";
	}

	int fd = open(dir, O_RDONLY);
	if(fd == -1){
		perror("ls");
		exit(1);
	}

	char buffer[buf_size];
	int count, offset = 0;

	do{
		count = syscall(SYS_getdents, fd, (struct linux_dirent*)buffer, buf_size);

		if(count == -1){
			perror("ls");
			close(fd);
			exit(1);
		}

		while(offset < count){
			struct linux_dirent* ld = (struct linux_dirent*)(buffer + offset);
			//printf("%lu %lu %u %s\n", ld->d_info, ld->d_off, ld->d_reclen, ld->d_name);
			printf("%s\n", ld->d_name);
			//write(0, ld->d_name, ld->d_reclen - 2 - offsetof(struct linux_dirent, d_name));
			offset += ld->d_reclen;
		}
	} while(count != 0);

	close(fd);

	return 0;		
}
