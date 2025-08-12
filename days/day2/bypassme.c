#include <stdio.h>
#include <string.h>

int main() {
    char serial[50];
    printf("Enter serial: ");
    scanf("%49s", serial);

    if(strcmp(serial, "ABC123") == 0) {
        printf("Access Granted!\n");
    } else {
        printf("Invalid serial.\n");
    }
    return 0;
}
