#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

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
    AddressBook(const std::string& file) : fileName(file) {
        loadContacts();
    }

   void AddressBook::addContact(const Contact& contact) {
    contacts.push_back(contact);
    std::cout << "The contact was successfully added.\n";
}

void AddressBook::removeContact(const std::string& name) {
    auto it = std::find_if(contacts.begin(), contacts.end(),
                           [&](const Contact& c) { return c.name == name; });
    if (it != contacts.end()) {
        contacts.erase(it);
        std::cout << "The contact was successfully deleted.\n";
    } else {
        std::cout << "Contact not found.\n";
    }
}

void AddressBook::updateContact(const std::string& name, const Contact& newContact) {
    auto it = std::find_if(contacts.begin(), contacts.end(),
                           [&](const Contact& c) { return c.name == name; });
    if (it != contacts.end()) {
        it->email = newContact.email;
        it->phone = newContact.phone;
        std::cout << "The contact was successfully updated.\n";
    } else {
        std::cout << "Contact not found.\n";
    }
}

void AddressBook::searchContacts(const std::string& term) {
    std::vector<Contact> results;
    for (const auto& contact : contacts) {
        if (contact.name.find(term) != std::string::npos ||
            contact.email.find(term) != std::string::npos ||
            contact.phone.find(term) != std::string::npos) {
            results.push_back(contact);
        }
    }

    std::cout << "Results:\n";
    if (!results.empty()) {
        for (const auto& contact : results) {
            std::cout << contact.name << " (" << contact.email << ", " << contact.phone << ")\n";
        }
    } else {
        std::cout << "No matching contacts found.\n";
    }
}

void AddressBook::listContacts() {
    std::cout << "Contacts:\n";
    if (!contacts.empty()) {
        for (const auto& contact : contacts) {
            std::cout << contact.name << " (" << contact.email << ", " << contact.phone << ")\n";
        }
    } else {
        std::cout << "No contacts found.\n";
    }
}

void AddressBook::saveContacts() {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& contact : contacts) {
            file << contact.name << ',' << contact.email << ',' << contact.phone << '\n';
        }
        std::cout << "The contacts were successfully saved.\n";
    } else {
        std::cout << "Error: Could not open the file.\n";
    }
    file.close();
}

void AddressBook::loadContacts() {
    std::ifstream file(fileName);
    if (file.is_open()) {
        contacts.clear();
        std::string line;
        while (std::getline(file, line)) {
            auto commaPos1 = line.find(',');
            auto commaPos2 = line.find(',', commaPos1 + 1);
            if (commaPos1 != std::string::npos && commaPos2 != std::string::npos) {
                Contact contact;
                contact.name = line.substr(0, commaPos1);
                contact.email = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
                contact.phone = line.substr(commaPos2 + 1);
                contacts.push_back(contact);
            }
        }
        std::cout << "The contacts were successfully loaded.\n";
    } else {
        std::cout << "Error: Could not open the file.\n";
    }
    file.close();
}

bool AddressBook::isValidPhoneNumber(const std::string& phone) {
    std::regex regex("^\\d{3}-\\d{3}-\\d{4}$");
    return std::regex_match(phone, regex);
}

bool AddressBook::isValidEmailAddress(const std::string& email) {
    std::regex regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, regex);
}
};
int main() {
    std::string fileName = "contacts.txt";
    AddressBook addressBook(fileName);

    while (true) {
    std::cout << "Welcome to the Address Book:\n\n"
              << "Commands:\n"
              << "add - add a new contact\n"
              << "delete - delete a contact\n"
              << "update - update a contact\n"
              << "search - search for a contact\n"
              << "list - list all contacts\n"
              << "save - save contacts to a file\n"
              << "load - load contacts from a file\n"
              << "exit - exit the program\n\n";
        std::cout << "Please enter a command: ";
        std::string command;
        std::getline(std::cin, command);

        if (command == "add") {
            Contact contact;
            std::cout << "Please enter the name of the contact: ";
            std::getline(std::cin, contact.name);

            do {
                std::cout << "Please enter the email address of the contact: ";
                std::getline(std::cin, contact.email);
                if (!addressBook.isValidEmailAddress(contact.email)) {
                    std::cout << "Invalid email address format. Please try again.\n";
                }
            } while (!addressBook.isValidEmailAddress(contact.email));

            do {
                std::cout << "Please enter the phone number of the contact: ";
                std::getline(std::cin, contact.phone);
                if (!addressBook.isValidPhoneNumber(contact.phone)) {
                    std::cout << "Invalid phone number format. Please try again.\n";
                }
            } while (!addressBook.isValidPhoneNumber(contact.phone));

            addressBook.addContact(contact);
        } else if (command == "delete") {
            std::cout << "Please enter the name of the contact: ";
            std::string name;
            std::getline(std::cin, name);
            addressBook.removeContact(name);
        } else if (command == "update") {
            std::cout << "Please enter the name of the contact: ";
            std::string name;
            std::getline(std::cin, name);
            Contact newContact;
            std::cout << "Please enter the new email address: ";
            std::getline(std::cin, newContact.email);

            if (!addressBook.isValidEmailAddress(newContact.email)) {
                std::cout << "Invalid email address format. The contact will not be updated.\n";
                continue;
            }

            std::cout << "Please enter the new phone number: ";
            std::getline(std::cin, newContact.phone);

            if (!addressBook.isValidPhoneNumber(newContact.phone)) {
                std::cout << "Invalid phone number format. The contact will not be updated.\n";
                continue;
            }

            addressBook.updateContact(name, newContact);
        } else if (command == "search") {
            std::cout << "Please enter the search term: ";
            std::string term;
            std::getline(std::cin, term);
            addressBook.searchContacts(term);
        } else if (command == "list") {
            addressBook.listContacts();
        } else if (command == "save") {
            addressBook.saveContacts();
        } else if (command == "load") {
            addressBook.loadContacts();
        } else if (command == "exit") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid command. Please try again.\n";
        }

        std::cout << std::endl;
    }

    return 0;
}
