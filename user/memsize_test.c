#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    printf("initial memsize: %d\n", memsize());
    uint size = 20000;
    char* allocated_memory = (char*)malloc(size);
    printf("memsize after malloc: %d\n", memsize());
    
    free(allocated_memory);
    printf("memsize after free: %d\n", memsize());
    exit(0, "");
}