#include <stdio.h>
#include <string.h>
#include "auth.h"

// Get the users
User users[MAX_USERS];
int userCount = 0;

// Initiage the login process
int login(int role)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\n==============================================\n");
    printf("|                  LOGIN                    |\n");
    printf("==============================================\n");

    printf("\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    return validateCredentials(username, password, role);
}

// Load user data at the beginning of the program
void loadUserData()
{
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL)
    {
        // Create default admin if file doesn't exist
        registerUser("admin", "admin123", 1);
        registerUser("staff", "staff123", 2);
        registerUser("customer", "customer123", 3);
        saveUserData();
        return;
    }

    userCount = 0;
    while (fscanf(file, "%s %s %d %d",
                  users[userCount].username,
                  users[userCount].password,
                  &users[userCount].role,
                  &users[userCount].active) != EOF &&
           userCount < MAX_USERS)
    {
        userCount++;
    }
    fclose(file);
}

// Save user data at the end of the program
int saveUserData()
{
    FILE *file = fopen(USERS_FILE, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open users file for writing!\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s %d %d\n",
                users[i].username,
                users[i].password,
                users[i].role,
                users[i].active);
    }
    fclose(file);
    return 1;
}

// Register a new user
int registerUser(char *username, char *password, int role)
{
    if (userCount >= MAX_USERS)
    {
        return 0;
    }

    // Check if username already exists
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return 0;
        }
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].role = role;
    users[userCount].active = 1;
    userCount++;
    return 1;
}

// Validate user credentials on login
int validateCredentials(char *username, char *password, int role)
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0 &&
            users[i].role == role &&
            users[i].active == 1)
        {
            return 1;
        }
    }
    return 0;
}