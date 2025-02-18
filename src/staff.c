#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "staff.h"

// Display the staff menu
void displayStaffMenu()
{
    system("cls");
    printf("\n==============================================\n");
    printf("|              STAFF MENU                   |\n");
    printf("==============================================\n");
    printf("\n1. View Room Status");
    printf("\n2. Check-in Guest");
    printf("\n3. Check-out Guest");
    printf("\n4. View Booking History");
    printf("\n5. Manage Reservations"); // New option
    printf("\n6. Logout");
    printf("\n\nEnter your choice (1-6): ");
}

// Handle the choice made by the staff
int handleStaffChoice(UserList *userList, RoomList *roomList, BookingList *bookingList)
{
    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        system("cls");
        printf("\n==============================================\n");
        printf("|              ROOM STATUS                  |\n");
        printf("==============================================\n");
        viewAllRooms(roomList);
        printf("\nPress any key to continue...");
        getch();
        break;
    case 2:
        checkInGuest(roomList, bookingList);
        break;
    case 3:
        checkOutGuest(roomList, bookingList);
        break;
    case 4:
        viewBookingHistory(bookingList);
        break;
    case 5:
        manageReservations(roomList, bookingList);
        break;
    case 6:
        printf("\nLogging out...\n");
        getch();
        break;
    default:
        printf("\nInvalid choice! Press any key to continue...");
        getch();
    }
    return choice;
}

// Check-in a guest
void checkInGuest(RoomList *roomList, BookingList *bookingList)
{
    int roomNumber;
    char guestName[50];
    system("cls");
    printf("\n==============================================\n");
    printf("|              CHECK-IN GUEST               |\n");
    printf("==============================================\n");

    viewAllRooms(roomList);

    printf("\nEnter Room Number: ");
    scanf("%d", &roomNumber);
    getchar();

    printf("Enter Guest Name: ");
    scanf("%[^\n]s", guestName);
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
                addBooking(bookingList, roomNumber, guestName, time(NULL), 0);
                printf("\nGuest checked in successfully!\n");
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

// Check-out a guest
void checkOutGuest(RoomList *roomList, BookingList *bookingList)
{
    int roomNumber;
    system("cls");
    printf("\n==============================================\n");
    printf("|             CHECK-OUT GUEST               |\n");
    printf("==============================================\n");

    viewAllRooms(roomList);

    printf("\nEnter Room Number: ");
    scanf("%d", &roomNumber);
    getchar();

    for (int i = 0; i < roomList->count; i++)
    {
        if (roomList->rooms[i].roomNumber == roomNumber)
        {
            if (!roomList->rooms[i].status)
            {
                printf("\nRoom is not occupied!\n");
            }
            else
            {
                roomList->rooms[i].status = 0; // Mark as available
                updateBookingCheckout(bookingList, roomNumber, time(NULL));
                printf("\nGuest checked out successfully!\n");
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

// View the booking history
void viewBookingHistory(const BookingList *bookingList)
{
    system("cls");
    printf("\n==============================================\n");
    printf("|            BOOKING HISTORY                |\n");
    printf("==============================================\n");

    printf("\nRoom | Guest Name        | Check-in           | Check-out\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < bookingList->count; i++)
    {
        char checkin[26], checkout[26] = "Still occupied";
        struct tm *timeinfo;

        timeinfo = localtime(&bookingList->bookings[i].checkinTime);
        strftime(checkin, 26, "%Y-%m-%d %H:%M:%S", timeinfo);

        if (bookingList->bookings[i].checkoutTime > 0)
        {
            timeinfo = localtime(&bookingList->bookings[i].checkoutTime);
            strftime(checkout, 26, "%Y-%m-%d %H:%M:%S", timeinfo);
        }

        printf("%-4d | %-15s | %-18s | %s\n",
               bookingList->bookings[i].roomNumber,
               bookingList->bookings[i].guestName,
               checkin,
               checkout);
    }

    printf("\nPress any key to continue...");
    getch();
}

// For managing the reservations
void manageReservations(RoomList *roomList, BookingList *bookingList)
{
    int choice;
    do
    {
        system("cls");
        printf("\n==============================================\n");
        printf("|         MANAGE RESERVATIONS               |\n");
        printf("==============================================\n");
        printf("1. View All Reservations\n");
        printf("2. Modify Reservation\n");
        printf("3. Cancel Reservation\n");
        printf("4. Back to Staff Menu\n");
        printf("\nEnter choice (1-4): ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            viewBookingHistory(bookingList);
            break;
        case 2:
        {
            viewBookingHistory(bookingList);
            int roomNumber;
            printf("\nEnter Room Number to modify: ");
            scanf("%d", &roomNumber);
            getchar();

            int bookingIndex = findActiveBooking(bookingList, roomNumber);
            if (bookingIndex != -1)
            {
                printf("\nCurrent guest: %s\n", bookingList->bookings[bookingIndex].guestName);
                printf("Enter new guest name: ");
                char newName[50];
                scanf("%[^\n]s", newName);
                getchar();
                strcpy(bookingList->bookings[bookingIndex].guestName, newName);
                saveBookingData(bookingList);
                printf("\nReservation modified successfully!\n");
            }
            else
            {
                printf("\nNo active booking found for this room!\n");
            }
            getch();
            break;
        }
        case 3:
        {
            viewBookingHistory(bookingList);
            int roomNumber;
            printf("\nEnter Room Number to cancel: ");
            scanf("%d", &roomNumber);
            getchar();

            int bookingIndex = findActiveBooking(bookingList, roomNumber);
            if (bookingIndex != -1)
            {
                bookingList->bookings[bookingIndex].checkoutTime = time(NULL);
                for (int i = 0; i < roomList->count; i++)
                {
                    if (roomList->rooms[i].roomNumber == roomNumber)
                    {
                        roomList->rooms[i].status = 0;
                        break;
                    }
                }
                saveBookingData(bookingList);
                saveRoomData(roomList);
                printf("\nReservation cancelled successfully!\n");
            }
            else
            {
                printf("\nNo active booking found for this room!\n");
            }
            getch();
            break;
        }
        case 4:
            return;
        default:
            printf("\nInvalid choice!\n");
            getch();
        }
    } while (1);
}