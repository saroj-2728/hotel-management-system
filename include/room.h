#ifndef ROOM_H
#define ROOM_H

#define MAX_ROOMS 50
#define ROOMS_FILE "data/rooms.txt"

typedef struct {
    int roomNumber;
    int type;        // 1: Single, 2: Double, 3: Suite
    float price;
    int status;      // 0: Available, 1: Occupied
} Room;

typedef struct {
    Room rooms[MAX_ROOMS];
    int count;
} RoomList;

void loadRoomData(RoomList* roomList);
int saveRoomData(const RoomList* roomList);
int addRoom(RoomList* roomList, int roomNumber, int type, float price);
void viewAllRooms(const RoomList* roomList);
int deleteRoom(RoomList* roomList, int roomNumber);

#endif