/* Line based array */

/*
 * ASCII is 7 bits, while `char` holds 8 bits.
 * So using char[] to hold unicode 8 characters is fine.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *lines[1024];
    int line_num;
} LBA;

static const LBA EMPTY_LBA = {
    .lines = 0,
    .line_num = 0,
};

// -------------------------------[ Initialization ]
const LBA* mkTextStorage(void) {
    return &EMPTY_LBA;
}

// -------------------------------[ Test suite ]
int main(int argc, char const *argv[])
{
    const LBA* t = mkTextStorage();
    printf("Line number is: %d\n", t->line_num);

    for (int i = 0; i < t->line_num; i++) {
        printf("[%d] -> %s\n", i, t->lines[i]);
    }
    return 0;
}
