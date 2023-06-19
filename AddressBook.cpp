#include "addressbook.h"

AddressBook::AddressBook(const std::string& file) : fileName(file) {
    loadContacts();
}

void AddressBook::addContact(const Contact& contact) {
    if (!isValidEmailAddress(contact.email)) {
        std::cout << "Invalid email address format. The contact will not be added.\n";
        return;
    }

    if (!isValidPhoneNumber(contact.phone)) {
        std::cout << "Invalid phone number format. The contact will not be added.\n";
        return;
    }

    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << contact.name << ',' << contact.email << ',' << contact.phone << '\n';
        file.close();
        std::cout << "The contact was successfully added.\n";
    } else {
        std::cout << "Error: Could not open the file.\n";
    }
}

void AddressBook::removeContact(const std::string& name) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::ofstream outFile("temp.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: Could not create temporary file.\n";
        inFile.close();
        return;
    }

    std::string line;
    bool contactFound = false;
    while (std::getline(inFile, line)) {
        auto commaPos1 = line.find(',');
        if (commaPos1 != std::string::npos) {
            std::string contactName = line.substr(0, commaPos1);
            if (contactName != name) {
                outFile << line << '\n';
            } else {
                contactFound = true;
            }
        }
    }
    inFile.close();
    outFile.close();

    if (contactFound) {
        std::remove(fileName.c_str());
        std::rename("temp.txt", fileName.c_str());
        std::cout << "The contact was successfully deleted.\n";
    } else {
        std::cout << "Contact not found.\n";
        std::remove("temp.txt");
    }
}

void AddressBook::updateContact(const std::string& name, const Contact& newContact) {
    if (!isValidEmailAddress(newContact.email)) {
        std::cout << "Invalid email address format. The contact will not be updated.\n";
        return;
    }

    if (!isValidPhoneNumber(newContact.phone)) {
        std::cout << "Invalid phone number format. The contact will not be updated.\n";
        return;
    }

    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::ofstream outFile("temp.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: Could not create temporary file.\n";
        inFile.close();
        return;
    }

    std::string line;
    bool contactFound = false;
    while (std::getline(inFile, line)) {
        auto commaPos1 = line.find(',');
        if (commaPos1 != std::string::npos) {
            std::string contactName = line.substr(0, commaPos1);
            if (contactName != name) {
                outFile << line << '\n';
            } else {
                outFile << newContact.name << ',' << newContact.email << ',' << newContact.phone << '\n';
                contactFound = true;
            }
        }
    }
    inFile.close();
    outFile.close();

    if (contactFound) {
        std::remove(fileName.c_str());
        std::rename("temp.txt", fileName.c_str());
        std::cout << "The contact was successfully updated.\n";
    } else {
        std::cout << "Contact not found.\n";
        std::remove("temp.txt");
    }
}

void AddressBook::searchContacts(const std::string& term) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::string line;
    std::vector<Contact> results;
    while (std::getline(file, line)) {
        auto commaPos1 = line.find(',');
        auto commaPos2 = line.find(',', commaPos1 + 1);
        if (commaPos1 != std::string::npos && commaPos2 != std::string::npos) {
            std::string contactName = line.substr(0, commaPos1);
            std::string contactEmail = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            std::string contactPhone = line.substr(commaPos2 + 1);
            if (contactName.find(term) != std::string::npos ||
                contactEmail.find(term) != std::string::npos ||
                contactPhone.find(term) != std::string::npos) {
                Contact contact;
                contact.name = contactName;
                contact.email = contactEmail;
                contact.phone = contactPhone;
                results.push_back(contact);
            }
        }
    }
    file.close();

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
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::string line;
    std::cout << "Contacts:\n";
    bool contactsFound = false;
    while (std::getline(file, line)) {
        auto commaPos1 = line.find(',');
        auto commaPos2 = line.find(',', commaPos1 + 1);
        if (commaPos1 != std::string::npos && commaPos2 != std::string::npos) {
            std::string contactName = line.substr(0, commaPos1);
            std::string contactEmail = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            std::string contactPhone = line.substr(commaPos2 + 1);
            std::cout << contactName << " (" << contactEmail << ", " << contactPhone << ")\n";
            contactsFound = true;
        }
    }
    file.close();

    if (!contactsFound) {
        std::cout << "No contacts found.\n";
    }
}

void AddressBook::saveContacts() {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::ofstream outFile("temp.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: Could not create temporary file.\n";
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        outFile << line << '\n';
    }
    inFile.close();
    outFile.close();

    std::remove(fileName.c_str());
    std::rename("temp.txt", fileName.c_str());
    std::cout << "Contacts saved.\n";
}

void AddressBook::loadContacts() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error: Could not open the file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        auto commaPos1 = line.find(',');
        auto commaPos2 = line.find(',', commaPos1 + 1);
        if (commaPos1 != std::string::npos && commaPos2 != std::string::npos) {
            std::string contactName = line.substr(0, commaPos1);
            std::string contactEmail = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            std::string contactPhone = line.substr(commaPos2 + 1);
            Contact contact;
            contact.name = contactName;
            contact.email = contactEmail;
            contact.phone = contactPhone;
        }
    }
    file.close();
}

bool AddressBook::isValidPhoneNumber(const std::string& phone) {
    // Simple check for a valid phone number format (10 digits)
    std::regex regex("\\d{10}");
    return std::regex_match(phone, regex);
}

bool AddressBook::isValidEmailAddress(const std::string& email) {
    // Simple check for a valid email address format
    std::regex regex("[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,4}");
    return std::regex_match(email, regex);
}

Contact AddressBook::createContact() {
    Contact contact;
    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, contact.name);

    std::cout << "Enter email: ";
    std::getline(std::cin, contact.email);

    std::cout << "Enter phone: ";
    std::getline(std::cin, contact.phone);

    return contact;
}
