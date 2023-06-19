#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <string>
#include <vector>

struct Contact {
    std::string name;
    std::string email;
    std::string phone;
};

class AddressBook {
private:
    std::vector<Contact> contacts;
    std::string fileName;

public:
    AddressBook(const std::string& file);

    void addContact(const Contact& contact);
    void removeContact(const std::string& name);
    void updateContact(const std::string& name, const Contact& newContact);
    void searchContacts(const std::string& term);
    void listContacts();
    void saveContacts();
    void loadContacts();

private:
    bool isValidPhoneNumber(const std::string& phone);
    bool isValidEmailAddress(const std::string& email);
};

#endif // ADDRESSBOOK_H
