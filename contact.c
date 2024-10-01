#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validation.h"
#include "search.h"

// Initialize and load contacts from the file
void initialize(AddressBook *addressBook) {
    loadContactsFromFile(addressBook);
}

// List all contacts in the address book
void listContacts(AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
        printf("\n");
    }
}

// Create a new contact
void createContact(AddressBook *addressBook) {
    printf("Enter the name: ");
    getchar();
    scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].name);
    getchar();

    // Phone number validation
    printf("Enter the Phone number: ");
    scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
    while (phone_validation(addressBook)) {
        printf("Enter a valid phone number: ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
    }

    // Email validation
    printf("Enter the mail id: ");
    scanf("%s", addressBook->contacts[addressBook->contactCount].email);
    while (mail_validation(addressBook) == 0) {
        printf("Enter a valid Email id: ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].email);
    }

    printf("Contact successfully created\n");
    addressBook->contactCount++;  // Increment the contact count
}

// Function to display a contact's details
void displayContact(Contact contact) {
    printf("\nContact Details:\n");
    printf("Name: %s\n", contact.name);
    printf("Phone: %s\n", contact.phone);
    printf("Email: %s\n", contact.email);
}

// Function to allow user to select a contact based on displayed index (if multiple matches)
int selectContact(AddressBook *addressBook, int *matchedIndices, int matchedCount) {
    int selection;
    printf("\nEnter the index number of the contact to select: ");
    scanf("%d", &selection);
    selection--;  // Convert to zero-based index

    if (selection >= 0 && selection < matchedCount) {
        return matchedIndices[selection];
    } else {
        printf("Invalid selection. Please try again.\n");
        return -1;
    }
}

// Function to handle matching contacts and proceed based on whether there is one or multiple matches
int handleMatchingContacts(AddressBook *addressBook, int *matchedIndices, int matchedCount) {
    if (matchedCount == 1) {
        // Only one match, no need to select, return the first match directly
        return matchedIndices[0];
    } else if (matchedCount > 1) {
        // Multiple matches, ask user to select by index
        return selectContact(addressBook, matchedIndices, matchedCount);
    } else {
        printf("No contacts found.\n");
        return -1;
    }
}

// Search for contacts by partial match
void searchContact(AddressBook *addressBook) {
    int menu;
    printf("\nSearch by:\n");
    printf("1. Search By Name\n");
    printf("2. Search By Phone No\n");
    printf("3. Search By Email id\n");
    printf("4. Exit\n");
    scanf("%d", &menu);
    getchar();  // Consume newline

    char search_term[100];
    switch (menu) {
        case 1:
            printf("Enter the name you want to search: ");
            break;
        case 2:
            printf("Enter the phone number you want to search: ");
            break;
        case 3:
            printf("Enter the email you want to search: ");
            break;
        case 4:
            return;  // Exit the search
        default:
            printf("Invalid choice.\n");
            return;
    }
    scanf("%[^\n]", search_term);
    getchar();  // Consume newline

    // Array to store the indices of matched contacts
    int matchedIndices[100];
    int matchedCount = 0;

    // Display all matching contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((menu == 1 && strstr(addressBook->contacts[i].name, search_term)) ||
            (menu == 2 && strstr(addressBook->contacts[i].phone, search_term)) ||
            (menu == 3 && strstr(addressBook->contacts[i].email, search_term))) {
            printf("%d. Name: %s, Phone: %s, Email: %s\n", matchedCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            matchedIndices[matchedCount] = i;
            matchedCount++;
        }
    }

    int selectedIndex = handleMatchingContacts(addressBook, matchedIndices, matchedCount);
    if (selectedIndex != -1) {
        displayContact(addressBook->contacts[selectedIndex]);
    }
}

// Edit a contact by partial match and user selection
void editContact(AddressBook *addressBook) {
    int option;
    printf("\nEdit by:\n");
    printf("1. Edit Contact By Name\n");
    printf("2. Edit Contact By Phone No\n");
    printf("3. Edit Contact By Email id\n");
    printf("4. Exit\n");
    scanf("%d", &option);
    getchar();

    char search_term[100];
    switch (option) {
        case 1:
            printf("Enter the name you want to edit: ");
            break;
        case 2:
            printf("Enter the phone number you want to edit: ");
            break;
        case 3:
            printf("Enter the email you want to edit: ");
            break;
        case 4:
            return;  // Exit edit
        default:
            printf("Invalid choice.\n");
            return;
    }
    scanf("%[^\n]", search_term);
    getchar();  // Consume newline

    // Array to store the indices of matched contacts
    int matchedIndices[100];
    int matchedCount = 0;

    // Display matching contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((option == 1 && strstr(addressBook->contacts[i].name, search_term)) ||
            (option == 2 && strstr(addressBook->contacts[i].phone, search_term)) ||
            (option == 3 && strstr(addressBook->contacts[i].email, search_term))) {
            printf("%d. Name: %s, Phone: %s, Email: %s\n", matchedCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            matchedIndices[matchedCount] = i;
            matchedCount++;
        }
    }

    int selectedIndex = handleMatchingContacts(addressBook, matchedIndices, matchedCount);
    if (selectedIndex == -1) return;

    // Prompt for which information to edit
    int fieldOption;
    printf("\nWhat would you like to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    scanf("%d", &fieldOption);
    getchar(); // Consume newline

    // Edit the selected contact based on user's choice
    char new_value[100];
    switch (fieldOption) {
        case 1:
            printf("Enter the new name: ");
            scanf("%[^\n]", new_value);
            strcpy(addressBook->contacts[selectedIndex].name, new_value);
            break;
        case 2:
            printf("Enter the new phone number: ");
            scanf("%s", new_value);
            strcpy(addressBook->contacts[selectedIndex].phone, new_value);
            break;
        case 3:
            printf("Enter the new email: ");
            scanf("%s", new_value);
            strcpy(addressBook->contacts[selectedIndex].email, new_value);
            break;
        case 4:
            return; // Exit editing
        default:
            printf("Invalid choice. No changes made.\n");
            return;
    }
    printf("Contact edited successfully.\n");
}

// Delete a contact by partial match and user selection
void deleteContact(AddressBook *addressBook) {
    int option;
    printf("\nDelete by:\n");
    printf("1. Delete Contact By Name\n");
    printf("2. Delete Contact By Phone No\n");
    printf("3. Delete Contact By Email id\n");
    printf("4. Exit\n");
    scanf("%d", &option);
    getchar();

    char search_term[100];
    switch (option) {
        case 1:
            printf("Enter the name you want to delete: ");
            break;
        case 2:
            printf("Enter the phone number you want to delete: ");
            break;
        case 3:
            printf("Enter the email you want to delete: ");
            break;
        case 4:
            return;  // Exit delete
        default:
            printf("Invalid choice.\n");
            return;
    }
    scanf("%[^\n]", search_term);
    getchar();  // Consume newline

    // Array to store the indices of matched contacts
    int matchedIndices[100];
    int matchedCount = 0;

    // Display matching contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((option == 1 && strstr(addressBook->contacts[i].name, search_term)) ||
            (option == 2 && strstr(addressBook->contacts[i].phone, search_term)) ||
            (option == 3 && strstr(addressBook->contacts[i].email, search_term))) {
            printf("%d. Name: %s, Phone: %s, Email: %s\n", matchedCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            matchedIndices[matchedCount] = i;
            matchedCount++;
        }
    }

    int selectedIndex = handleMatchingContacts(addressBook, matchedIndices, matchedCount);
    if (selectedIndex == -1) return;

    // Confirm deletion
    printf("Are you sure you want to delete this contact? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);  // Note the space before %c to consume any newline
    if (confirm == 'y' || confirm == 'Y') {
        // Delete the selected contact
        for (int j = selectedIndex; j < addressBook->contactCount - 1; j++) {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }
        addressBook->contactCount--;  // Decrement contact count
        printf("Contact deleted successfully.\n");
    } else {
        printf("Deletion canceled.\n");
    }
}

// Save contacts to file and exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
