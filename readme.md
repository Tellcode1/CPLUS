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
