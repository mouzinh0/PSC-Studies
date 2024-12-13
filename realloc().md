The C stdlib library realloc() function is used to reallocate the size of dynamically allocated memory. It allows us to allocates or reserves a new memory block after deallocating the previously allocated memory.

The function realloc() is used for optimizing the memory uses. If we find that allocated memory is too large or too small. We can use the realloc() to adjust the size of the allocated memory.

> Note : This function will only work when the memory has been dynamically allocated before using realloc() function.

> Syntax : void *realloc(void *ptr, size_t size)

### Parameters :
  
  - **ptr** − It represents a pointer to a memory block to be reallocated. That is previously allocated by the 'malloc()', 'calloc()', and 'realloc()'.
  - **size** − It represents the new size for the memory block, in bytes. If the size is zero, pointer is not null. A new minimum sized object is allocated, original object will freed.

Return Value :

This function returns a pointer to the newly allocated memory. Otherwise 'NULL' if the function fails to allocate the requested block of memory.


### Example :

```
#include <stdio.h>
#include <stdlib.h>

int main() {
   // Initially allocate memory for 2 integers
   int *ptr = malloc(2 * sizeof(int));
   if (ptr == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
   }

   ptr[0] = 5;
   ptr[1] = 10;

   // increase the size of the integer
   int *ptr_new = realloc(ptr, 3 * sizeof(int));
   if (ptr_new == NULL) {
      fprintf(stderr, "Memory reallocation failed\n");
      free(ptr);
      return 1;
   }

   ptr_new[2] = 15;
   
   int i;
   // Display the array
   for (i = 0; i < 3; i++) {
      printf("%d ", ptr_new[i]);
   }

   free(ptr_new);
   return 0;
}
```
Output : 5 10 15
