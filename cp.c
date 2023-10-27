#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "cp: incorrect argument number\n");
		exit(1);
	}

	int source = open(argv[1], O_RDONLY);

	if(source == -1){
		perror("cp");
		exit(1);
	}

	int dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);

	if(dest == -1){
		perror("cp");
		exit(1);
	}

	const int buf_size = 1;
	char buffer[buf_size];

	size_t count;
	do{
		count = read(source, buffer, buf_size);
		if (count == -1){
			perror("cp");
			close(source);
			close(dest);
			exit(1);
		}
		if(write(dest, buffer, count) == -1){
			perror("cp");
			close(source);
			close(dest);
			exit(1);	
		}		
	} while(count == buf_size);

	close(source);
	close(dest);

	return 0;
}
