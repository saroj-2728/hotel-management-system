#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "menu.h"
#include "auth.h"
#include "admin.h"

// Display the landing screen
void displayLandingScreen()
{
    // Clear screen and display the menu
    system("cls");
    printf("\n==============================================\n");
    printf("|          HOTEL MANAGEMENT SYSTEM          |\n");
    printf("==============================================\n");
    printf("\n1. Administrator");
    printf("\n2. Hotel Staff");
    printf("\n3. Customer");
    printf("\n4. Guest");
    printf("\n5. Exit");
    printf("\n\nEnter your role (1-5): ");
}

// Handle the user's choice from the landing screen
void handleLandingChoice()
{
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear input buffer

    switch (choice)
    {
    case 1:
        printf("\nRedirecting to Administrator login...\n");
        if (login(1))
        {
            printf("\nLogin successful! Welcome Administrator!\n");
            getch();
            while (1)
            {
                displayAdminMenu();
                handleAdminChoice();
                if (choice == 4)
                    break; // Break if logout selected
            }
        }
        else
        {
            printf("\nLogin failed! Invalid credentials.\n");
            getch();
        }
        break;
    case 2:
        printf("\nRedirecting to Hotel Staff login...\n");
        if (login(2))
        {
            printf("\nLogin successful! Welcome Staff member!\n");
            getch();
        }
        else
        {
            printf("\nLogin failed! Invalid credentials.\n");
            getch();
        }
        break;
    case 3:
        printf("\nRedirecting to Customer login...\n");
        if (login(3))
        {
            printf("\nLogin successful! Welcome Customer!\n");
            getch();
        }
        else
        {
            printf("\nLogin failed! Invalid credentials.\n");
            getch();
        }
        break;
    case 4:
        printf("\nEntering guest mode...\n");
        break;
    case 5:
        printf("\nThank you for using Hotel Management System!\n");
        exit(0);
    default:
        printf("\nInvalid choice! Please try again.");
        printf("\nPress Enter to continue...");
        getch();
    }
}