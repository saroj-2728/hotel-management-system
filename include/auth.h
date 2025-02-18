#ifndef AUTH_H
#define AUTH_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_USERS 100
#define USERS_FILE "data/users.txt"

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int role;  // 1: Admin, 2: Staff, 3: Customer
    int active; // 0: Inactive, 1: Active
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
} UserList;

void loadUserData(UserList* userList);
int saveUserData(const UserList* userList);
int registerUser(UserList* userList, char* username, char* password, int role);
int validateCredentials(const UserList* userList, char* username, char* password, int role);
int login(UserList* userList, int role);
void viewAllUsers(const UserList* userList);

#endif