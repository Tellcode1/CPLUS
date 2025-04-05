# CPLUS
A simple C header making your life as a programmer easier.
## string.h
Requirements:  
- oop.h  
- <stdlib.h>  
- <string.h>
  
**I) Create a new string and initialize it**
```c
string text init(string)(&text, "Hello, world!");
```
**II) Change the value**
```c
string text init(string)(&text, "Hello, world!");
text.set(text.self, "laurum eum epsilon or whatever that fucking latin text was");
```
**III) Getting the value**
```c
string text init(string)(&text, "Hello, world!");
printf(text.value);
```
**IV) Getting the lenght**
```c
string text init(string)(&text, "Hello, world!");
printf("%i\n", text.len(text.self));
```

## OOP
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
```

**II) Adding fields and functions**  
```c
// Include the header
#include "path/to/cplus.h"

// Create an object
object Name {
    self(Name); // Initialize the self field.

    // Add a field
    int myField;

    // Add a function entry;
    objectfn_pointer(Name, myFunction, void); // Replace void with the function type
} Name;

// Define the function
objectfn(Name, myFunction, void)(Name self) { // Add more arguments if needed
    printf("%i\n", self.myField);
}
objectsetup(Name)(Name* result) { // Add aditional arguments if needed.
    result->self = result; // Set value of self field.

    // (Optional) define the default value
    result->myField = 4;

    // Link the function
    objectfn_setup(result, Name, myFunction);
}

int main() {
    Name instance init(Name)(&instance); // Last parentheses are arguments of objectsetup

    // Using the instance
    instance.myField += 2;
    instance.myFunction(instance.self);

    return 0;
}
```
