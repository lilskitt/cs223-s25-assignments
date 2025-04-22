#include <stdio.h>

int main()
{
    FILE* fp = fopen("message", "r");
    char c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    return 0;
}
