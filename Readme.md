# Hotel Management System 
A C-based console application for managing hotel operations with multi-user support.

## Features

**Administrator**
- User Management (Add/Remove/Modify)
- Room Management
- View System Users

**Staff**
- Check-in/Check-out Guests
- View Booking History
- Manage Reservations

**Customer**
- Book/Cancel Rooms
- View Available Rooms
- Check Booking History

**Guest**
- View Room Availability
- Search Rooms

## Setup Instructions

### Requirements
- GCC Compiler (MinGW for Windows)
- Visual Studio Code

### Installation
```bash
# Clone repository
git clone https://github.com/saroj-2728/hotel-management-system.git
cd hotel-management-system

# Create data directory
mkdir data
```

### Running
1. Using Batch File:
```bash
run.bat
```
2. Using VS Code:
   - Press `Ctrl + Shift + B`
     
## Project Structure
```
hotel-management-system/
├── .vscode/
│   ├── tasks.json
│   └── settings.json
├── include/
│   ├── admin.h
│   ├── auth.h
│   ├── booking.h
│   ├── customer.h
│   ├── guest.h
|   ├── menu.h
│   ├── room.h
│   └── staff.h
├── src/
│   ├── admin.c
│   ├── auth.c
│   ├── booking.c
│   ├── customer.c
│   ├── guest.c
│   ├── main.c
│   ├── menu.c
│   ├── room.c
│   └── staff.c
├── data/
├── .gitignore
├── README.md
└── run.bat
```

## Default Credentials
```
Admin:     admin/admin123
Staff:     staff/staff123
Customer:  customer/customer123
```

## Data Files
- `users.txt`: User credentials
- `rooms.txt`: Room information
- `bookings.txt`: Booking records