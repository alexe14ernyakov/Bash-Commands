#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "chmod: invalid argument number\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; argv[1][i] != '\0'; i++){
		if(argv[1][i] > '7' || argv[1][i] < '0'){
			fprintf(stderr, "chmod: invalid mode\n");
			exit(EXIT_FAILURE);
		}
	}

	unsigned long rights = strtoul(argv[1], NULL, 8);
	
	if(rights > 4095){
		fprintf(stderr, "chmod: invalid mode\n");
		exit(EXIT_FAILURE);		
	}
	
	if (chmod(argv[2],(mode_t)rights) == -1){
		perror("chmod");
		exit(EXIT_FAILURE);
	} 
	
	return 0;
}

