#ifndef MENU_H
#define MENU_H

#include "auth.h"
#include "room.h"
#include "booking.h"

void displayLandingScreen();
void handleLandingChoice(UserList* userList, RoomList* roomList, BookingList* bookingList);

#endif