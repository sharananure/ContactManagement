#include <stdio.h>
#include "file.h"
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;  // Declare an AddressBook object
    initialize(&addressBook); // Initialize the address book by loading contacts from the file

    do {
        // Display the menu options to the user
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);  // Get user's choice
        
        // Execute the appropriate function based on user's input
        switch (choice) {
            case 1:
                createContact(&addressBook); // Create a new contact
                break;
            case 2:
                searchContact(&addressBook); // Search for a contact
                break;
            case 3:
                editContact(&addressBook); // Edit an existing contact
                break;
            case 4:
                deleteContact(&addressBook); // Delete a contact
                break;
            case 5:          
                listContacts(&addressBook); // List all contacts
                break;
            case 6:
                printf("Saving contacts...\n");
                saveContactsToFile(&addressBook); // Save all contacts to a file
                break;
            case 7:
                // Provide an option to save before exiting
                int exitOption;
                printf("\nExit Menu:\n");
                printf("1. Save and exit\n");
                printf("2. Exit without saving\n");
                scanf("%d", &exitOption); // Get the exit option

                switch (exitOption) {
                    case 1:
                        printf("Saving contacts and exiting...\n");
                        saveContactsToFile(&addressBook); // Save and exit
                        return 0; // Exit the program
                    case 2:
                        printf("Exiting without saving...\n");
                        return 0; // Exit without saving
                    default:
                        printf("Invalid option. Returning to main menu.\n");
                        break;
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // Handle invalid input
        }
    } while (choice != 7);  // Loop until the user chooses to exit
    
    return 0;  // End the program
}
