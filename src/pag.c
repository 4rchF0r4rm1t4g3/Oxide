#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "out.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void setPagingDir (void)
{
    for (int i = 0; i<1024; i++)
    {
        page_directory[i] = 0x00000002;
    }

    for (int i = 0;i<1024;i++)
    {
        first_page_table[i] = (i*0x1000) | 3;
    }

    page_directory[0] = ((uint32_t)first_page_table) | 3;
}

extern void loadPageDir (uint32_t* pageDir);
extern void enablePaging (void);

void init_paging (void)
{
    setPagingDir();
    loadPageDir(page_directory);
    enablePaging();

    outlf("Paging enabled");
}
