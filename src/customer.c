#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "customer.h"

void displayCustomerMenu()
{
    system("cls");
    printf("\n==============================================\n");
    printf("|             CUSTOMER MENU                 |\n");
    printf("==============================================\n");
    printf("\n1. View Available Rooms");
    printf("\n2. Book Room");
    printf("\n3. Cancel Reservation"); // New
    printf("\n4. View My Bookings");   // New
    printf("\n5. Logout");
    printf("\n\nEnter your choice (1-5): ");
}

int handleCustomerChoice(UserList *userList, RoomList *roomList, BookingList *bookingList)
{
    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        system("cls");
        printf("\n==============================================\n");
        printf("|           AVAILABLE ROOMS                 |\n");
        printf("==============================================\n");
        viewAvailableRooms(roomList);
        printf("\nPress any key to continue...");
        getch();
        break;
    case 2:
        bookRoom(roomList, bookingList, userList);
        break;
    case 3:
        cancelReservation(roomList, bookingList, userList);
        break;
    case 4:
        viewMyBookings(bookingList, userList->users[userList->count - 1].username);
        break;
    case 5:
        printf("\nLogging out...\n");
        getch();
        break;
    default:
        printf("\nInvalid choice! Press any key to continue...");
        getch();
    }
    return choice;
}

void viewAvailableRooms(const RoomList *roomList)
{
    printf("\nAvailable Rooms:\n");
    printf("----------------------------------------\n");
    printf("Room No. | Type   | Price\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < roomList->count; i++)
    {
        if (!roomList->rooms[i].status)
        { // Only show available rooms
            printf("%-8d | ", roomList->rooms[i].roomNumber);
            switch (roomList->rooms[i].type)
            {
            case 1:
                printf("Single | ");
                break;
            case 2:
                printf("Double | ");
                break;
            case 3:
                printf("Suite  | ");
                break;
            }
            printf("%.2f\n", roomList->rooms[i].price);
        }
    }
}

void bookRoom(RoomList *roomList, BookingList *bookingList, UserList *userList)
{
    int roomNumber;
    system("cls");
    printf("\n==============================================\n");
    printf("|              BOOK ROOM                    |\n");
    printf("==============================================\n");

    viewAvailableRooms(roomList);

    printf("\nEnter Room Number to book: ");
    scanf("%d", &roomNumber);
    getchar();

    for (int i = 0; i < roomList->count; i++)
    {
        if (roomList->rooms[i].roomNumber == roomNumber)
        {
            if (roomList->rooms[i].status)
            {
                printf("\nRoom is already occupied!\n");
            }
            else
            {
                roomList->rooms[i].status = 1; // Mark as occupied
                addBooking(bookingList, roomNumber,
                           userList->users[userList->count - 1].username,
                           time(NULL), 0);
                printf("\nRoom booked successfully!\n");
                saveRoomData(roomList);
                saveBookingData(bookingList);
            }
            getch();
            return;
        }
    }

    printf("\nRoom not found!\n");
    getch();
}

void cancelReservation(RoomList *roomList, BookingList *bookingList, UserList *userList)
{
    int roomNumber;
    system("cls");
    printf("\n==============================================\n");
    printf("|          CANCEL RESERVATION               |\n");
    printf("==============================================\n");

    // Show current bookings for this customer
    viewMyBookings(bookingList, userList->users[userList->count - 1].username);

    printf("\nEnter Room Number to cancel: ");
    scanf("%d", &roomNumber);
    getchar();

    int bookingIndex = findActiveBooking(bookingList, roomNumber);
    if (bookingIndex != -1)
    {
        // Update room status
        for (int i = 0; i < roomList->count; i++)
        {
            if (roomList->rooms[i].roomNumber == roomNumber)
            {
                roomList->rooms[i].status = 0; // Mark as available
                break;
            }
        }

        // Update booking
        bookingList->bookings[bookingIndex].checkoutTime = time(NULL);

        printf("\nReservation cancelled successfully!\n");
        saveRoomData(roomList);
        saveBookingData(bookingList);
    }
    else
    {
        printf("\nNo active booking found for this room!\n");
    }
    getch();
}

void viewMyBookings(const BookingList *bookingList, const char *username)
{
    system("cls");
    printf("\n==============================================\n");
    printf("|            MY BOOKINGS                    |\n");
    printf("==============================================\n");

    printf("\nRoom | Check-in           | Status\n");
    printf("----------------------------------------\n");

    int found = 0;
    for (int i = 0; i < bookingList->count; i++)
    {
        if (strcmp(bookingList->bookings[i].guestName, username) == 0)
        {
            found = 1;
            char checkin[26];
            struct tm *timeinfo = localtime(&bookingList->bookings[i].checkinTime);
            strftime(checkin, 26, "%Y-%m-%d %H:%M:%S", timeinfo);

            printf("%-4d | %-18s | %s\n",
                   bookingList->bookings[i].roomNumber,
                   checkin,
                   bookingList->bookings[i].checkoutTime == 0 ? "Active" : "Completed");
        }
    }

    if (!found)
    {
        printf("\nNo bookings found.\n");
    }

    printf("\nPress any key to continue...");
    getch();
}