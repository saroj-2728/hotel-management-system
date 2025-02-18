#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "admin.h"
#include "auth.h"
#include "room.h"

// Display the admin menu
void displayAdminMenu()
{
    system("cls");
    printf("\n==============================================\n");
    printf("|            ADMINISTRATOR MENU             |\n");
    printf("==============================================\n");
    printf("\n1. Register New User");
    printf("\n2. Manage Rooms");
    printf("\n3. View All Users");
    printf("\n4. Manage User Status");
    printf("\n5. Logout");
    printf("\n\nEnter your choice (1-5): ");
}

// Handle the choice made by the admin
int handleAdminChoice(UserList *userList, RoomList *roomList)
{
    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        registerNewUser(userList);
        break;
    case 2:
        manageRooms(roomList);
        break;
    case 3:
        system("cls");
        printf("\n==============================================\n");
        printf("|              USER LIST                    |\n");
        printf("==============================================\n");
        viewAllUsers(userList);
        printf("\nPress any key to continue...");
        getch();
        break;
    case 4:
        manageUserStatus(userList); // Fixed: Added missing call
        break;
        case 5:
        printf("\nLogging out...\n");
        getch();
        break;
    default:
        printf("\nInvalid choice! Press any key to continue...");
        getch();
        break;
    }
    return choice;
}

// Register a new user
void registerNewUser(UserList *userList)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int role;

    system("cls");
    printf("\n==============================================\n");
    printf("|            REGISTER NEW USER              |\n");
    printf("==============================================\n");

    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    printf("\nSelect role:\n");
    printf("1. Administrator\n");
    printf("2. Hotel Staff\n");
    printf("3. Customer\n");
    printf("Enter role (1-3): ");
    scanf("%d", &role);
    getchar();

    if (role < 1 || role > 3)
    {
        printf("\nInvalid role! Registration cancelled.\n");
        getch();
        return;
    }

    if (registerUser(userList, username, password, role))
    {
        printf("\nUser registered successfully!\n");
        saveUserData(userList);
    }
    else
    {
        printf("\nRegistration failed! Username might already exist or maximum users reached.\n");
    }
    getch();
}

// Manage rooms on the hotel
void manageRooms(RoomList *roomList)
{
    int choice;
    do
    {
        system("cls");
        printf("\n==============================================\n");
        printf("|            MANAGE ROOMS                   |\n");
        printf("==============================================\n");
        printf("1. View All Rooms\n");
        printf("2. Add New Room\n");
        printf("3. Update Room Details\n");
        printf("4. Delete Room\n");
        printf("5. Back to Admin Menu\n");
        printf("\nEnter choice (1-5): ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            system("cls");
            viewAllRooms(roomList);
            printf("\nPress any key to continue...");
            getch();
            break;
        case 2:
        {
            viewAllRooms(roomList);
            int roomNum, type;
            float price;
            printf("\nEnter Room Number: ");
            scanf("%d", &roomNum);
            printf("Enter Room Type (1:Single, 2:Double, 3:Suite): ");
            scanf("%d", &type);
            printf("Enter Room Price: ");
            scanf("%f", &price);

            if (addRoom(roomList, roomNum, type, price))
            {
                printf("\nRoom added successfully!\n");
                saveRoomData(roomList);
            }
            else
            {
                printf("\nFailed to add room!\n");
            }
            printf("\nPress any key to continue...");
            getch();
            break;
        }
        case 3:
            updateRoomDetails(roomList);
            break;
        case 4:
        {
            int roomNum;
            viewAllRooms(roomList);
            printf("\nEnter Room Number to delete: ");
            scanf("%d", &roomNum);

            for (int i = 0; i < roomList->count; i++)
            {
                if (roomList->rooms[i].roomNumber == roomNum)
                {
                    // Check if room is occupied
                    if (roomList->rooms[i].status)
                    {
                        printf("\nCannot delete an occupied room!\n");
                        getch();
                        return;
                    }
                    
                    for (int j = i; j < roomList->count - 1; j++)
                    {
                        roomList->rooms[j] = roomList->rooms[j + 1];
                    }
                    roomList->count--;
                    saveRoomData(roomList);
                    printf("\nRoom deleted successfully!\n");
                    getch();
                    return;
                }
            }
            printf("\nRoom not found!\n");
            getch();
            break;
        }
        case 5:
            return;
        default:
            printf("\nInvalid choice!\n");
            printf("Press any key to continue...");
            getch();
        }
    } while (1);
}

// Manage the users' status
void manageUserStatus(UserList *userList)
{
    system("cls");
    printf("\n==============================================\n");
    printf("|           MANAGE USER STATUS              |\n");
    printf("==============================================\n");

    viewAllUsers(userList);

    char username[MAX_USERNAME];
    printf("\nEnter username to toggle status: ");
    scanf("%s", username);

    for (int i = 0; i < userList->count; i++)
    {
        if (strcmp(userList->users[i].username, username) == 0)
        {
            userList->users[i].active = !userList->users[i].active;
            printf("\nUser status updated successfully!\n");
            saveUserData(userList);
            getch();
            return;
        }
    }
    printf("\nUser not found!\n");
    getch();
}

// Update the details of rooms in the hotel
void updateRoomDetails(RoomList *roomList)
{
    int roomNum;
    viewAllRooms(roomList);
    printf("\nEnter Room Number to update: ");
    scanf("%d", &roomNum);

    for (int i = 0; i < roomList->count; i++)
    {
        if (roomList->rooms[i].roomNumber == roomNum)
        {
            printf("\nCurrent Room Details:");
            printf("\nType: %s", 
                roomList->rooms[i].type == 1 ? "Single" :
                roomList->rooms[i].type == 2 ? "Double" : "Suite");
            printf("\nPrice: %.2f", roomList->rooms[i].price);
            printf("\nStatus: %s", roomList->rooms[i].status ? "Occupied" : "Available");

            printf("\n\nEnter new details:");
            printf("\nEnter new price: ");
            scanf("%f", &roomList->rooms[i].price);
            printf("Enter new type (1:Single, 2:Double, 3:Suite): ");
            scanf("%d", &roomList->rooms[i].type);
            
            saveRoomData(roomList);
            printf("\nRoom details updated successfully!\n");
            getch();
            return;
        }
    }
    printf("\nRoom not found!\n");
    getch();
}