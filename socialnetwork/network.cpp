#include "network.h"

Network::Network() : users_() {}

User* Network::getUser(int id) {
    if (id >= 0 && id < users_.size()) {
        return users_[id];
    }
    return nullptr;
}

void Network::addUser(User* user) {
    if (user) {
        users_.push_back(user);
    }
}

int Network::addConnection(std::string s1, std::string s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);
    if (id1 == -1 || id2 == -1) {
        return -1;
    }
    users_[id1]->addFriend(id2);
    users_[id2]->addFriend(id1);
    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);
    if (id1 == -1 || id2 == -1) {
        return -1;
    }
    users_[id1]->deleteFriend(id2);
    users_[id2]->deleteFriend(id1);
    return 0;
}

int Network::getId(std::string name) {
    for (size_t i = 0; i < users_.size(); i++) {
        if (users_[i]->getName() == name) {
            return users_[i]->getId();
        }
    }
    return -1;
}

int Network::numUsers() {
    return users_.size();
}

void Network:: readUsers(std::string fname) {
    std::ifstream infile(fname);
    if(!infile) {
        std::cout<< "Couldn't open the file" <<std::endl;
        return;
    }

    int id, year, zip;
    std::string name, info;
    std::getline(infile,info);

    // go through the file using the given layout of information to read all the information
    while(std::getline(infile,info)) {
        id = std::stoi(info);
        infile.ignore();

        std::getline(infile,info);
        name = info;
        infile.ignore();

        std::getline(infile,info);
        year = std::stoi(info);

        std::getline(infile,info);
        zip= std::stoi(info);

        // for friends, we need to use a loop
        std::getline(infile,info);
        std::stringstream ss(info);
        std::set<int> friendConnections;
        int friendId;
        while(ss >> friendId) {
            friendConnections.insert(friendId);
        }
        User* user = new User(id, name, year, zip, friendConnections);
        addUser(user);
    }
}

void Network::writeUsers(std::string fname) {
    std::ofstream outfile(fname);
    if (!outfile.is_open()) {
        std::cerr << "Could not open the file " << std::endl;
        return;
    }

    outfile << users_.size() << std::endl;
    for (auto* user : users_) {
        outfile << user->getId() << std::endl;
        outfile << '\t' << user->getName() << std::endl;
        outfile << '\t' << user->getYear() << std::endl;
        outfile << '\t' << user->getZip() << std::endl;
        outfile << '\t';
        
        for (int friendId : user->getFriends()) {
            outfile << friendId << ' ';
        }
        outfile << std::endl;
    }
    outfile.close();
}

std::vector<int> Network::shortestPath(int from, int to) {
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<int> prev(numUsers(), -1);

    visited[from] = true;
    q.push(from);

    while(q.size() > 0) {
        int cur = q.front();
        q.pop();
        for (int friendId : users_[cur]->getFriends()) {
            if (!visited[friendId]) {
                prev[friendId] = cur;
                visited[friendId] = true;
                q.push(friendId);
            }
        }
    }
    std::vector<int> output;
    int cur = to;
    while(cur != -1) {
        output.push_back(cur);
        cur = prev[cur];
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<int> prev(numUsers(), -1);
    std::vector<int> dist(numUsers(), -1);

    if (getUser(from) == nullptr) {
        to = -1;
        return std::vector<int> ();
    }

    dist[from] = 0;
    visited[from] = true;
    q.push(from);

    while(q.size() > 0) {
        int cur = q.front();
        q.pop();
        for (int friendId : users_[cur]->getFriends()) {
            if (!visited[friendId]) {
                prev[friendId] = cur;
                dist[friendId] = dist[cur] + 1;
                visited[friendId] = true;
                q.push(friendId);

                if (dist[friendId] == distance) {
                    to = friendId;
                    break;
                }
            }
        }
    }
    std::vector<int> output;
    int cur = to;

    if (to == -1){
        return std::vector<int> ();
    } else {
        while (cur != -1){
            output.push_back(cur);
            cur = prev[cur];
        }
        std::reverse(output.begin(),output.end());
        return output;
    }
}

std::vector<int> Network::suggestFriends(int who, int& score) {
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<int> dist(numUsers(), -1);
    std::vector<int> friendOfFriend;
    std::vector<int> suggested;

    if (who == -1) {
        return std::vector<int> ();
    }

    dist[who] = 0;
    q.push(who);

    while (q.size() > 0) {
        int cur = q.front();
        q.pop();
        std::set<int> neighbors = users_[cur]->getFriends();
   
        for (auto person : neighbors) {
            if (!visited[person]) {
                visited[person] = true;
                q.push(person);
                dist[person] = dist[cur] + 1;
                if (dist[person > 1]){
                        friendOfFriend.push_back(person);
                }
            }
        }
    }
    User* from = getUser(who);
    std::set<int>friends = from->getFriends();
    score = -1;
    for(auto person : friendOfFriend){
        int personScore;
        User* temp = getUser(person);
        std::set<int> tempFriends = temp->getFriends();

        for (auto fromFriend : friends){
            for (auto connection : tempFriends){
                if(connection = fromFriend){
                    personScore++;
                }
            }
        }
        if (personScore > score || score == -1){
            suggested.clear();
            suggested.push_back(person);
        }
        else if (personScore == score){
            suggested.push_back(person);
        }
    }
    return suggested;
}

std::vector<std::vector<int> > Network::groups(){
    std::vector<std::vector<int> > groups;
    std::vector<bool> visited(numUsers(), false);

    for (auto* user : users_){
        if (!visited[user->getId()]){
            std::stack<int> stck;
            std::vector<int> group;
            stck.push(user->getId());
            visited[user->getId()] = true;

            while (stck.size() > 0){
                int cur = stck.top();
                User* temp = getUser(cur);
                stck.pop();
                group.push_back(cur);

                for (auto neighbor : temp->getFriends()){
                    if (!visited[neighbor]){
                        visited[neighbor] = true;
                        stck.push(neighbor);
                    }
                } 
            }
            groups.push_back(group);
        }
    }
    return groups;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    int messageId = 0;
    for (auto person : users_) {
        for (auto post : person->getPosts())
        {
            messageId++;
        }
    }
    User* poster = getUser(ownerId);
    if (isIncoming) {
        Post* newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
        poster->User::addPost(newPost);
    } else {
        Post* newPost = new Post(messageId, ownerId, message, likes);
        poster->User::addPost(newPost);
    }
}

std::string Network::getPostsString(int ownerID, int howMany, bool showOnlyPublic){
    User* user = getUser(ownerID);
    std::string postString = user->getPostsString(howMany, showOnlyPublic);  
    return postString;
}

int Network::readPosts(std::string fname){
    std::string line;
    std::ifstream infile(fname);
    if (infile.is_open()){
        std::getline(infile, line);

        while(std::getline(infile, line)){
            int messageId = std::stoi(line); 

            std::getline(infile, line);
            std::string message = line.substr(1);

            std::getline(infile, line);
            int ownerId = std::stoi(line);

            std::getline(infile, line);
            int likes = std::stoi(line); 

            std::getline(infile, line); 
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::string s = line;

            std::getline(infile, line);
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::string author = line; 

            if (!s.empty()){
                if (s == "public"){
                    addPost(ownerId, message, likes, true, author, true);
                } else{
                    addPost(ownerId, message, likes, true, author, false);
                }

            } else{
                addPost(ownerId, message, likes, false, author, false);
            }     
        } infile.close();
    } else{
        return -1;
    } return 0;
}

bool compare(Post* p1, Post* p2){
    return p1->getMessageId() < p2->getMessageId();
}

int Network::writePosts(std::string fname){
    std::ofstream outfile(fname);
    int amount;
    std::vector<Post*> posts;
    if(!outfile){
        return -1;
    }
    for(auto users: users_){
        std::vector<Post*> Posts = users->getPosts();
        for(auto post : Posts){
            posts.push_back(post);
        }
    }

    std::sort(posts.begin(), posts.end(), compare);
    outfile << posts.size() << std::endl;
    for(auto post : posts){
        outfile << post->getMessageId() << std::endl;
        outfile << '\t' << post->getMessage() << std::endl;
        outfile << '\t' << post->getOwnerId() << std::endl;
        outfile << '\t' << post->getLikes() << std::endl;
        std::string author = post->getAuthor();
    }
}