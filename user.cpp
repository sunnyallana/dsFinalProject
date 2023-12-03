// user.cpp

#include "user.h"
#include "post.h"

int user::nextUserId = 1;

user::user() : currentFriendsCount(0), currentPostsCount(0), userId(nextUserId++) {
    userName = "";
    userPassword = "";
}

void user::setUserName(const string& receiveUserName) {
    userName = receiveUserName;
}

void user::setUserPassword(const string& password) {
    userPassword = password;
}

void user::setCurrentPostsCount(const int& receiveCurrentPostsCount) {
    currentPostsCount = receiveCurrentPostsCount;
}

void user::setCurrentFriendsCount(const int& receiveCurrentFriendsCount) {
    currentFriendsCount = receiveCurrentFriendsCount;
}

string user::getUserName() const {
    return userName;
}

string user::getUserPassword() const {
    return userPassword;
}

int user::getUserId() const {
    return userId;
}

int user::getCurrentPostsCount() const {
    return currentPostsCount;
}

int user::getCurrentFriendsCount() const {
    return currentFriendsCount;
}

void user::setPostsByUserHead(listNode<post*>* receiveHead) {
    postsByUser.setHead(receiveHead);
}

listNode<post*>* user::getPostsByUser(){
    return postsByUser.getHead();
}

listNode<user*>* user::getUserFriends() {
    return userFriends.getHead();
}


user::user(string receiveUserName, string receiveUserPassword)
    : currentFriendsCount(0), currentPostsCount(0), userId(nextUserId++) {
    userName = receiveUserName;
    userPassword = receiveUserPassword;
}

void user::addFriend(user* receiveFriend) {
    userFriends.insert(receiveFriend);
    receiveFriend->userFriends.insert(this);
    currentFriendsCount++;
    receiveFriend->currentFriendsCount++;
}

void user::removeFriend(user* receiveFriend) {
    userFriends.remove(receiveFriend);
    receiveFriend->userFriends.remove(this);
    currentFriendsCount--;
    receiveFriend->currentFriendsCount--;
}

void user::displayFriends() {
    cout << "Friends of " << userName << ": ";
    listNode<user*>* tempTraversingPointer = userFriends.getHead();
    while (tempTraversingPointer) {
        cout << tempTraversingPointer->data->getUserName() << " ";
        tempTraversingPointer = tempTraversingPointer->next;
    }
    cout << endl;
}

void user::createPost(post* receivePost) {
    postsByUser.insert(receivePost);
    currentPostsCount++;
}

void user::deletePost(post* receivePost) {
    postsByUser.remove(receivePost);
    currentPostsCount--;
}

void user::displayPosts() {
    cout << "Posts by " << userName << ":" << endl;
    listNode<post*>* tempTraversingPointer = postsByUser.getHead();
    while (tempTraversingPointer) {
        cout << "Post ID: " << tempTraversingPointer->data->getPostId() << " - " << tempTraversingPointer->data->getPostName() << endl;
        tempTraversingPointer = tempTraversingPointer->next;
    }
    cout << endl;
}