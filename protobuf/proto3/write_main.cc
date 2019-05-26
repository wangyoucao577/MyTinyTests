#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

// This function fills in a Person message based on user input.
void PromptForAddress(mytest_proto3::Person* person) {
    if (!person){
        return;
    }

    std::cout << "Enter person ID number: ";
    int id;
    std::cin >> id;
    person->set_id(id);
    std::cin.ignore(256, '\n');

    std::cout << "Enter name: ";
    getline(std::cin, *person->mutable_name());

    std::cout << "Enter email address (blank for none): ";
    std::string email;
    getline(std::cin, email);
    if (!email.empty()){
        person->set_email(email);
    }

    while (true){
        std::cout << "Enter a phone number (or leave blank to finish): ";
        std::string number;
        getline(std::cin, number);
        if (number.empty()){
            break;
        }

        mytest_proto3::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        std::cout << "Is this a mobile, home, or work phone? ";
        std::string type;
        getline(std::cin, type);
        if (type == "mobile") {
            phone_number->set_type(mytest_proto3::Person::MOBILE);
        }else if (type == "home") {
            phone_number->set_type(mytest_proto3::Person::HOME);
        }else if (type == "work") {
            phone_number->set_type(mytest_proto3::Person::WORK);
        }else {
            std::cout << "Unknown phone type. Using default." << std::endl;
        }
    }
}

// Main function: Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same file.
int main(int argc, char* argv[]){
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << std::endl;
        return -1;
    }

    mytest_proto3::AddressBook address_book;

    {
        // Read the existing address book. 
        std::fstream input(argv[1], std::ios::in | std::ios::binary);
        if (!input) {
            std::cout << argv[1] << ": File not found. Creating a new file. " << std::endl;
        }else if (!address_book.ParseFromIstream(&input)) {
            std::cerr << "Failed to parse address book. " << std::endl;
            return -1;
        }
    }

    // Add an address.
    PromptForAddress(address_book.add_people());

    {
        // Write the new address book back to disk.
        std::fstream output(argv[1], std::ios::out | std::ios::trunc | std::ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            std::cerr << "Failed to write address book." << std::endl;
            return -1;
        }
    }

    //Optional: Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    
    return 0;
}