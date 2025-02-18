#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "menu.h"
#include "auth.h"
#include "admin.h"
#include "staff.h"
#include "customer.h"
#include "guest.h"

// Display the landing screen to the user
void displayLandingScreen()
{
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

// Handle the choice made by the user on the landing screen
void handleLandingChoice(UserList *userList, RoomList *roomList, BookingList *bookingList)
{
    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("\nRedirecting to Administrator login...\n");
        if (login(userList, 1))
        {
            printf("\nLogin successful! Welcome Administrator!\n");
            getch();
            // Start the admin menu
            while (1)
            {
                displayAdminMenu();
                int adminChoice = handleAdminChoice(userList, roomList);
                // If the admin chooses 5, log out from the admin account
                if (adminChoice == 5)
                {
                    printf("\nLogging out from Administrator account...\n");
                    getch();
                    break;
                }
            }
        }
        break;
    case 2:
        printf("\nRedirecting to Hotel Staff login...\n");
        if (login(userList, 2))
        {
            printf("\nLogin successful! Welcome Staff member!\n");
            getch();
            while (1)
            // Start the staff menu
            {
                displayStaffMenu();
                int staffChoice = handleStaffChoice(userList, roomList, bookingList);
                // If the staff chooses 6, log out from the staff account
                if (staffChoice == 6)
                {
                    printf("\nLogging out from Staff account...\n");
                    getch();
                    break;
                }
            }
        }
        break;
    case 3:
        printf("\nRedirecting to Customer login...\n");
        if (login(userList, 3))
        {
            printf("\nLogin successful! Welcome Customer!\n");
            getch();
            // Start the customer menu
            while (1)
            {
                displayCustomerMenu();
                int customerChoice = handleCustomerChoice(userList, roomList, bookingList);
                // If the customer chooses 5, log out from the customer account
                if (customerChoice == 5)
                {
                    printf("\nLogging out from Customer account...\n");
                    getch();
                    break;
                }
            }
        }
        break;
    case 4:
        printf("\nEntering guest mode...\n");
        getch();
        // Start the guest menu
        while (1)
        {
            displayGuestMenu();
            int guestChoice = handleGuestChoice(roomList);
            // If the guest chooses 3, exit guest mode
            if (guestChoice == 3)
            {
                break;
            }
        }
        break;
    case 5:
        printf("\nThank you for using Hotel Management System!\n");
        exit(0);
    default:
        printf("\nInvalid choice! Please try again.\n");
        printf("Press Enter to continue...");
        getch();
    }
}