#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("kerekes.txt", "w");
    fprintf(fp, "Kerekes Krisztofer");
    fprintf(fp, "Mernokinformatika");
    fprintf(fp, "TRNA8A");

    fclose(fp);
    FILE *fpr;
    fpr = fopen("kerekes.txt", "r");
    char beolvas[100];
    fscanf(fpr, "%[^\n]s", beolvas);
    printf("%s",beolvas);

    fclose(fpr);
    return 0;
}
