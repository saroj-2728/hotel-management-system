#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "admin.h"

void displayAdminMenu() {
    system("cls");
    printf("\n==============================================\n");
    printf("|            ADMINISTRATOR MENU             |\n");
    printf("==============================================\n");
    printf("\n1. Register New User");
    printf("\n2. Manage Rooms");
    printf("\n3. View All Users");
    printf("\n4. Logout");
    printf("\n\nEnter your choice (1-4): ");
}

void handleAdminChoice() {
    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            printf("\nRegister New User selected\n");
            printf("Press any key to continue...");
            getch();
            break;
        case 2:
            printf("\nManage Rooms selected\n");
            printf("Press any key to continue...");
            getch();
            break;
        case 3:
            printf("\nView All Users selected\n");
            printf("Press any key to continue...");
            getch();
            break;
        case 4:
            printf("\nLogging out...\n");
            return;
        default:
            printf("\nInvalid choice! Press any key to continue...");
            getch();
    }
}