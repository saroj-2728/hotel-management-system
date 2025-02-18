#ifndef ADMIN_H
#define ADMIN_H

#include "auth.h"
#include "room.h"

void displayAdminMenu();
int handleAdminChoice(UserList* userList, RoomList* roomList);
void registerNewUser(UserList* userList);
void manageRooms(RoomList* roomList);
void manageUserStatus(UserList* userList);
void updateRoomDetails(RoomList* roomList);

#endif