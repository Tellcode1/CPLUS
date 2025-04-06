# CPLUS
A simple C header making your life as a programmer easier.  

**How to use?**  
1. Copy all files from the project
2. include [cplus.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus.h)

## [oop.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/oop.h)  
Requirements:
  - Elecricity (optional)  

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
#include <stdio.h>

// Create an object
object Name {
    self(Name); // Initialize the self field.

    // Add a field
    int myField;

    // Add a function entry;
    objectfn_pointer(Name, myFunction, void)(selftype Name *self); // Replace void with the function type
} Name;

// Define the function
objectfn(Name, myFunction, void)(Name *self) { // Add more arguments if needed
    printf("%i\n", self->myField);
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

**III) Inheritance**
```c
#include "../inc/cplus.h"
#include <stdio.h>

// Create animal object
// No explanation needed here cuz we already know how to do that

object Animal {
    self(Animal);
    int age;
    objectfn_pointer(Animal, info, void)(selftype Animal *self);
} Animal;
        objectfn(Animal, info, void)(Animal *self) {
            printf("Im an Animal of age %i\n", self->age);
        }
        objectsetup(Animal)(Animal *result) {
            result->self = result;
            result->age = 0;
            objectfn_setup(result, Animal, info);
        }

// Create object dog
object Dog {
    self(Dog);
    inherit(Animal); // It inherits from animal
    objectfn_pointer(Dog, bark, void)(selftype Dog *self);
} Dog;
        objectfn(Dog, bark, void)(Dog *self) {
            // Example of accessing inherited fields
            printf("Woof, im %i\n", self->inherited->age);
        }

        // Overwrite info function
        // Just create a function for Dog with any name that isnt conflicting with already defined fields
        objectfn(Dog, inherited_info, void)(Animal *self) {
            printf("Im a Dog of age %i\n", self->age);
        }

        objectsetup(Dog)(Dog *result) {
            // Setup object
            result->self = result;
            objectfn_setup(result, Dog, bark);

            // Setup inheritance
            // result->inherited is a pointer
            inherit_setup(result->inherited, Animal)(result->inherited);

            // Overwrite info function
            result->inherited->info = objectfn_name(Dog, inherited_info);
        }

int main() {
    Animal animal init(Animal)(&animal);
    animal.age = 4;
    animal.info(animal.self);

    Dog dog init(Dog)(&dog);
    // Accessing inherited fields
    dog.inherited->age = 2;

    dog.bark(dog.self);

    // Accessing Inherited functions
    dog.inherited->info(dog.inherited->self);
    return 0;
}
```
## [namespace.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/namespace.h)
Requirements:
- [oop.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/oop.h)
  
**Note: Objects in namespaces require additional setup**  
```c
#include "../inc/cplus.h"
#include <stdio.h>

// Create the object
object Object {
    self(Object); // Initialise 'self' field
    int field; // Initialise 'field' field
    objectfn_pointer(Object, changeField, void); // Add function pointer
} Object;

// Define the function
objectfn(Object, changeField, void)(Object self, int newField) {
    self.field = newField;
}

// Define what values has initialised object
objectsetup(Object)(Object *result, int field) {
    result->self = result; // Add this or 'self' won't work
    result->field = field; // Initialise 'field' value
    objectfn_setup(result, Object, changeField); // Link function
}

// Create a namespace
namespace NAMESPACE {
    Object obj; // Object as a field
} NAMESPACE;

// Create the namespace for use
namespace_create(NAMESPACE, ns) {
    .obj = 0 // Placeholder value of 0
};

int main() {
    // Initialise the object instance inside of namespace ns
    init(Object)(&ns.obj, 4);

    // Operations using the object instance
    printf("%i\n", ns.obj.field);
    
    ns.obj.changeField(ns.obj.self, 5);
    printf("%i\n", ns.obj.field);
    
    ns.obj.field--;
    printf("%i\n", ns.obj.field);
    
    return 0;
}
```

**I) Creating a namespace, adding fields and functions**
```c
#include "../inc/cplus.h"
#include <stdio.h>

// Create the math namespace
namespace math_namespace {
    float pi; // Add field 'pi'
    namespacefn_pointer(add, int); // Add function 'add'
} math_namespace;

// Define the function add
namespacefn(math_namespace, add, int)(int a, int b) {
    return a + b;
}

// Define the math namespace for use
namespace_create(math_namespace, math) {
    .pi = 3.14, // Setup value for 'pi'
    .add = namespacefn_name(math_namespace, add) // Link 'add' function
};

int main() {
    printf("%i\n", math.add(2, 3)); // Use the namespace
    return 0;
}
```
## [string.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/string.h)
Requirements:  
- [oop.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/oop.h)
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
