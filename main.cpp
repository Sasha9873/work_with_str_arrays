#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const size_t N_LINES = 2;
const size_t MAX_STR_LEN = 100;


void read_from_file(FILE* file, char** text)
{
	char buffer[MAX_STR_LEN];

	char* dinamic_str = NULL;

	for(size_t i = 0; i < N_LINES; ++i)
	{
		//fread(buffer, sizeof(char), MAX_STR_LEN - 1, file);
		fgets(buffer, MAX_STR_LEN, file);
		//fscanf(file, "%s", buffer);
		text[i] = strdup(buffer);
	}

}

char** read_from_file(FILE* file)
{
	char** text = (char**)calloc(N_LINES, sizeof(char*));
	if(!text)
		return NULL;

	char buffer[MAX_STR_LEN];

	char* dinamic_str = NULL;

	for(size_t i = 0; i < N_LINES; ++i)
	{
		//fread(buffer, sizeof(char), MAX_STR_LEN - 1, file);
		fgets(buffer, MAX_STR_LEN, file);
		//fscanf(file, "%s", buffer);
		text[i] = strdup(buffer);
	}

	return text;
}

void delete_text(char** text)
{
	if(!text)
		return;

	for(size_t i = 0; i < N_LINES; ++i)
	{
		if(text[i])
		{
			free(text[i]);
			text[i] = NULL;
		}
	}

	if(text)
	{
		//free(text);
		text = NULL;
	}
}


void print_strs(char** text)
{
	for(size_t i = 0; i < N_LINES; ++i)
		printf("%p %s", text[i], text[i]);
}

int main()
{

	FILE* file = fopen("text.txt", "r");
	
	char* text[N_LINES] = {};
	read_from_file(file, text);

	print_strs(text);

	fseek(file, 0, SEEK_SET);

	char** new_text = read_from_file(file);
	print_strs(new_text);

	fclose(file);
	printf("%p %p\n", text, new_text);
	delete_text(text);
	delete_text(new_text);
	free(new_text);

	return 0;
}