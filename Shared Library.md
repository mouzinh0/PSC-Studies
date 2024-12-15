### What is a Shared Object (Shared Dynamic Library)?

A shared object (.so file on Linux) is a dynamic library. It’s similar to a .dll on Windows or a .dylib on macOS. Instead of bundling all code into a single large executable, you compile parts of the program into shared libraries that can be loaded at runtime.
Benefits include:

- Smaller executables (they share code at runtime).
- Easier updates (replace the shared library without rebuilding the entire program).
- Multiple programs can use the same shared library simultaneously.

### Why Create a Shared Library (libstore.so)?

In the previous points, you compiled all the .c files along with your test program directly into one executable. This worked fine for a small, self-contained project. However, as the project grows, it becomes beneficial to separate frequently reused code into a library.

- Before:
You had multiple source files (http_get_json.c, http_post_json.c, model.c, common.c) and a test file (test_model.c). You compiled them all together into a single executable. This meant every time you built the test program, you recompiled and relinked all the code.

- Now (with libstore.so):
You first compile and link all the common code (http_get_json.c, http_post_json.c, model.c, common.c) into a shared library (libstore.so). Then, the test program (test_model.c) only needs to link against libstore.so. The test program is now separate from the library.

### Benefits of Using a Shared Library

- Modularity & Reusability:

The functions for fetching products, users, and posting carts are now in a separate library (libstore.so). If you wanted to write another program that uses the same functions, you wouldn’t need to recompile all the source code again. You could just link against libstore.so.

- Faster Builds:

If you change only the test program (test_model.c), you don’t have to recompile all the .c files that form libstore.so. The library is already built, so you just re-link the test program against the existing libstore.so. This can save time in larger projects.

- Easier Maintenance & Updates:

If you fix a bug or add a feature to model.c (for example), you just update and rebuild libstore.so. Any programs linked against libstore.so automatically benefit from the updated code without needing to be fully recompiled.

- Distribution & Deployment:

In many real-world situations, you distribute libraries separately from executables. For example, system libraries like libcurl and libjansson are shared libraries. Your code now mimics a professional setup where you have a separate “API” (your libstore.so) and one or more clients (like test_model).

### What Are We Doing in the Makefile?


- Compiling with -fPIC and -shared:

-fPIC (Position Independent Code) is required for shared libraries, making the code relocatable at runtime. -shared tells the linker to produce a shared object (.so) instead of a normal executable. The Makefile first builds object files (.o) for each .c file, then links them into libstore.so.

- Linking the test program against -lstore:

In the test_model build command, we specify -L. to look in the current directory for libraries, and -lstore to link against libstore.so. Since we’ve built libstore.so, the linker knows to resolve all references from test_model.c against this library.

- LD_LIBRARY_PATH=. ./test_model:

This sets the environment variable LD_LIBRARY_PATH so the runtime loader knows where to find libstore.so. On most systems, by default, only standard system locations are searched for libraries. Setting LD_LIBRARY_PATH to . (the current directory) ensures that when test_model runs, it can find libstore.so.

### Example 

```
CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -lcurl -ljansson
INCLUDE = -I./include

# Source files
SOURCES = http_get_json.c http_post_json.c model.c common.c
OBJECTS = $(SOURCES:.c=.o)

# Shared library name
LIBNAME = libstore.so

all: $(LIBNAME) test_model

$(LIBNAME): $(OBJECTS)
	$(CC) -shared -o $(LIBNAME) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test_model: test_model.c
	$(CC) $(CFLAGS) $(INCLUDE) test_model.c -L. -lstore $(LDFLAGS) -o test_model

run: test_model
	LD_LIBRARY_PATH=. ./test_model

clean:
	rm -f $(OBJECTS) $(LIBNAME) test_model

# gcc -Wall -g -fPIC -I./include -L. -lstore -o test_model test_model.c -lcurl -ljansson

```



