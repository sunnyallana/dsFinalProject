// user.h
#ifndef USER_H
#define USER_H

#pragma once
#include <iostream>
#include "linkedList.h"
#include "post.h"
using namespace std;

class post; // Forward declaration

class user {
private:
    // Login credentials
    string userName;
    string userPassword;
    // Connectivity
    linkedList<user*> userFriends;
    linkedList<post*> postsByUser;
    // Constants
    int userId;
    static int nextUserId;
    int currentPostsCount;
    int currentFriendsCount;
    user(); // private constructor
public:
    // Setter for user attributes
    void setUserName(const string& receiveUserName);
    void setUserPassword(const string& password);
    void setCurrentPostsCount(const int& receiveCurrentPostsCount);
    void setCurrentFriendsCount(const int& receiveCurrentFriendsCount);
    // Getter for user attributes
    string getUserName() const;
    string getUserPassword() const;
    int getUserId() const;
    int getCurrentPostsCount() const;
    int getCurrentFriendsCount() const;

    user(string receiveUserName, string receiveUserPassword);

    void addFriend(user* receiveFriend);
    void removeFriend(user* receiveFriend);
    void displayFriends();
    void createPost(post* receivePost);
    void deletePost(post* receivePost);
    void displayPosts();
};
#endif // USER_H
