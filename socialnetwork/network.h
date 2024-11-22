#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

class Network {
public:
    
    //default constructor
    Network();

    //getters

    //pre: none
    //post: returns a pointer to the user with the given ID
    User* getUser(int id);

    //pre: none
    //post: returns the ID associated with the given name
    int getId(std::string name);

    //pre: the user is not a nullpointer
    //post: adds the user to the network
    void addUser(User*);

    //pre: both users exist in the network and do not have a connection
    //post: adds a friend connection to the user
    int addConnection(std::string s1, std::string s2);

    //pre: both users exist in the network and have a connection
    //post: deletes the friend connection
    int deleteConnection(std::string s1, std::string s2);

    //pre: none
    //post: returns the number of users in the network
    int numUsers();

    //pre: the file exists
    //post: reads users from a given file
    void readUsers(std::string fname);

    //pre: none
    //post: writes users to a file
    void writeUsers(std::string fname);

    //pre: from and to exist in the network
    //post: returns the shortest path between two users using BFS
    std::vector<int> shortestPath(int from, int to);

    //pre: from and to exist in the network
    //post: returns the shortest path between two users using BFS
    std::vector<int> distanceUser(int from, int& to, int distance);

    //pre: who exists in the network
    //post: returns a list of suggested friends based off that user's "score", or number of shared friends
    std::vector<int> suggestFriends(int who, int& score);

    //pre: none
    //post: returns a list of all connected components in the network using DFS
    std::vector<std::vector<int> > groups();

    //pre: none
    //post: add the new post to the messages vector of the user whose id is ownerId
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    //pre: none
    //post: call User::getPostsString
    std::string getPostsString(int ownerID, int howMany, bool showOnlyPublic);

    //pre: the file exists
    //post: read a post from the file in the given format
    int readPosts(std::string fname);

    //pre: the file exists
    //post: write a post to the file in the given format
    int writePosts(std::string fname);

private:
    //vector of users in the network
    std::vector<User*> users_;
};

#endif
