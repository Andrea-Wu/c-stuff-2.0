#include <stdio.h>

int main(int argc, char* argv[]){
	FILE* newfile = fopen(argv[1],"a");
	printf("%s\n", argv[1]);
	if(newfile == NULL){
		printf(":(\n");
	}

	fputs(".", newfile);
	int i;
	for(i = 0; i < 10; i++){
		fputs(" ", newfile);
	}
	fputs(".", newfile);
	fclose(newfile);
}
