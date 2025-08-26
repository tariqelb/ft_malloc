#include <stdlib.h>
#include <unistd.h>

void print(char *s) {
    int i = 0;
    while (s[i]) i++;
    write(1, s, i);
}

int main() {
    char *addr;

    // malloc(0) should return NULL or a unique pointer (implementation-defined)
    addr = malloc(0);
    if (addr)
        free(addr); // If it returns something, it should be freeable

    // free(NULL) should do nothing
    free(NULL);

    // free of a non-malloced pointer - should not crash
    free((void *)0x12345);

    // realloc with NULL pointer should act like malloc
    addr = realloc(NULL, 100);
    if (addr == NULL) {
        print("ERROR: realloc(NULL, size) failed\n");
        return (1);
    }
    free(addr);

    // realloc with size 0 should act like free and return NULL (or unique ptr)
    addr = malloc(100);
    addr = realloc(addr, 0);
    if (addr)
        free(addr); // If it returns something, it should be freeable

    print("Bonjour\n");
    return (0);
}
