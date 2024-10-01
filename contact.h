#ifndef CONTACT_H 
#define CONTACT_H

// Maximum number of contacts allowed in the address book
#define MAX_CONTACTS 100

// Structure to represent a contact
typedef struct {
    char name[50];   // Contact's name
    char phone[20];  // Contact's phone number
    char email[50];  // Contact's email address
} Contact;

// Structure to represent the address book containing contacts
typedef struct {
    Contact contacts[100];  // Array of contacts
    int contactCount;       // Current number of contacts in the address book
} AddressBook;

// Function declarations for managing contacts
void createContact(AddressBook *addressBook);  // Function to create a new contact
void searchContact(AddressBook *addressBook);  // Function to search for a contact
void editContact(AddressBook *addressBook);    // Function to edit an existing contact
void deleteContact(AddressBook *addressBook);  // Function to delete a contact
void listContacts(AddressBook *addressBook);   // Function to list all contacts
void initialize(AddressBook *addressBook);     // Function to initialize and load contacts from file
void saveContactsToFile(AddressBook *AddressBook);  // Function to save contacts to file

#endif
