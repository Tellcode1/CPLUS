# CPLUS
A simple C header making your life as a programmer easier.
### OOP
Example
```c
#include "cplus.h"

// Create new object named Cat
object(Cat) {
    // Initialize self variable
    self(Cat);

    // Age parameter
    int age;

    // Setup entry for a void function called meow
    objectfn_pointer(Cat, meow, void);
};

// Create the meow function with argument of self
objectfn(Cat, meow, void)(arg_self(Cat)) {
    printf("Meow, i'm %i\n", self.age);
}

// Create object setup function for Cat that initializes the object
objectsetup(Cat)(objectsetup_result(Cat)) {
    // Setup self field
    result->self = result;

    // Attach the meow function
    objectfn_setup(result, Cat, meow);
}

int main() {
    // Create and initialize the object instance
    obj(Cat) cat init(Cat)(&cat);

    // Use the object
    cat.age = 6;
    cat.meow(cat.self);
    
    return 0;
}
```

How to make your own object?

- Create the object
```c
object(MyObject) {
    self(MyObject);
    // here you can add fields like:
    // int data1;
};
```
- Create object initialiser
```c
// Result is what the initialized object will have
objectsetup(MyObject)(objectsetup_result(MyObject)) {
    result->self = result; // result->self is instance pointer
}
```
- Creating an object instance
```c
obj(MyObject) instance init(MyObject)(&instance);
```

- Adding a function to the object  
  Add a function pointer as a field in your object
     ```c
     object(MyObject) {
        self(MyObject);
        objectfn_pointer(MyObject, func1, void); // Add this
     }
     ```
