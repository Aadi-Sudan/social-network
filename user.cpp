#include "user.h"

User::User() : id_(1), name_("Anonymous"), year_(2004), zip_(95129), friends_(), privacy_(0) {}

User::User(int id, std::string name, int year, int zip, std::set<int> friends, int privacy) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
    privacy_ = privacy;
}

int User::getId() const {
    return id_;
}

std::string User::getName() const {
    return name_;
}

int User::getYear() const {
    return year_;
}

int User::getZip() const {
    return zip_;
}

std::set<int>& User::getFriends(){
    return friends_;
}

void User::addFriend(int id) {
    if (id >= 0 && friends_.find(id) == friends_.end()) {
        friends_.insert(id);
    }
}

void User::deleteFriend(int id) {
    if (id >= 0 && friends_.find(id) != friends_.end()) {
        friends_.erase(id);
    }
}

void User::addPost(Post* post) {
    messages_.push_back(post);
}

std::vector<Post*> User::getPosts() {
    return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic)  {
    std::string postString;
    int count = 0;
    for (int i = messages_.size() - 1; i >= 0 && count < howMany; i--) {
        Post* post = messages_[i];  
        if (!showOnlyPublic || post->getIsPublic()) {
            postString += post->toString() + "\n";
            count++;
        }
    }
    return postString;
}   

int User::getPrivacy() {
    return privacy_;
}

void User::setPrivacy(int privacy) {
    privacy_ = privacy;
}