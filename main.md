# C-Fun

A c-fun program consists of zero or more global statements and exactly one global function named main.

A global statement is either a function, a class, an enum or a data type.

## General

Variables are declared either with the keywords `const` or `let`, functions can additionally be declared with `pure`.

`let` allows for any sort of modification.

`const` declares a variable as not changeable. You are not allowed to either reassign it nor (in case the variable is an object) call non-pure member functions on that object (as they could change the object).

`pure` is only valid as a function declaration. A pure function is only allowed to access other variables declared as const (for primitives and objects) and other functions declared as pure.

`const` and `pure` variables are reordered by the compiler to match their dependencies:

```
const a : int = 3;
const c : int = a + b;
const b : int = 2;
```
is valid c-fun. The compiler will move the third statement before the second.

This is mainly intended for functions. Imagine this example:
```
const foo : int => int = bar => foo2(bar) + 1;
pure foo2 : int => int = bar2 => bar2 * 2;
```
You don't have to order them by yourself, the compiler does this for you.

## Types

### Primitives

Currently all C++ primitives are supported. A seperated listing of them will follow soon.

### Arrays and Maps

Arrays and Maps are initialized with standard JSON notation. Note, that constant arrays or Maps won't allow the use of impure functions on them!

```
const array : int[] = [1, 2, 4, 5, 6, 7];
const dict : map = {
    key: "value",
    key2: "value2"
};
```

### Functions

```
const foo : int => int = bar => {
    return bar + 1;
};
```

A function is nothing more than a constant variable assignment, this means there is not a seperate `function` keyword. Every constant has to have a type signature.

Example in detail:

`const foo`: declare a constant variable with the identifier "foo".

`: int => int`: type signature of the variable. The fat arrow indicates a function. Read it as "a function that *maps* an integer to an integer".

`= bar => { ... };`: initializes the variable with an anonymous function that accespts an integer (remember the type signature) that can be accessed in the function as `bar`. The braces are optional in this case as the function is only one statement long.

`return bar + 1;`: define that the function returns the input parameter increased by one.

Functions can only one argument. This means you will have to use closures for imitating multiple arguments. This does not result in a spam of parentesis, because you can call a function with any amount of arguments:

```
const bar : int => int => int = a => b => a + b;

const addTwo : int => int = bar(2);
const sum : int = bar(2, 4);
```

### Custom Types

#### Union Types

You can declare a union type with the or pipe: `type a = int | long;`.

#### Enums

Enums can be used to create a completely custom type
```
enum a {
    Option1,
    Option2,
    Option3;
}
```
An option in an enum type can have a value assigned, that allows a variable of the enum to be typecasted to the value. If you use values, you have to provide them to every option and they have to be of the same type:

valid:
```
enum b {
    Option1 = 0,
    Option2 = 1,
    Option3 = 2;
}
```
invalid:
```
enum c {
    Option1 = 0,
    Option2 = "1", //types have to match
    Option3; //you have to provide all values
}
```

it is possible to automate said assignment of values when you declare an `assign` function (note that it has to be pure):
```
enum d {
    Option1, Option2, Option3;

    assign = assign;
}

pure assign : int => int = n => 2 ** n;
```
In this example every option will get a power of two assigned (this is useful for flags). You can also define helpful member functions but unlike classes, they have to be pure (more on member functions in the section "classes").


## Classes

```
class ClassName {
    const foo : int;
    let bar : int;
    const baz : int = 3;
    
    constructor = initClassName;

    member foo = fooPlusBar;
    member fooPlusBar : () => int;
}

const initClassName : int => int => map = foo => bar => ({ foo: foo, bar: bar });
const fooPlusBar : ClassName => int = instance => instance.foo + instance.bar;
```

The class declaration itself is fairly minimal, just so you can see what's inside.

As you can see there is a special constructor keyword. You simply assign a variable of type function to it to define a constructor. A constructor has to return a dictionary with inital values for *all* member variables that are not staticly assigned.

The member keyword is used to add functions to a class. As seen in the example the member syntax automaticly applies the instance of the class to the function. With the equals sign you are able to alias a function name.

For both, the member and the constructor keyword, type signatures are optional as they are already provided by the functions assigned to them. You can add them for readability.
