#include <stdio.h>
#include "menu.h"
#include "auth.h"

int main() {
    loadUserData(); // Load user data at startup
    while(1) {
        displayLandingScreen();
        handleLandingChoice();
    }
    return 0;
}