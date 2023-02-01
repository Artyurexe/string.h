#include <stdio.h>

int main() {
    char str[100];
    double p = 3.;
    sprintf(str, "%-+#14f", p);
    puts(str);
    return 1;
}
