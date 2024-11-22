#include "post.h"

Post::Post() : messageId_(0), ownerId_(0), message_(""), likes_(0) {};

Post::Post(int messageId, int ownerId, std::string message, int likes){
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

std::string Post::toString(){
    std::string tostring;
    tostring = message_ + " Liked by " + std::to_string(likes_) + " people";
    return tostring;
}

int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}

std::string Post::getMessage(){
    return message_;
}

int Post::getLikes(){
    return likes_;
}

std::string Post::getAuthor(){
    return "";
}

bool Post::getIsPublic(){
    return true;
}

IncomingPost::IncomingPost() : Post(), author_(""), isPublic_(true) {};

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic) {}

std::string IncomingPost::toString(){
    std::string tostring;
    if (isPublic_ == true){
    tostring = author_ + " wrote: " + Post::toString();
    } else {
        tostring = author_ + " wrote (private)" + ": " + Post::toString();
    }
    return tostring;
}

std::string IncomingPost::getAuthor(){
    return author_;
}

bool IncomingPost::getIsPublic(){
    return isPublic_;
}