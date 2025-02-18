#include <stdio.h>
#include <direct.h>  // for _mkdir
#include "menu.h"
#include "auth.h"
#include "room.h"
#include "booking.h"

int main() {
    // Create data directory if it doesn't exist
    _mkdir("data");

    UserList userList = {0};  // Initialize user list
    RoomList roomList = {0};  // Initialize room list
    BookingList bookingList = {0};  // Initialize booking list
    
    // Load initial data
    loadUserData(&userList);
    loadRoomData(&roomList);
    loadBookingData(&bookingList);
    
    // Main loop of the program
    while(1) {
        displayLandingScreen();
        handleLandingChoice(&userList, &roomList, &bookingList);
    }
    
    return 0;
}