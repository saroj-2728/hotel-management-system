#ifndef GUEST_H
#define GUEST_H

#include "room.h"

void displayGuestMenu();
int handleGuestChoice(RoomList* roomList);
void searchRooms(const RoomList* roomList);

#endif