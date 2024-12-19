
# Example usage
```c
#include <stdio.h>
#include "dyarr.h"

typedef struct {
    int x;
    int y;
} Point;


int main() {
    
    //  DA_Create(T): Initializes an array of type T with a capacity of 2 elements
    int* i_arr = DA_Create(int);	// Integer array
    float* f_arr = DA_Create(float);	// Float array
    Point* point_arr = DA_Create(Point);    // Struct Point array
    
    int num = 99;
    Point p = {7, 11};
    
    // DA_Add(array, value): Add (push) elements to the end of the array
    DA_Add(i_arr, 12);	// Can take constants/r-values 
    DA_Add(i_arr, num);	// Can take variables
    DA_Add(f_arr, 12.4f);	/* NOT putting 'f' at a constant floating-point number 
    						 * will make it double type instead of float! */
    DA_Add(point_arr, p);	// Add struct Point p
    
    // DA_Remove(array, i): Removes the element at index i
    DA_Remove(i_arr, 0);
    
    // DA_Insert(array, i, value): Inserts an element at index i
    DA_Insert(f_arr, 0, 23.23f);

    // Accessing an element just like normal arrays
    f_arr[1] = 10.10;

    // Finding the index of the element
    // notice that `index` is not defined, its defined later within the macro DA_Find()
    printf("Index of 99: ");
    DA_Find(i_arr, 99, index);
    printf("%d\n", index);

    int num2 = 23;
    DA_Insert(i_arr, 0, num2);
    
    // DA_Print(array, format, s, e): Prints elements from s to e in the array
    printf("Integers: ");
    DA_Print(i_arr, "%d, ", 0, DA_Size(i_arr));	// Prints the whole array
    printf("\n");
    
    printf("Floats: ");
    DA_Print(f_arr, "%.2f, ", 0, DA_Size(f_arr));
    printf("\n");

    printf("Struct: ");
    printf("(%d, %d)\n", point_arr[0].x, point_arr[0].y);    // Printing an element normally
    
        
    // Test adding many integers
    for (int i = 0; i < 10; i++) {
        DA_Add(i_arr, i);
    }

    DA_Print(i_arr, "%d, ", 0, DA_Size(i_arr));

    printf("\nIndex of 8: ");
    DA_Find(i_arr, 8, index_x);
    printf("%d\n", index_x);
    
    // ALWAYS free dynamic arrays with DA_Free(arr)
    DA_Free(i_arr);
    DA_Free(f_arr);
    DA_Free(point_arr);
    return 0;
}
```
# Other functions
`DA_Find(array, value, output)`: Assigns the index of `value` in `array` to `output`.  
`DA_Pop(array, index, output)`: Removes (pops) the value at `index` and assigns the removed value to `output`.  
`DA_Fit_Shrink(array)`: Reduce `array` capacity such that its the same as the number of elements it stores.  
`DA_Clear(array)`: Clears `array`.  
`DA_Is_Empty(array)`: Returns `1` if `array` has the size of 0, returns `0` otherwise.  
`DA_Size(array)`: Retuns `size_t <elements>`.  
`DA_Cap(array)`: Returns `size_t <max_capacity>` where `max_capacity` is the threshold of when `array` doubles its size. Whenever `DA_Size(array) >= DA_Cap(array)`, `max_capacity` doubles.  
`DA_Data_Size(array)`: Returns `size_t <size_per_element_in_bytes`, same as `sizeof(array[i])`.
# Note
If you want to use my code for your personal projects, just put your .c files to `src` folder and/or your .h files to `include` folder. Then, edit `makefile` accordingly (e.g. linking an external library) and execute `make`, no need to edit `makefile` if you just want to use the code above. The executable files will be put inside `bin` folder, `cd` into `bin` then execute `program` by typing `./program`. Object files will also be put inside `obj` folder. 
