#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "out.h"

typedef struct block_header {
    size_t size;
    struct block_header* next;
    int free;
} block_header_t;

block_header_t* heap_start;

block_header_t* current;

void* kernmalloc(size_t requestedSize)
{

    current = heap_start;
    while (current)
    {
        if ((current->next == NULL) && (current->size == 0))
        {
            outlf("no more memory");
            return NULL; // No more memory
        }

        if(current->free)
        {
            if(current->size >= requestedSize)
            {
                current->free = 0; // Mark as used
                return (void*)((uint8_t*)current + 1);
            }
        }

        current = current->next;
    }

    return NULL; // No suitable block found
}