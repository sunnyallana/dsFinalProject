#include <iostream>
#include "user.h"
#include "post.h"
using namespace std;


class NetworkAnalyser {
private:
    linkedList<user*> userNetwork;
    int uCount;

public:
    NetworkAnalyser() : uCount(0) {}

    ~NetworkAnalyser() {
        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            listNode<user*>* next = temp->next;
            delete temp->data;
            delete temp;
            temp = next;
        }
    }

    user* findUser(int userId) {
        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserId() == userId) {
                return temp->data;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void addUser(const string& userName, const string& userPassword) {
        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                cout << "User with the same name already exists." << endl;
                return;
            }
            temp = temp->next;
        }

        user* newUser = new user(userName, userPassword);
        userNetwork.insert(newUser);
        uCount++;
        cout << "User added successfully." << endl;
    }

    void removeUser(const string& userName) {
        listNode<user*>* temp = userNetwork.getHead();
        listNode<user*>* prev = nullptr;

        while (temp) {
            if (temp->data->getUserName() == userName) {
                if (prev) {
                    prev->next = temp->next;
                }
                else {
                    userNetwork.setHead(temp->next);
                }
                delete temp->data;
                delete temp;
                cout << "User removed successfully." << endl;
                uCount--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "User not found." << endl;
    }

    void displayUsers() {
        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            cout << "User ID: " << temp->data->getUserId() << ", User Name: " << temp->data->getUserName() << endl;
            temp = temp->next;
        }
    }

    void addFriend(const std::string& userName1, const std::string& userName2) {
        user* user1 = nullptr;
        user* user2 = nullptr;


        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName1) {
                user1 = temp->data;
            }
            if (temp->data->getUserName() == userName2) {
                user2 = temp->data;
            }

            temp = temp->next;


            if (user1 && user2) {
                break;
            }
        }

        if (user1 && user2) {
            user1->addFriend(user2);
            user2->addFriend(user1);
            cout << "Friend added successfully." << endl;
        }
        else {
            cout << "One or both users not found." << endl;
        }
    }

    void removeFriend(const string& userName1, const string& userName2) {
        user* user1 = nullptr;
        user* user2 = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName1) {
                user1 = temp->data;
            }
            if (temp->data->getUserName() == userName2) {
                user2 = temp->data;
            }

            temp = temp->next;

            if (user1 && user2) {
                break;
            }
        }

        if (user1 && user2) {
            user1->removeFriend(user2);
            user2->removeFriend(user1);
            cout << "Friend removed successfully." << endl;
        }
        else {
            cout << "One or both users not found." << endl;
        }
    }

    void addPost(const string& userName, const string& postName, const string& postDes) {
        user* currentUser = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                currentUser = temp->data;
                break;
            }
            temp = temp->next;
        }

        if (currentUser) {
            post* newPost = new post(currentUser, postName, postDes);
            cout << "Post added successfully." << endl;
        }
        else {
            cout << "User not found." << endl;
        }
    }

    void removePost(const string& userName, const string& postName) {
        user* currentUser = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                currentUser = temp->data;
                break;
            }
            temp = temp->next;
        }

        if (currentUser) {
            listNode<post*>* postTemp = currentUser->getPostsByUser();
            listNode<post*>* postPrev = nullptr;

            while (postTemp) {
                if (postTemp->data->getPostName() == postName) {
                    if (postPrev) {
                        postPrev->next = postTemp->next;
                    }
                    else {
                        currentUser->setPostsByUserHead(postTemp->next);
                    }
                    delete postTemp->data;
                    delete postTemp;
                    cout << "Post removed successfully." << endl;
                    return;
                }
                postPrev = postTemp;
                postTemp = postTemp->next;
            }

            cout << "Post not found." << endl;
        }
        else {
            cout << "User not found." << endl;
        }
    }


    void editPost(const string& userName, const string& oldPostName, const string& newPostName, const string& newPostDes) {
        user* currentUser = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                currentUser = temp->data;
                break;
            }
            temp = temp->next;
        }

        if (currentUser) {
            listNode<post*>* postTemp = currentUser->getPostsByUser();

            while (postTemp) {
                if (postTemp->data->getPostName() == oldPostName) {
                    postTemp->data->setPostName(newPostName);
                    postTemp->data->setPostDescription(newPostDes);
                    cout << "Post edited successfully." << endl;
                    return;
                }
                postTemp = postTemp->next;
            }

            cout << "Post not found." << endl;
        }
        else {
            cout << "User not found." << endl;
        }
    }


    void displayUserPosts(const string& userName) {
        user* currentUser = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                currentUser = temp->data;
                break;
            }
            temp = temp->next;
        }

        if (currentUser) {
            currentUser->displayPosts();
        }
        else {
            cout << "User not found." << endl;
        }
    }

    void displayFriends(const string& userName) {
        user* currentUser = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName) {
                currentUser = temp->data;
                break;
            }
            temp = temp->next;
        }

        if (currentUser) {
            currentUser->displayFriends();
        }
        else {
            cout << "User not found." << endl;
        }
    }

    void findMutualFriends(const string& userName1, const string& userName2) {
        user* user1 = nullptr;
        user* user2 = nullptr;

        listNode<user*>* temp = userNetwork.getHead();
        while (temp) {
            if (temp->data->getUserName() == userName1) {
                user1 = temp->data;
            }
            if (temp->data->getUserName() == userName2) {
                user2 = temp->data;
            }

            temp = temp->next;

            if (user1 && user2) {
                break;
            }
        }

        if (user1 && user2) {
            listNode<user*>* temp1 = user1->getUserFriends();
            listNode<user*>* temp2 = user2->getUserFriends();

            cout << "Mutual Friends: ";
            while (temp1 && temp2) {
                if (temp1->data == temp2->data) {
                    cout << temp1->data->getUserName() << " ";
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
                else if (temp1->data < temp2->data) {
                    temp1 = temp1->next;
                }
                else {
                    temp2 = temp2->next;
                }
            }
            cout << endl;
        }
        else {
            cout << "One or both users not found." << endl;
        }
    }

};