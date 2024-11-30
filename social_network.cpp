#include <iostream>
#include <string>
#include <cstdlib>
#include "network.h"
#include "user.h"

// we need to first check if the user inputted the necessary arguments
int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Please provide a filename after your executable" << std::endl;
        return 1;
    }

    Network network;

    network.readUsers(argv[1]);
    network.readPosts(argv[2]);

    // infinite loop that gives the user a menu of choices
    //We could have also used a switch system (and that probably would have been better)
    while (true) {
        std::cout << "===== Menu =====" << std::endl;
        std::cout << "1. Add a user" << std::endl;
        std::cout << "2. Add a friend connection" << std::endl;
        std::cout << "3. Delete a friend connection" << std::endl;
        std::cout << "4. Write to file" << std::endl;
        std::cout << "5. Read posts from a file" << std::endl;

        int choice;
        std::cin >> choice;

        // if choice is 1, adds a user to the network
        if (choice == 1) {
            std::string firstName, lastName, name;
            int birthYear, zip;
            std::cout << "Enter your first name, last name, birth year, and zip code: ";
            std::cin >> firstName >> lastName >> birthYear >> zip;
            name = firstName + " " + lastName;
            User* newUser = new User(network.numUsers(), name, birthYear, zip, std::set<int>());
            network.addUser(newUser);

        } 

        // if choice is 2, creates a friend connection
        else if (choice == 2) {
            std::string firstName1, lastName1, firstName2, lastName2;
            std::cout << "Enter the names of the two users to make friends (firstName lastName): ";
            std::cin >> firstName1 >> lastName1 >> firstName2 >> lastName2;
            std::string name1 = firstName1 + " " + lastName1;
            std::string name2 = firstName2 + " " + lastName2;
            int result = network.addConnection(name1, name2);
            if (result == -1) {
                std::cerr << "Error: One or both users not found!" << std::endl;
            } else {
                std::cout << name1 + " and " + name2 + " are now friends." << std::endl;
            }

        } 
        
        // if choice is 3, delete a friend connection
        else if (choice == 3) {
            std::string firstName1, lastName1, firstName2, lastName2;
            std::cout << "Enter the names of the two users who don't want to be friends (firstName lastName): ";
            std::cin >> firstName1 >> lastName1 >> firstName2 >> lastName2;
            std::string name1 = firstName1 + " " + lastName1;
            std::string name2 = firstName2 + " " + lastName2;
            int result = network.deleteConnection(name1, name2);
            if (result == -1) {
                std::cerr << "The given users are not friends or could not be found." << std::endl;
            }
            else {
                std::cout << name1 + " and " + name2 + " are no longer friends." << std::endl;
            }

        } 
        
        // if choice is 4, writes users to a file
        else if (choice == 4) {
            std::string filename;
            std::cout << "Enter filename to write user data to: ";
            std::cin >> filename;
            char* file = &filename[0];
            network.writeUsers(file);
            std::cout << network.numUsers() << " users written to " << filename << std::endl;
        } 

        // if choice is 5, get the most recent posts from a given user
        else if (choice == 5) {
            std::string first, last, name;
            int num;
            std::cin >> first >> last >> num;
            name = first + " " + last;
            User* user = network.getUser(network.getId(name));

            if (user != nullptr) {
                std::vector<Post*> posts = user->getPosts();
                std::string postsString = user->getPostsString(num, false);
                std::cout << postsString;

                if (!postsString.empty()){
                        std::cout << std::endl;
                    }
            } 
        } 
        
        // if choice is anything else, quit the program
        else {
            std::cout << "Invalid choice, terminating program." << std::endl;
            break;
        }
    }

    return 0;
}