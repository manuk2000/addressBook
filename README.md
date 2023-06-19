# Address Book

A simple address book program implemented in C++. The program allows users to add, delete, update, search, list, save, and load contacts from a file.

## Usage

1. Compile the code using a C++ compiler.
2. Run the compiled executable.
3. Follow the on-screen instructions to perform various operations on the address book.

## Dependencies

The program uses the following C++ libraries:

- iostream: For input/output operations.
- fstream: For file handling.
- vector: For storing contacts.
- algorithm: For finding and manipulating contacts.
- regex: For validating phone numbers and email addresses.

## Contact Structure

The contact structure consists of the following fields:

- name: The name of the contact.
- email: The email address of the contact.
- phone: The phone number of the contact.

## Commands

The program supports the following commands:

- `add`: Add a new contact.
- `delete`: Delete a contact.
- `update`: Update a contact.
- `search`: Search for a contact.
- `list`: List all contacts.
- `save`: Save contacts to a file.
- `load`: Load contacts from a file.
- `exit`: Exit the program.

## File Format

Contacts are stored in a file in CSV (comma-separated values) format. Each line represents a contact and contains the following fields:

`name,email,phone`

- `name`: The name of the contact.
- `email`: The email address of the contact.
- `phone`: The phone number of the contact.

## Input Validation

The program validates phone numbers and email addresses using regular expressions. Phone numbers must be in the format `123-456-7890`, and email addresses must follow the standard email format.

Feel free to modify the code to suit your needs.

Enjoy using the Address Book program!
