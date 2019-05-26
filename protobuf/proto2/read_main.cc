#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

// Iterate though all people in the AddressBook and prints info about them.
void ListPeople(const mytest_proto2::AddressBook& address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const mytest_proto2::Person& person = address_book.people(i);

        std::cout << "Person ID: " << person.id() << std::endl;
        std::cout << "  Name: " << person.name() << std::endl;
        if (person.has_email()) {
            std::cout << "  Email address: " << person.email() << std::endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const mytest_proto2::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
                case mytest_proto2::Person::MOBILE:
                    std::cout << "  Mobile phone #: ";
                    break;
                case mytest_proto2::Person::HOME:
                    std::cout << "  Home phone #: ";
                    break;
                case mytest_proto2::Person::WORK:
                    std::cout << "  Work phone #: ";
                    break;
            }
            std::cout << phone_number.number() << std::endl;
        }
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside. 
int main(int argc, char* argv[1]) {
    // Verify that the version of the library that we linked against is 
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << std::endl;
        return -1;
    }

    mytest_proto2::AddressBook address_book;

    {
        // Read the existing address book
        std::fstream input(argv[1], std::ios::in | std::ios::binary);
        if (!address_book.ParseFromIstream(&input)){
            std::cerr << "Failed to parse address book." << std::endl;
            return -1;
        }
    }

    ListPeople(address_book);

    // Optional: Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    
    return 0;
}