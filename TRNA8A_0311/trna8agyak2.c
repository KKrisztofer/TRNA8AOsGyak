#include <stdio.h>
#include <stdlib.h>

int main()
{
    char command[101];
    printf("Adj meg egy parancsot: ");
    scanf("%s", command);
    system(command);
    return 0;
}
