#include <stdio.h>
#include "room.h"

void loadRoomData(RoomList* roomList) {
    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        // Create sample rooms if file doesn't exist
        roomList->count = 0;
        addRoom(roomList, 101, 1, 100.0);
        addRoom(roomList, 102, 2, 150.0);
        addRoom(roomList, 103, 3, 200.0);
        saveRoomData(roomList);
        return;
    }

    roomList->count = 0;
    while (fscanf(file, "%d %d %f %d", 
           &roomList->rooms[roomList->count].roomNumber,
           &roomList->rooms[roomList->count].type,
           &roomList->rooms[roomList->count].price,
           &roomList->rooms[roomList->count].status) != EOF && 
           roomList->count < MAX_ROOMS) {
        roomList->count++;
    }
    fclose(file);
}

int saveRoomData(const RoomList* roomList) {
    FILE *file = fopen(ROOMS_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to open rooms file for writing!\n");
        return 0;
    }

    for (int i = 0; i < roomList->count; i++) {
        fprintf(file, "%d %d %.2f %d\n", 
                roomList->rooms[i].roomNumber,
                roomList->rooms[i].type,
                roomList->rooms[i].price,
                roomList->rooms[i].status);
    }
    fclose(file);
    return 1;
}

int addRoom(RoomList* roomList, int roomNumber, int type, float price) {
    if (roomList->count >= MAX_ROOMS) return 0;

    // Check if room number already exists
    for (int i = 0; i < roomList->count; i++) {
        if (roomList->rooms[i].roomNumber == roomNumber) return 0;
    }

    roomList->rooms[roomList->count].roomNumber = roomNumber;
    roomList->rooms[roomList->count].type = type;
    roomList->rooms[roomList->count].price = price;
    roomList->rooms[roomList->count].status = 0;  // Available by default
    roomList->count++;
    return 1;
}

void viewAllRooms(const RoomList* roomList) {
    printf("\nRoom List:\n");
    printf("----------------------------------------\n");
    printf("Room No. | Type   | Price  | Status\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < roomList->count; i++) {
        printf("%-8d | ", roomList->rooms[i].roomNumber);
        switch(roomList->rooms[i].type) {
            case 1: printf("Single | "); break;
            case 2: printf("Double | "); break;
            case 3: printf("Suite  | "); break;
        }
        printf("%-6.2f | ", roomList->rooms[i].price);
        printf("%s\n", roomList->rooms[i].status ? "Occupied" : "Available");
    }
}