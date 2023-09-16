#include "work_with_strs_from_file.h"

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
	{
		*error = EOPENFILE;
		printf("aaaaaaaaaaa\n");
		return NULL;
	}

	file_info->size = get_file_size(file_ptr);


	file_info->buffer = (char*)calloc(file_info->size + 2, sizeof(char)); 
	fread(file_info->buffer, sizeof(char), file_info->size, file_ptr);

	printf("%s\n", file_info->buffer);


	fclose(file_ptr);

	return file_info;
}


size_t get_n_strings(char* buffer, size_t buff_size)
{
	size_t n_strings = 0;
	for(size_t i = 0; i < buff_size; ++i)
	{
		if(buffer[i] == '\n')
			++n_strings;
	}

	return n_strings;
}

void parse_buffer(file_information* file_info, error_t* error)
{
	if(!file_info->size)
		return;

	char* const buffer = file_info->buffer;

	if(buffer[file_info->size - 1] != '\n')   /// if the last string in the file does not end with '\n'
	{
		buffer[file_info->size] = '\n';
		++file_info->size;
	}


	size_t n_strings = get_n_strings(buffer, file_info->size);
	file_info->n_strings = n_strings;

	file_info->text = (char**)calloc(n_strings, sizeof(char*));

	printf("size = %ld %c %d\n", file_info->size, file_info->buffer[0], file_info->buffer[0]);
	

	file_info->text[0] = buffer;

	size_t cur_str = 0;
	for(size_t i = 0; i < file_info->size; ++i)
	{
		if(i == file_info->size - 1)
		{
			++cur_str;
			buffer[i] = '\0';
			break;
		}

		if(buffer[i] == '\n')
		{
			file_info->text[++cur_str] = &buffer[i + 1];
			buffer[i] = '\0';
		}
	}


	for(size_t i = 0; i < file_info->n_strings; ++i)
		printf("%s\n", file_info->text[i]);

	
}


file_information* delete_file_info(file_information* file_info)
{
	if(!file_info)
		return nullptr;

	if(file_info->text)
	{
		free(file_info->text);
		file_info->text = nullptr;
	}

	if(file_info->buffer)
	{
		free(file_info->buffer);
		file_info->buffer = nullptr;
	}
	

	free(file_info);
	file_info = nullptr;

	return nullptr;
}