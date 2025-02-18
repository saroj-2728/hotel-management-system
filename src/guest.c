#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "guest.h"

// Display guest menu
void displayGuestMenu() {
    system("cls");
    printf("\n==============================================\n");
    printf("|               GUEST MENU                  |\n");
    printf("==============================================\n");
    printf("\n1. View Room Availability");
    printf("\n2. Search Rooms by Type/Rate");
    printf("\n3. Exit Guest Mode");
    printf("\n\nEnter your choice (1-3): ");
}

// Handle choice selected by guest
int handleGuestChoice(RoomList* roomList) {
    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            system("cls");
            printf("\n==============================================\n");
            printf("|           ROOM AVAILABILITY               |\n");
            printf("==============================================\n");
            viewAllRooms(roomList);
            printf("\nPress any key to continue...");
            getch();
            break;
        case 2:
            searchRooms(roomList);
            break;
        case 3:
            printf("\nExiting guest mode...\n");
            getch();
            break;
        default:
            printf("\nInvalid choice! Press any key to continue...");
            getch();
    }
    return choice;
}

// Search rooms by type or price range
void searchRooms(const RoomList* roomList) {
    int choice;
    system("cls");
    printf("\n==============================================\n");
    printf("|           SEARCH ROOMS                    |\n");
    printf("==============================================\n");
    printf("\n1. Search by Type");
    printf("\n2. Search by Price Range");
    printf("\n3. Back to Guest Menu");
    printf("\n\nEnter choice (1-3): ");
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1: {
            printf("\nSelect Room Type:");
            printf("\n1. Single");
            printf("\n2. Double");
            printf("\n3. Suite");
            printf("\nEnter choice (1-3): ");
            int type;
            scanf("%d", &type);
            getchar();

            printf("\nRooms of selected type:\n");
            printf("----------------------------------------\n");
            printf("Room No. | Status    | Price\n");
            printf("----------------------------------------\n");
            
            for(int i = 0; i < roomList->count; i++) {
                if(roomList->rooms[i].type == type) {
                    printf("%-8d | %-9s | %.2f\n",
                           roomList->rooms[i].roomNumber,
                           roomList->rooms[i].status ? "Occupied" : "Available",
                           roomList->rooms[i].price);
                }
            }
            break;
        }
        case 2: {
            float minPrice, maxPrice;
            printf("\nEnter minimum price: ");
            scanf("%f", &minPrice);
            printf("Enter maximum price: ");
            scanf("%f", &maxPrice);
            getchar();

            printf("\nRooms in price range %.2f - %.2f:\n", minPrice, maxPrice);
            printf("----------------------------------------\n");
            printf("Room No. | Type   | Status    | Price\n");
            printf("----------------------------------------\n");
            
            for(int i = 0; i < roomList->count; i++) {
                if(roomList->rooms[i].price >= minPrice && 
                   roomList->rooms[i].price <= maxPrice) {
                    printf("%-8d | ", roomList->rooms[i].roomNumber);
                    switch(roomList->rooms[i].type) {
                        case 1: printf("Single | "); break;
                        case 2: printf("Double | "); break;
                        case 3: printf("Suite  | "); break;
                    }
                    printf("%-9s | %.2f\n",
                           roomList->rooms[i].status ? "Occupied" : "Available",
                           roomList->rooms[i].price);
                }
            }
            break;
        }
        case 3:
            return;
        default:
            printf("\nInvalid choice!\n");
    }
    printf("\nPress any key to continue...");
    getch();
}