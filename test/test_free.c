#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    char *addr;

    i = 0;
    while (i < 1024) {
        addr = (char *)malloc(1024);
        if (addr == NULL) {
            write(1, "ERROR: malloc failed\n", 21);
            return (1);
        }
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
}
