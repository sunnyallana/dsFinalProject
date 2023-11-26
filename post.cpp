// post.cpp

#include "post.h"
#include "user.h"

int post::nextPostId = 1;

post::post() : likesCount(0), postName(""), postDescription(""), owner(nullptr), postId(NULL) {}

user* post::getOwner() const {
    return owner;
}

int post::getLikesCount() const {
    return likesCount;
}

int post::getPostId() const {
    return postId;
}

string post::getPostName() const {
    return postName;
}

string post::getPostDescription() const {
    return postDescription;
}

void post::setPostName(const string& newName) {
    postName = newName;
}

void post::setPostDescription(const string& newDescription) {
    postDescription = newDescription;
}

post::post(user* receiveOwner, const string receiveName, const string receiveDescription)
    : likesCount(0), postId(nextPostId++), postName(receiveName), postDescription(receiveDescription) {
    owner = receiveOwner;
    receiveOwner->createPost(this);
}

void post::likePost(user* receiveUser) {
    usersThatLiked.insert(receiveUser);
    likesCount++;
}

void post::removeLike(user* receiveUser) {
    if (usersThatLiked.search(receiveUser)) {
        usersThatLiked.remove(receiveUser);
        likesCount--;
    }
}

bool post::isOwner(user* receiveOwner) {
    return (owner == receiveOwner);
}

void post::editName(user* receiveOwner, string receivePostName) {
    if (isOwner(receiveOwner)) {
        postName = receivePostName;
    }
}

void post::editDescription(user* receiveOwner, string receivePostDescription) {
    if (isOwner(receiveOwner)) {
        postDescription = receivePostDescription;
    }
}

void post::displayUsersThatLiked() {
    if (likesCount == 0) {
        cout << "No users have liked this post." << endl;
    }
    else {
        listNode<user*>* tempTraversingPointer = usersThatLiked.getHead();
        while (tempTraversingPointer) {
            cout << tempTraversingPointer->data->getUserName() << endl;
            tempTraversingPointer = tempTraversingPointer->next;
        }
    }
}


void post::display() {
    cout << "Post ID: " << postId << endl;
    cout << "Post Name: " << postName << endl;
    cout << "Post Description: " << postDescription << endl;
    cout << "Likes: " << likesCount << endl;
    cout << "Liked By Users: ";
    displayUsersThatLiked();
}