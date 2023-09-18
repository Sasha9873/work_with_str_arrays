#include <stdio.h>
#include <assert.h>
#include <algorithm>

const static size_t DATA_SIZE = 10;


void my_qsort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));
void sort(int* data, int left, int right);
int partition(int* data, int left, int right);
void print_colourful_data(int* data, size_t size, size_t pivot_i, size_t left, size_t right);
/*while( left != right ) {
      if( cmp( *left, *pivot ) ) {
         ++left;
      } else {
         while( (left != --right) && cmp( *pivot, *right ) )
           ;
         std::iter_swap( left, right );
      }
    }
 
    --left;
    std::iter_swap( first, left );


int partition2(int* data, int first, int last)
{

    while( left != right ) {
      if( data[left] < pivot ) {
         ++left;
      } else {
         while( (left != --right) && pivot < data[right]  )
           ;
         std::iter_swap( left, right );
      }
    }
 
    --left;
    std::iter_swap( first, left );
}*/

int partition(int* data, int left, int right)
{
    printf("\n\nNew part:\n");
    size_t pivot_i = (left + right) / 2;
    int pivot = data[pivot_i];

    printf("%d pivot = %d\n", (left + right)/2, pivot);
    printf("left = %d pivot_i = %d right = %d\n", left, pivot_i, right);



    while(left < right)
    {
        //print_colourful_data(data, DATA_SIZE, pivot_i, left, right);
        printf("left = %d pivot_i = %d right = %d\n", left, pivot_i, right);

        while(data[left] < pivot && left < right)
        {
            assert(left < right);
            ++left;
        }

        while(data[right] > pivot && left < right)
        {
            assert(right >= 0);
            --right;
        }

        printf("left = %d pivot_i = %d right = %d\n", left, pivot_i, right);


        if(left < right)
        {
            printf("before swap:\n");
            print_colourful_data(data, DATA_SIZE, pivot_i, left, right);
            //printf("left = %d pivot_i = %d right = %d\n", left, pivot_i, right);
            std::swap(data[right], data[left]);
            //printf("left = %d pivot_i = %d right = %d %d\n", left, pivot_i, right, right == pivot_i);
            if(right == pivot_i)
            {
                pivot_i = left;
                --left;
            }
            else if(left == pivot_i)
            {
                pivot_i = right;
                ++right;
            }
            //printf("left = %d pivot_i = %d right = %d\n", left, pivot_i, right);
            ++left;
            --right;    
            printf("after swap:\n");
            print_colourful_data(data, DATA_SIZE, pivot_i, left, right);
        }
        

        

    }
    printf("left = %d\n", left);
    return left;
}

void sort(int* data, int left, int right)
{
    if(left >= right)
        return;

    if(left == right - 1)
    {
        if(data[left] > data[right])
        {
            std::swap(data[right], data[left]);
        }
        return;
    }

    int mid = partition(data, left, right);

    sort(data, left, mid - 1);
    sort(data, mid, right);


}

void my_qsort(void *base, size_t nmemb /*n_elements*/, size_t size /*sizeof element*/, int (*compare)(const void *, const void *))
{
    
}

void print_colourful_data(int* data, size_t size, size_t pivot_i, size_t left, size_t right)
{
    for(size_t i = 0; i < size; ++i)
        printf("%3ld ", i);
    printf("\n"); 

    printf("\033[0;34m");
    for(size_t i = 0; i < size; ++i)
    {

        if(i >= left + 1)
            printf("\033[0;32m");

        //if(i == pivot_i + 1)
          //  printf("\033[0;32m");

        if(i == right)
            printf("\033[0;33m");

        if(i > right)
            printf("\033[0;31m");

        if(i == left)
            printf("\033[0;36m");

        if(i == pivot_i)
            printf("\033[0;37m");

        if(i == pivot_i && (i == right || i == left))
            printf("\033[0;35m");

        printf("%3d ", data[i]);
    }

    printf("\x1b[0m");

    printf("\n\n"); 
}

void print_data(int* data, size_t size)
{
    for(size_t i = 0; i < size; ++i)
        printf("%3ld ", i);
    printf("\n"); 

    for(size_t i = 0; i < size; ++i)
        printf("%3d ", data[i]);
    printf("\n"); 
}

int main()
{
    int data[10] = {5, 2, 15, 3, 10, 16, 10, 5, 10, 4};

    //print_data(data, 10);

    sort(data, 0, 10 - 1);
    int mid = partition(data, 0, 10 - 1);
    printf("mid = %d\n", mid);
    //printf("\n");
    print_data(data, 10);

    //printf("\033[0;36m00ffmaaaaaaaaaaa");

    
    return 0;
}