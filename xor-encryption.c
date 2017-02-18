#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO:
	1) Encrypt last few bytes (size < chunk_size)
	2) Why are some characters lost?
*/

// Function declarations
void encode_string(char *);

// Declaring key as global variable
// Because multiple functions will need to access it repeatedly
// Better performance
char *key;

int main(int argc, char *argv[]) {
	
	// Making sure filename is entered as argument
	if (argc < 3) {
		printf("ERROR: Enter filenames (input and output) as a command line argument!\n");
		printf("Exiting...\n");
		return 0;
	}

	// Requirements for the algorithm
	// filestream, key(100B), chunk_size, output_filestream
	FILE *main_file, *out_file;
	key = malloc(100);
	int chunk_size;

	// Open the input file (given as the first cammand line argument)
	main_file = fopen(argv[1], "rb");
	if (!main_file) {
		printf("ERROR: Input file could not be read");
		return 0;
	}

	// Open the output file (given as the second command line argument)
	out_file = fopen(argv[2], "wb");
	if (!out_file) {
		printf("ERROR: Could not create output file");
		return 0;
	}

	// Get key from user
	// And update the chunk_size
	printf("Enter key (l<=100): ");
	scanf("%s", key);
	chunk_size = (int) strlen(key);
	
	// Read the file iteratively into sub_string
	char *sub_string = malloc(chunk_size);
	while (fread(sub_string, chunk_size, 1, main_file) == 1) {
		
		// Encode the sub_string and write it to out_file
		encode_string(sub_string);
		fwrite(sub_string, chunk_size, 1, out_file);
	}
	
	fclose(main_file);
	fclose(out_file);
	return 1;
}

void encode_string(char *string) {
	int counter = 0;

	while (counter < strlen(string)) {
		int a = string[counter];
		int b = key[counter];
		int c = a^b;
		string[counter] = (char) c;
		counter++;
	}

	return;
}

/*	int counter;
	FILE *ptr_myfile;
	int x;

	ptr_myfile = fopen("abc.bin", "rbx");
	if(!ptr_myfile) {
		printf("Unable to open file!");
		return 0;
	}

	for (counter = 1; counter<=10; counter++) {
		x = counter;
		fwrite(&x, 1, 1, ptr_myfile);
	}

	
	for (counter=1; counter<=12; counter++) {
		if (fread(&x, 1, 1, ptr_myfile) == 1)
			printf("%d\n", x);
	}
		
	fclose(ptr_myfile);
	return 1; */
