#include "main.h"


int main(int argc, char const *argv[])
{
	char file_name[MAX_FILE_NAME] = "";

	if(argc < 2)  //no flags
	{
		strncpy(file_name, "text.txt", MAX_FILE_NAME - 1);
	}
	else
	{
		strncpy(file_name, argv[1], MAX_FILE_NAME - 1);
		printf("file = %s\n", file_name);
	}
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

	

	error_t error = OK;
	file_information* file_info = read_text_from_file_to_buff(file_name, &error);
	if(error != OK)
	{
		printf("error = %d\n", error);
		return error;
	}

	printf("size = %ld %c %d\n", file_info->size, file_info->buffer[0], file_info->buffer[0]);


	parse_buffer(file_info, &error);

	file_info = delete_file_info(file_info);

	return 0;
}