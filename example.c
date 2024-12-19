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
    for (int i = 0; i < 10000; i++) {
        DA_Add(i_arr, i);
    }

    DA_Print(i_arr, "%d, ", 0, DA_Size(i_arr));
    
    // ALWAYS free dynamic arrays with DA_Free(arr)
    DA_Free(i_arr);
    DA_Free(f_arr);
    DA_Free(point_arr);
    return 0;
}
