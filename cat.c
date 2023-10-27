#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
	const int buf_size = 1024;
	char  buffer[buf_size];
	int fd;
	size_t count;
	
	for(int i = 1; i < argc; i++){
		fd = open(argv[1], O_RDONLY);
		
		if(fd == -1){
			perror("cat");
			exit(1);
		}

		do{
			count = read(fd, buffer, buf_size);
			
			if(count == -1){
				perror("cat");
				close(fd);
				exit(1);
			}

			if(write(0, buffer, count) == -1){
				perror("cat");
				close(fd);
				exit(1);
			}
		} while(count == buf_size);

		close(fd);
	}

	return 0;
}
