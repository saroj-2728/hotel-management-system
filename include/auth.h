// The authentication header file
#ifndef AUTH_H
#define AUTH_H

// Constants
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_USERS 100
#define USERS_FILE "data/users.txt"

// Details of the user
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int role;  // 1: Admin, 2: Staff, 3: Customer
    int active; // 0: Inactive, 1: Active
} User;

// Global variables
extern User users[MAX_USERS];
extern int userCount;

// Function prototypes
int login(int role);
void loadUserData();
int validateCredentials(char* username, char* password, int role);
int saveUserData();
int registerUser(char* username, char* password, int role);

#endif