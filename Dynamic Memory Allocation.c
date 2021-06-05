#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
void * my_malloc(size_t size)
{

    intptr_t x = _get_heap_handle(  ); //To get the handle of the current Heap

    void *malloc_ptr;
	malloc_ptr =  HeapAlloc(x, 0, size);  // To allocate memory in HeapMemory
	if(malloc_ptr == NULL)
    {
        printf("Failed to allocate the memory"); //Failed to grant the memory
        return NULL;
    }
	return malloc_ptr;   //If succesfull resturn pointer to the memory

}

void * my_calloc (size_t nmemb, size_t size)
{
    if(nmemb ==0)
    {
        printf("The number of blocks cannot be Zero"); //If the number of block = 0 return null because it is not possible
        return NULL;
    }
    else if(size == 0)
    {
        printf("The size of the blocl cnnot be 0");  //If the size = 0 return null because it is not possible
        return NULL;
    }
    else


    {
        size_t totalsize = nmemb*size;

        void *ptr_c = my_malloc(sizeof(totalsize));  //Calling my_maalloc
        if (ptr_c != NULL)
        {
            memset(ptr_c, 0, totalsize);  //Assigning 0 to the memory
        }
        else
        {
            return NULL;
        }
        return ptr_c;
    }

}



void * my_realloc(void *ptr, size_t size)
{
    void *ptr_r;
    intptr_t x_r = _get_heap_handle(  );  // to get the handle of the heap from the OS(Windows)
    ptr = HeapReAlloc(x_r,0,ptr,size);   //For reallocation of the memory

}

void my_free (void* ptr)
{
    _Bool p;
    void * x = _get_heap_handle(  );   //To free the allocated memory.
    p =  HeapFree( x,0,ptr); //HeapFree is OS function to free the Heap

}
size_t free_space_in_my_heap (void *ptr)
{
    //size_t free_space_in_my_heap (void *ptr)

    size_t s;
    intptr_t h_s = _get_heap_handle(  );
    s= HeapSize(h_s,0, ptr);
      return s;
}

int main()
{

	// This pointer will hold the
	// base address of the block created
	int* ptr;
	int n, i;

	// Get the number of elements for the array
	n = 5;
	printf("Enter number of elements: %d\n", n);

	// Dynamically allocate memory using calloc()
	ptr = (int*)my_calloc(n, sizeof(int));

	// Check if the memory has been successfully
	// allocated by malloc or not
	if (ptr == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {

		// Memory has been successfully allocated
		printf("Memory successfully allocated using my_calloc.\n");

		// Get the elements of the array
		for (i = 0; i < n; ++i) {
			ptr[i] = i + 1;
		}

		// Print the elements of the array
		printf("The elements of the array are: ");
		for (i = 0; i < n; ++i) {
			printf("%d, ", ptr[i]);
		}

		// Get the new size for the array
		n = 10;
		printf("\n\nEnter the new size of the array: %d\n", n);

		// Dynamically re-allocate memory using realloc()
		ptr = my_realloc(ptr, n * sizeof(int));

		// Memory has been successfully allocated
		printf("Memory successfully re-allocated using my_realloc.\n");

		// Get the new elements of the array
		for (i = 5; i < n; ++i) {
			ptr[i] = i + 1;
		}

		// Print the elements of the array
		printf("The elements of the array are: ");
		for (i = 0; i < n; ++i) {
			printf("%d, ", ptr[i]);
		}

		my_free(ptr);
	}

	return 0;
}
