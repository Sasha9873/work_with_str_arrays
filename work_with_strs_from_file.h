#ifndef WORK_WITH_STR_FROM_FILE_H
#define WORK_WITH_STR_FROM_FILE_H


#include "main.h"

void read_from_file(FILE* file, char** text);
char** read_from_file(FILE* file);
void delete_text(char** text);
void print_strs(char** text);

file_information* read_text_from_file_to_buff(const char* file_name, error_t* error);
size_t get_file_size(FILE* file_ptr);
FILE* open_file(const char* file_name, const char* mode, error_t* error);
void parse_buffer(file_information* file_info, error_t* error);


size_t get_n_strings(char* buffer, size_t buff_size);
file_information* delete_file_info(file_information* file_info);

#endif