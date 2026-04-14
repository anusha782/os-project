#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    while (1) {
        malloc(1024 * 1024); // allocate 1MB repeatedly
        printf("Allocating memory...\n");
        sleep(1);
    }
    return 0;
}
