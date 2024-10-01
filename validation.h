/*
 * Function: phone_validation
 * ----------------------------
 * Validates the phone number for a contact. This function checks if the phone number
 * contains exactly 10 digits and if the phone number is unique (no duplicates allowed).
 *
 * addressBook: Pointer to the AddressBook structure.
 *
 * returns: 0 if the phone number is valid, 1 if invalid (either due to incorrect length,
 *          non-numeric characters, or a duplicate entry).
 */
int phone_validation(AddressBook *addressBook);


/*
 * Function: mail_validation
 * ----------------------------
 * Validates the email address for a contact. This function checks if the email contains
 * exactly one '@' symbol, ends with ".com", and has characters between the '@' and ".com".
 * Additionally, it ensures that the email address is unique (no duplicates allowed).
 *
 * addressBook: Pointer to the AddressBook structure.
 *
 * returns: 1 if the email address is valid, 0 if invalid (either due to incorrect format or
 *          a duplicate entry).
 */
int mail_validation(AddressBook *addressBook);


/*
 * Function: main
 * ----------------------------
 * The entry point of the program. This function initializes the address book and displays
 * a menu for users to manage contacts. The user can create, search, edit, delete, list, and
 * save contacts, or exit the program. The menu runs in a loop until the user decides to exit.
 *
 * returns: 0 when the program exits.
 */
int main();
