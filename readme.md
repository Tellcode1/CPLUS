# CPLUS
A simple C header making your life as a programmer easier.
### OOP
**I) Creating your first object**  
To create your first object you need to define atleast 2 things    
1) Create an empty object
```c
// Create an object
object Name {
    self(Name); // Initialize the self field.
} Name;
```
2) Create an object initializer function
```c
// Name is the same as from previous snippet and requires the previous code
objectsetup(Name)(Name* result) { // Add aditional arguments if needed.
    result->self = result; // Set value of self field.
}
```
3) Creating an instance
```c
// Create and initialize an object
Name instance init(Name)(&instance); // Last parentheses are arguments of objectsetup
```
4) Final code
```c
// Include the header
#include "path/to/cplus.h"

// Create an object
object Name {
    self(Name); // Initialize the self field.
} Name;

objectsetup(Name)(Name* result) { // Add aditional arguments if needed.
    result->self = result; // Set value of self field.
}

int main() {
    Name instance init(Name)(&instance); // Last parentheses are arguments of objectsetup
    return 0;
}
