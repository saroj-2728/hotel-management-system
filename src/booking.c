#include <stdio.h>
#include <string.h>
#include "booking.h"

void loadBookingData(BookingList* bookingList) {
    FILE* file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL) {
        bookingList->count = 0;
        return;
    }

    bookingList->count = 0;
    while (fscanf(file, "%d %s %ld %ld",
           &bookingList->bookings[bookingList->count].roomNumber,
           bookingList->bookings[bookingList->count].guestName,
           &bookingList->bookings[bookingList->count].checkinTime,
           &bookingList->bookings[bookingList->count].checkoutTime) != EOF &&
           bookingList->count < MAX_BOOKINGS) {
        bookingList->count++;
    }
    fclose(file);
}

int saveBookingData(const BookingList* bookingList) {
    FILE* file = fopen(BOOKINGS_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to open bookings file for writing!\n");
        return 0;
    }

    for (int i = 0; i < bookingList->count; i++) {
        fprintf(file, "%d %s %ld %ld\n",
                bookingList->bookings[i].roomNumber,
                bookingList->bookings[i].guestName,
                bookingList->bookings[i].checkinTime,
                bookingList->bookings[i].checkoutTime);
    }
    fclose(file);
    return 1;
}

int addBooking(BookingList* bookingList, int roomNumber, const char* guestName, time_t checkinTime, time_t checkoutTime) {
    if (bookingList->count >= MAX_BOOKINGS) {
        return 0;
    }

    bookingList->bookings[bookingList->count].roomNumber = roomNumber;
    strncpy(bookingList->bookings[bookingList->count].guestName, guestName, MAX_GUEST_NAME - 1);
    bookingList->bookings[bookingList->count].guestName[MAX_GUEST_NAME - 1] = '\0';
    bookingList->bookings[bookingList->count].checkinTime = checkinTime;
    bookingList->bookings[bookingList->count].checkoutTime = checkoutTime;
    bookingList->count++;
    return 1;
}

void updateBookingCheckout(BookingList* bookingList, int roomNumber, time_t checkoutTime) {
    for (int i = 0; i < bookingList->count; i++) {
        if (bookingList->bookings[i].roomNumber == roomNumber && 
            bookingList->bookings[i].checkoutTime == 0) {
            bookingList->bookings[i].checkoutTime = checkoutTime;
            break;
        }
    }
}

int findActiveBooking(const BookingList* bookingList, int roomNumber) {
    for (int i = 0; i < bookingList->count; i++) {
        if (bookingList->bookings[i].roomNumber == roomNumber && 
            bookingList->bookings[i].checkoutTime == 0) {
            return i;
        }
    }
    return -1;
}