#ifndef STAFF_H
#define STAFF_H

#include "auth.h"
#include "room.h"
#include "booking.h"

void displayStaffMenu();
int handleStaffChoice(UserList* userList, RoomList* roomList, BookingList* bookingList);
void checkInGuest(RoomList* roomList, BookingList* bookingList);
void checkOutGuest(RoomList* roomList, BookingList* bookingList);
void viewBookingHistory(const BookingList* bookingList);
void manageReservations(RoomList* roomList, BookingList* bookingList);

#endif