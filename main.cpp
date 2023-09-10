#include "main.h"

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


//-------------------------------------------------------------------------
size_t get_file_size(FILE* file_ptr)
{
	fseek(file_ptr, 0, SEEK_END);

	size_t size = ftell(file_ptr);

	fseek(file_ptr, 0, SEEK_SET);

	return size;
}

FILE* open_file(const char* file_name, const char* mode, error_t* error)
{
	FILE* file_ptr = fopen(file_name, "r");

	if(!file_ptr)
	{
		if(error)
			*error = EOPENFILE;
		return NULL;
	}

	return file_ptr;
}

///returns buff
file_information* read_text_from_file_to_buff(const char* file_name, error_t* error)
{
	file_information* file_info = (file_information*)calloc(1, sizeof(file_information));
	
	file_info->file_name = file_name;

	
	FILE* file_ptr = open_file(file_name, "r", error);
	if(!file_ptr)
		return NULL;

	file_info->size = get_file_size(file_ptr);


	file_info->buffer = (char*)calloc(file_info->size + 2, sizeof(char)); 
	fread(file_info->buffer, sizeof(char), file_info->size, file_ptr);

	printf("%s\n", file_info->buffer);


	fclose(file_ptr);

	return file_info;
}

void parse_buffer(file_information* file_info, error_t* error)
{
	if(!file_info->size)
		return;

	file_info->text = (char**)calloc(MAX_N_STRS, sizeof(char*));

	char* const buffer = file_info->buffer;
	size_t n_strings = 0;

	printf("size = %d %c %d\n", file_info->size, file_info->buffer[0], file_info->buffer[0]);
	if(buffer[file_info->size - 1] != '\n')
	{
		buffer[file_info->size] = '\n';
		++file_info->size;
	}

	file_info->text[0] = buffer;

	for(size_t i = 0; i < file_info->size; ++i)
	{
		if(i == file_info->size - 1)
		{
			++n_strings;
			buffer[i] = '\0';
			break;
		}

		if(buffer[i] == '\n')
		{
			file_info->text[++n_strings] = &buffer[i + 1];
			buffer[i] = '\0';
		}
	}

	file_info->n_strings = n_strings;

	for(size_t i = 0; i < file_info->n_strings; ++i)
		printf("%s\n", file_info->text[i]);

	free(file_info->text);
	free(file_info->buffer);
}


int main()
{

	/*FILE* file = fopen("text.txt", "r");
	
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
	free(new_text);*/

	const char* file_name = "text.txt";

	error_t error = OK;
	file_information* file_info = read_text_from_file_to_buff(file_name, &error);
	if(error != OK)
		return error;

	printf("size = %d %c %d\n", file_info->size, file_info->buffer[0], file_info->buffer[0]);


	parse_buffer(file_info, &error);

	free(file_info);

	return 0;
}