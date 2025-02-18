#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "auth.h"

int login(UserList* userList, int role)
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

    return validateCredentials(userList, username, password, role);
}

void loadUserData(UserList* userList)
{
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL)
    {
        // Create default admin if file doesn't exist
        userList->count = 0;
        registerUser(userList, "admin", "admin123", 1);
        registerUser(userList, "staff", "staff123", 2);
        registerUser(userList, "customer", "customer123", 3);
        saveUserData(userList);
        return;
    }

    userList->count = 0;
    while (fscanf(file, "%s %s %d %d",
                  userList->users[userList->count].username,
                  userList->users[userList->count].password,
                  &userList->users[userList->count].role,
                  &userList->users[userList->count].active) != EOF &&
           userList->count < MAX_USERS)
    {
        userList->count++;
    }
    fclose(file);
}

int saveUserData(const UserList* userList)
{
    FILE *file = fopen(USERS_FILE, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open users file for writing!\n");
        return 0;
    }

    for (int i = 0; i < userList->count; i++)
    {
        fprintf(file, "%s %s %d %d\n",
                userList->users[i].username,
                userList->users[i].password,
                userList->users[i].role,
                userList->users[i].active);
    }
    fclose(file);
    return 1;
}

int registerUser(UserList* userList, char* username, char* password, int role)
{
    if (userList->count >= MAX_USERS)
    {
        return 0;
    }

    // Check if username already exists
    for (int i = 0; i < userList->count; i++)
    {
        if (strcmp(userList->users[i].username, username) == 0)
        {
            return 0;
        }
    }

    strcpy(userList->users[userList->count].username, username);
    strcpy(userList->users[userList->count].password, password);
    userList->users[userList->count].role = role;
    userList->users[userList->count].active = 1;
    userList->count++;
    return 1;
}

int validateCredentials(const UserList* userList, char* username, char* password, int role)
{
    for (int i = 0; i < userList->count; i++)
    {
        if (strcmp(userList->users[i].username, username) == 0 &&
            strcmp(userList->users[i].password, password) == 0 &&
            userList->users[i].role == role &&
            userList->users[i].active == 1)
        {
            return 1;
        }
    }

    printf("\nInvalid credentials! Please try again.\n");
    getch();
    return 0;
}

void viewAllUsers(const UserList* userList)
{
    printf("\nUsername            | Role       | Status\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < userList->count; i++)
    {
        printf("%-18s | ", userList->users[i].username);
        
        switch(userList->users[i].role)
        {
            case 1: printf("Admin      | "); break;
            case 2: printf("Staff      | "); break;
            case 3: printf("Customer   | "); break;
            default: printf("Unknown    | ");
        }
        
        printf("%s\n", userList->users[i].active ? "Active" : "Inactive");
    }
}