#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validation.h"

// PHONE VALIDATIONS

// Validates phone number while creating a new contact.
int phone_validation(AddressBook *addressBook) 
{
    int i;
    char* phone = addressBook->contacts[addressBook->contactCount].phone;
    int size = addressBook->contactCount;

    // Check if the phone number contains only digits
    for (i = 0; phone[i] != '\0'; i++) 
    {
        if (!(phone[i] >= '0' && phone[i] <= '9')) 
        {
            return 1;  // Invalid character found
        }
    }

    // Ensure phone number is exactly 10 digits
    if (i != 10) 
    {
        return 1;  // Invalid length
    }

    // Check for duplicates in the existing contact list
    for (i = 0; i < size; i++) 
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0) 
        {
            return 1;  // Duplicate phone number
        }
    }

    return 0;  // Valid phone number
}

// E-MAIL VALIDATIONS

// Validates email while creating a new contact.
int mail_validation(AddressBook *addressBook) 
{
    int i, at_found = 0, at_count = 0, com_found = 0, at_pos = 0, com_pos = 0;
    char* email = addressBook->contacts[addressBook->contactCount].email;
    int len = strlen(email);

    // Check for '@' and ensure there's exactly one
    for (i = 0; email[i] != '\0'; i++) 
    {
        if (email[i] == '@') 
        {
            at_count++;
            if (at_count == 1) 
            {
                at_found = 1; 
                at_pos = i;
            }
        }
    }

    if (at_count != 1) 
    {
        return 0;  // Invalid email: more or less than one '@'
    }

    // Check if email ends with ".com"
    if (len >= 4 && strcmp(&email[len - 4], ".com") == 0) 
    {
        com_found = 1;
        com_pos = len - 4;
    }

    if (!at_found || !com_found || at_pos >= com_pos - 1) 
    {
        return 0;  // Invalid email format
    }

    // Check for duplicate email addresses
    for (i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0) 
        {
            return 0;  // Duplicate email
        }
    }

    return 1;  // Valid email
}

