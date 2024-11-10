#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Define the struct student */
struct student {
    const char *name;
    int number;
};

/* Prototype of the array_remove_cond function */
size_t array_remove_cond(void **array, size_t size,
                         int (*eval)(const void *, const void *), void *context);

/* Predicate function to remove students with number greater than the given threshold */
int remove_if_greater(const void *elem, const void *context) {
    const struct student *stud = (const struct student *)elem;
    int threshold = *(const int *)context;
    return stud->number > threshold;
}

int main(int argc, char *argv[]) {
    /* Check if the program received the required argument */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_threshold>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Convert the argument to an integer */
    int threshold = atoi(argv[1]);

    /* Static instances of struct student */
    static struct student student1 = {"Alice", 1001};
    static struct student student2 = {"Bob", 1002};
    static struct student student3 = {"Charlie", 999};
    static struct student student4 = {"Diana", 1003};

    /* Static array of pointers to struct student */
    struct student *students_array[] = {
        &student1,
        &student2,
        &student3,
        &student4
    };

    /* Size of the array */
    size_t size = sizeof(students_array) / sizeof(students_array[0]);

    /* Call array_remove_cond to remove students with number > threshold */
    size_t new_size = array_remove_cond(
        (void **)students_array,      /* array */
        size,                         /* size */
        remove_if_greater,            /* predicate function */
        &threshold                     /* context */
    );

    /* Print the remaining students */
    printf("Students with number <= %d:\n", threshold);
    for (size_t i = 0; i < new_size; ++i) {
        printf("Name: %s, Number: %d\n",
               students_array[i]->name,
               students_array[i]->number);
    }

    return EXIT_SUCCESS;
}

/*
 * Implementation of array_remove_cond
 * For the purpose of this test, we include a simple implementation.
 */
size_t array_remove_cond(void **array, size_t size,
                         int (*eval)(const void *, const void *), void *context) {
    void **current = array;
    void **last = array + size;

    while (current < last) {
        if (eval(*current, context)) {
            /* Remove element by shifting subsequent elements left */
            size_t nbytes = (last - current - 1) * sizeof(void *);
            if (nbytes > 0) {
                memmove(current, current + 1, nbytes);
            }
            --size;
            --last;
            /* Do not increment current; check the new element at this position */
        } else {
            ++current;
        }
    }
    return size;
}
