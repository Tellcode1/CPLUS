
**Documentation under construction**

This project aims to supply its users with high level abstractions, such as OOP, string, namespaces and arrays.  
The library is easy to port for embedded systems as all you need to do is provide definitions for malloc and free in [malloc.h](https://github.com/wwidlishy/CPLUS/blob/main/cplus/externals/malloc.h)


---
# Table of contents

1. Object Oriented Programming  
	‎ 1. [Defining objects](#defining-objects)  
	‎ 2. Adding fields  
	‎ 3. Adding functions  
	‎ 4. Inheritance  
	‎ 5. Creating instances  
2. Namespaces  
	‎ 1. Creating namespace base  
	‎ 2. Adding fields  
	‎ 3. Adding functions  
	‎ 4. Adding instances of objects  
	‎ 5. **Namespace initializer, `namespace_create`**  
	‎ 6. Using the namespace  
3. Strings  
	‎ 1. Initializing a string  
	‎ 2. Accessing string value  
	‎ 3. `string.len()`  
	‎ 4. `string.set()`  
	‎ 5. `string.count_char()`  
4. Arrays  
	‎ 1. Initializing an array  
	‎ 2. Iterating trough an array  
	‎ 3. Getting the value at an index  
	‎ 4. `array.set()`  
	‎ 5. `array.append()`  
	‎ 6. `array.find()`  
	‎ 7. `array.insert()`  
	‎ 8. `array.insert_elements()`  
	‎ 9. `array.subarr()`  
	‎ 10. `array.remove()`  

---
# Object Oriented Programming

## Defining objects

This is how you define an object:

```c
// replace 'Name' with your objects name

object Name {
	// Initialize itself
	self(Name);
} Name;

// This function is called on each instance initialized of 'Name'
objectsetup(Name)(Name *result) {
	// Set self to its correct value
	setupself(result);
}
```

Understanding `objectsetup`:

```c
// This function is called on each instance initialized of [Object Name]
// In this function all the 'magic' behind OOP happens

objectsetup([Object Name])([Object Name] *result, [Additional Arguments if needed]) {
	// Set self to its correct value
	setupself(result);
}
```
## Adding fields

**Note: you can only assign default values in `objectsetup`**
You add a field how you would a variable:

```c
// replace 'Name' with your objects name

object Name {
	// Initialize itself
	self(Name);

	// Create a field
	int field;
} Name;

// This function is called on each instance initialized of 'Name'
objectsetup(Name)(Name *result) {
	// Set self to its correct value
	setupself(result);

	// You can define the default value of fields here
	result->field = 42;
}
```

## Adding functions

**Note: if you don't link your functions properly in `objectsetup` it might lead to unexpected behaviour**
To add a function you need to set up a pointer:

```c
// replace 'Name' with your objects name

object Name {
	// Initialize itself
	self(Name);

	// Create a field
	int field;

	// Setup a function pointer
	objectfn_pointer(Name, myFunction, void)(selftype Name *self);
} Name;

objectfn(Name, myFunction, void)(Name *self) {
	// Use '->' since self is a pointer
	self->field = 42;
}

// This function is called on each instance initialized of 'Name'
objectsetup(Name)(Name *result) {
	// Set self to its correct value
	setupself(result);

	// Link the function
	objectfn_setup(result, Name, myFunction);
}

```

Understanding `objectfn_pointer`:

```c
// objectfn_pointer usage:
// (use in the same object as 'Object Name')

objectfn_pointer([Object Name], [Function Name], [Return Type])(selftype [Object Name] *self, [More Arguments of the Function]);
```

- What is `selftype`?
- `selftype` is a requirement when referencing object as a type inside of the objects definition. For example:

```c
object SomeObject {
	self(SomeObject);	

	// Here selftype is needed as we are in SomeObjects definition
	objectfn_pointer(SomeObject, SomeFunction, void)(selftype SomeObject *self);
} SomeObject;

// Here selftype is not needed
objectfn(SomeObject, SomeFunction, void)(SomeObject *self) {
	// Do something
}
```

Understanding `objectfn`

```c
// A function definition

objectfn([Object Name], [Function Name], [Return Type])([Object Name] *self, [Additional Arguments if needed]) {
	How to access a field?
	Since self is a pointer you can use:
		self->[Field Name]

	How to call a function?
	Since self is a pointer you can use:
		self->[Function Name](self, [Function Arguments])
}

```

Understanding `objectfn_setup`

```c
// Inside of 'objectsetup' you need to link your function else risk unexpected behaviour

objectsetup([Object Name])([Object Name] *result) {
	setupself([Object Name]);
	// Link the function
	objectfn_setup(result, [Object Name], [Function Name]);
}

```
## Inheritance

**Note: inheritance is a pointer to an instance of inherited class, access it using the `inherited` field**

```c
// Create Base Object 'Fruit'

object Fruit {
	// Initialize 'self' field
    self(Fruit);

	// Initialize 'name' field
    char *name;

} Fruit;

// Setup 'Fruit'
objectsetup(Fruit))(Fruit *result) {
	setupself(Fruit);
}

// Create Object 'Banana' which inherits from 'Fruit'
object Banana {
	// Initialize 'self' field
    self(Banana);

	// Inherit from 'Fruit'
    inherit(Fruit);

} Banana;

// Setup 'Banana'
objectsetup(Banana))(Banana *result) {
	setupself(Banana);

	// Initialize object from which we are inheriting.
	inherit_setup(result, Fruit);
}

```
