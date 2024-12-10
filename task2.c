#include <stdio.h>
#include <stdlib.h>

/* Declare the operations */
int add(int a, int b) { printf("Adding 'a' and 'b'\n"); return a + b; }
int subtract(int a, int b) { printf("Subtracting 'b' from 'a'\n"); return a - b; }
int multiply(int a, int b) { printf("Multiplying 'a' and 'b'\n"); return a * b; }
int divide(int a, int b) { 
    if (b == 0) { 
        printf("Division by zero is not allowed.\n"); 
        return 0; 
    }
    printf("Dividing 'a' by 'b'\n"); 
    return a / b; 
}

int exit_program(int a, int b) { 
    printf("Exiting program.\n"); 
    exit(0); 
}

int main(void)
{
    int a = 6, b = 3;
    int option;

    // Function pointer array
    int (*operations[])(int, int) = {add, subtract, multiply, divide, exit_program};

    printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
    printf("Specify the operation to perform (0: add | 1: subtract | 2: multiply | 3: divide | 4: exit): ");
    scanf("%d", &option);

    // Call the appropriate function
    printf("x = %d\n", operations[option](a, b));
    return 0;
}
