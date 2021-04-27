#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fajl, vissza;
    char szoveg[100];

    szoveg[0] = 0;

    fajl = open("trna8a.txt", O_RDWR);

    if (fajl == -1) {
        perror("Fajl megnyitas [open()] hiba! \n");
        exit(-1);
    }

    vissza = read(fajl, szoveg, 100);
    printf("A read() %d byteot olvasott.\n\n", vissza);
    strcpy(szoveg, "TRNA8A");


    vissza = lseek(fajl, 0, SEEK_SET);
    printf("Az lseek() beallt a %d. helyre, és ide ", vissza);

    vissza = write(fajl, szoveg, 6);
    printf("a write() %d byteot irt: %s\n\n", vissza, szoveg);
    strcpy(szoveg, "TRNA8A");

    close(fajl);

    return 0;
}

