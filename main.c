#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_data(const char* data[], size_t rows, size_t columns);
void print_int_data(const int* data[], size_t rows, size_t columns);
void print_triangle_array(const int* data, size_t rows);
int getter(int** data, size_t i, size_t j);

const size_t CUR_ROWS = 7;
const size_t CUR_COLUMNS = 4;


int getter(const int* data, size_t i, size_t j)
{
	return *(data + i + j + 2);
}

void print_data(const char** data, size_t rows, size_t columns)
{
	for(size_t i = 0; i < rows; ++i)
	{
		for(size_t j = 0; j < columns; ++j)
			printf("%c", *((char*)(data) + i*columns + j));
		printf("\n");
	}
}

void print_int_data(const int data[])
{
	size_t rows = data[0], columns = data[1];
	for(size_t i = 0; i < rows; ++i)
	{
		for(size_t j = 0; j < columns; ++j)
			//printf("%d ", *(int*)((char*)data + i*columns*sizeof(int) + j*sizeof(int)));
			//printf("%d ", *(      (int*)data  + i*columns/**sizeof(int)*/ + j/**sizeof(int)*/));
			printf("%d ", getter(data, i*columns, j));

		printf("\n");
	}
}

// void print_int_data(const int* data[], size_t rows, size_t columns)
// {
// 	for(size_t i = 0; i < rows; ++i)
// 	{
// 		for(size_t j = 0; j < columns; ++j)
// 			//printf("%d ", *(int*)((char*)data + i*columns*sizeof(int) + j*sizeof(int)));
// 			//printf("%d ", *(      (int*)data  + i*columns/**sizeof(int)*/ + j/**sizeof(int)*/));
// 			printf("%d ", getter(data, i*columns, j));

// 		printf("\n");
// 	}
// }

void print_triangle_array(const int* data, size_t rows)
{
	size_t k = 0;
	for(size_t i = 0; i < rows; ++i)
	{
		for(size_t j = 0; j < i + 1; ++j)
		{
			printf("%3d ", *(data + k));
			++k;
		}
		printf("\n");
	}
}

int main()
{
	char data[7][4] = {{'A', 'B', 'C', 'D'},
						"EFG",
						"abc"};

	printf("%c\n", *(*(data) + 1));

	printf("%c\n", *(*(data + 1) + 2));
	print_data((const char**)data, 7, 4);

	int int_data[]   = {2, 2,
						1, 2,
						3, 4};

	print_int_data((const int*)int_data);

	int triangle[] = { 0,
					   2,  3,
					  -2, -1, -5,
					   5,  2, -1, 0};

	print_triangle_array(triangle, 4);

	return 0;
}