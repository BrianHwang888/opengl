#include <stdio.h>
#include <stdlib.h>

#include "../inc/file_utils.h"

const char* read_entire_file(const char* file_path) {
	FILE* fp = fopen(file_path, "rb");
	if(fp == NULL) {
		perror("Failed to open file\n");
		return NULL;
	}
	
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp); 
	rewind(fp);
	printf("opened file success\n");
	char* buffer = (char*)malloc(sizeof(char) * (file_size + 1));
	if(buffer == NULL) {
		perror("Failed to allocate buffer\n");
		return NULL;
	}
	size_t result = fread(buffer, 1, file_size, fp);
	if(result != file_size) {
		perror("Failed to read entire file\n");
		return NULL;
	}
	buffer[file_size] = '\0';
	fclose(fp);
	return buffer;
}
