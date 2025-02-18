#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "auth.h"
#include "room.h"
#include "booking.h"

void displayCustomerMenu();
int handleCustomerChoice(UserList* userList, RoomList* roomList, BookingList* bookingList);
void viewAvailableRooms(const RoomList* roomList);
void bookRoom(RoomList* roomList, BookingList* bookingList, UserList* userList);
void cancelReservation(RoomList* roomList, BookingList* bookingList, UserList* userList);
void viewMyBookings(const BookingList* bookingList, const char* username);

#endif