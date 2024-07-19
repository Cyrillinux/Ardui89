#include <stdio.h>
int main(int argc, char *argv[]) {
    /* Debug
    // See all args
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    };
    return -1;
     */
    printf("fake version : %s\n", _FAKE_VERSION_);
    printf("sdcc version : %s\n", _SDCC_VERSION_);
    return 0;
};

