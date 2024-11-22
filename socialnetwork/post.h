#ifndef POST_H
#define POST_H

#include <string>

class Post {
public:

    //default constructor
    Post();

    //parameterized constructor 
    Post(int messageId, int ownerId, std::string message, int likes);

    //pre: none
    //post: returns the following: [message_] Liked by [likes_] people.
    std::string toString();

    //pre: none
    //post: return message ID
    int getMessageId();

    //pre: none
    //post: return owner ID
    int getOwnerId();

    //pre: none
    //post: return message content
    std::string getMessage();

    //pre: none
    //post: return num of likes
    int getLikes();

    //pre: none
    //post: returns ""
    virtual std::string getAuthor();

    //pre: none
    //post: returns true
    virtual bool getIsPublic();

private:
    //ID of the message
    int messageId_;
    //ID of the owner
    int ownerId_;
    //message content
    std::string message_;
    //num of likes
    int likes_;
};

class IncomingPost : public Post {
public:
    
    //default constructor
    IncomingPost();

    //parameterized constructor
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    //pre: none
    //post: returns returns the following: [author_] wrote[private]: [toString] 
    std::string toString();

    //pre: none
    //post: returns author name
    std::string getAuthor();

    //pre: none
    //post: returns isPublic_
    bool getIsPublic();

private:
    //author of the post
    std::string author_;
    //whether the post is public or not
    bool isPublic_;
};

#endif