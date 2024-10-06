When a function is declared as static in C, it means that the scope of the function is limited to the file where it is declared.
In other words, static functions have internal linkage, which means they are only visible within the file where they are defined.

## Advantages:

* **Encapsulation (File Scope):**

The static keyword ensures that these helper functions (append_char, append_string, etc.) are not exposed or accessible from other files.
This encapsulates the functionality within the file where they are implemented,
making the code modular and preventing external code from accidentally calling or depending on these functions.

* **Avoid Name Collisions:**

In a larger program, especially when there are multiple source files, you might have functions with the same name in different files.
Declaring a function as static prevents potential name collisions, as the function is only visible and callable within the file it is declared.
For example, if another file in the project has its own append_char function, there would be no conflict as the static
versions are confined to their respective files.

* **Optimization by the Compiler:**

Since the compiler knows that static functions will only be used in the same file,
it can sometimes perform optimizations like inlining the function to improve performance, as it doesn’t need to worry about external linkage.
