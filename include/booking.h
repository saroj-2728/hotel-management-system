#ifndef BOOKING_H
#define BOOKING_H

#include <time.h>

#define MAX_BOOKINGS 100
#define MAX_GUEST_NAME 50
#define BOOKINGS_FILE "data/bookings.txt"

typedef struct {
    int roomNumber;
    char guestName[MAX_GUEST_NAME];
    time_t checkinTime;
    time_t checkoutTime;
} Booking;

typedef struct {
    Booking bookings[MAX_BOOKINGS];
    int count;
} BookingList;

void loadBookingData(BookingList* bookingList);
int saveBookingData(const BookingList* bookingList);
int addBooking(BookingList* bookingList, int roomNumber, const char* guestName, time_t checkinTime, time_t checkoutTime);
void updateBookingCheckout(BookingList* bookingList, int roomNumber, time_t checkoutTime);
int findActiveBooking(const BookingList* bookingList, int roomNumber);

#endif