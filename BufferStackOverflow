// Está pidiendo un overflow a gritos.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct credential {
    char name[32];
    char pass[32];
};

bool login(void) {
    char realpass[32];
    struct credential user;

    // Prompt for username
    printf("User: ");
    fgets(user.name, sizeof(user), stdin);

    // Simulate database fetch by directly setting realpass
    strncpy(realpass, "securepassword", sizeof(realpass) - 1);
    realpass[sizeof(realpass) - 1] = '\0';  // Ensure null termination

    // Prompt for password
    printf("Pass: ");
    fgets(user.pass, sizeof(user), stdin);

    // Compare user.pass with realpass
    return strncmp(user.pass, realpass, sizeof(realpass) - 1) == 0;
}

int main() {
    if (login()) {
        printf("Login successful!\n");
    } else {
        printf("Login failed.\n");
    }
    return 0;
}
