#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <fstream>
#include "post.h"

class User {
public:
    
    //default constructor
    User();

    //constructor
    //pre: none
    //post: initializes the user with the provided ID, name, year, zip code, and set of friends
    User(int id, std::string name, int year, int zip, std::set<int> friends, int privacy);

    //pre: none
    //post: returns the user's ID
    int getId() const;

    //pre: none
    //post: returns the user's name
    std::string getName() const;

    //pre: none
    //post: Returns the user's birth year.
    int getYear() const;

    //pre: none
    //post: Returns the user's zip code.
    int getZip() const;

    //pre: none
    //post: returns a reference to the user's set of friends
    std::set<int>& getFriends();

    //pre: the ID is an integer > 0 and is not already in the set
    //post: adds the friend ID to the set
    void addFriend(int id);

    //pre: the ID is an integer > 0 and is in the set
    //post: removes the friend ID from the set
    void deleteFriend(int id);

    //pre: none
    //post: add a post
    void addPost(Post* post);

    //pre: none
    //post: return posts
    std::vector<Post*> getPosts();

    //pre: none
    //post: returns a string that holds the most recent howMany post
    std::string getPostsString(int howMany, bool showOnlyPublic);

    //pre: none
    //post: returns the privacy level
    int getPrivacy();

    //pre: none
    //post: sets the privacy level
    void setPrivacy(int privacy);

private:
    //user ID
    int id_;
    //user name
    std::string name_;
    //user birth year
    int year_;
    //user zip code
    int zip_; 
    //user set of friends
    std::set<int> friends_;
    //vector of posts by this user
    std::vector<Post*> messages_;
    //privacy level of the user - 0 is public and viewable by anyone, 1 is viewable by friends of friends, and 2 is private and viewable only by friends
    int privacy_;
};

#endif
