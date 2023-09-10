#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const size_t N_LINES = 2;
const size_t MAX_STR_LEN = 100;
const size_t MAX_N_STRS = 100;


struct file_information{
	const char* file_name;
	size_t size;
	size_t n_strings;
	char* buffer;
	char** text; ///pointers to the beginning of the strs in the text

} typedef file_information;

enum error_t{
	OK 		  = 0,	
	ENOMEM    = -1,
	EOPENFILE = -2,
};

void read_from_file(FILE* file, char** text);
char** read_from_file(FILE* file);
void delete_text(char** text);
void print_strs(char** text);

file_information* read_text_from_file_to_buff(const char* file_name, error_t* error);
size_t get_file_size(FILE* file_ptr);
FILE* open_file(const char* file_name, const char* mode, error_t* error);
void parse_buffer(file_information* file_info, error_t* error);



