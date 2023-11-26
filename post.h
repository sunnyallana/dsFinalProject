// post.h
#ifndef POST_H
#define POST_H

#pragma once
#include <iostream>
#include "linkedList.h"
#include "user.h"
using namespace std;

class user; // Forward declaration

class post {
private:
    int likesCount;
    int postId;
    static int nextPostId;
    std::string postName;
    std::string postDescription;
    user* owner;
    linkedList<user*> usersThatLiked;

    post(); // private constructor

public:
    // Getter methods
    int getLikesCount() const;
    int getPostId() const;
    string getPostName() const;
    string getPostDescription() const;
    user* getOwner() const;

    // Setter methods
    void setPostName(const string& newName);
    void setPostDescription(const string& newDescription);

    post(user* receiveOwner, const string receiveName, const string receiveDescription);

    void likePost(user* receiveUser);
    void removeLike(user* receiveUser);
    bool isOwner(user* receiveOwner);
    void editName(user* receiveOwner, string receivePostName);
    void editDescription(user* receiveOwner, string receivePostDescription);
    void displayUsersThatLiked();
    void display();
};
#endif // POST_H