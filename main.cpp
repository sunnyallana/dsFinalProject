#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include "post.h"
#include "user.h"
#include "avlTree.h"

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

    void addFriend(const string& userName1, const string& userName2) {
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
            currentUser->createPost(newPost);
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

        // Find the user objects for userName1 and userName2
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
                if (temp1->data->getUserName() == temp2->data->getUserName()) {
                    cout << temp1->data->getUserName() << " ";
                    cout << "Add: " << temp1->data
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
                else if (temp1->data->getUserName() < temp2->data->getUserName()) {
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

void clearScreen() {
    system("cls");
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}

int main() {
    NetworkAnalyser analyzer;

    int choice;
    do {
        cout << "\n\t\t\t   SOCIAL NETWORK ANALYSER\n";
        cout << "\t\t\t\t   WELCOME!\n";
        cout << "\n\t\t\t----------------------------\n\n";
        cout << "\t\t\t\t  Main Menu\n";
        cout << "\n\t\t\t----------------------------\n";
        cout << "\t\t\t|  1. Add User             |\n";
        cout << "\t\t\t|  2. Remove User          |\n";
        cout << "\t\t\t|  3. Add Friend           |\n";
        cout << "\t\t\t|  4. Remove Friend        |\n";
        cout << "\t\t\t|  5. Add Post             |\n";
        cout << "\t\t\t|  6. Edit Post            |\n";
        cout << "\t\t\t|  7. Remove Post          |\n";
        cout << "\t\t\t|  8. Display User Posts   |\n";
        cout << "\t\t\t|  9. Display Friends      |\n";
        cout << "\t\t\t| 10. Find Mutual Friends  |\n";
        cout << "\t\t\t|  0. Exit                 |\n";
        cout << "\t\t\t----------------------------\n";
        cout << "\t\t\t  Enter your choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1: {
            cout << "\n\n\t\tUser Addition\n\n";
            string userName, userPassword;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Enter user password: ";
            cin >> userPassword;
            /*avlTree<string> aOne;
            aOne.buildTreeFromDictionary("dictionary.csv");
            */if (true) {
                cout << "Adding user " << userName << "!\n";
                analyzer.addUser(userName, userPassword);
                delay(2000);
                clearScreen();
            }
            else {
                cerr << "Password is weak" << endl;
            }
            break;
        }
        case 2: {
            cout << "\n\n\t\tUser Removal\n\n";
            string userName;
            cout << "Enter user name to remove: ";
            cin >> userName;
            cout << "Removing user " << userName << "!\n";
            analyzer.removeUser(userName);
            delay(2000);
            clearScreen();
            break;
        }
        case 3: {
            cout << "\n\n\t\tAdd Friend\n\n";
            string userName1, userName2;
            cout << "Enter user name who wants to add friend: ";
            cin >> userName1;
            cout << "Enter user name of the friend needed to be added: ";
            cin >> userName2;
            cout << "Adding friend " << userName2 << " for user " << userName1 << "!\n";
            analyzer.addFriend(userName1, userName2);
            delay(2000);
            clearScreen();
            break;
        }
        case 4: {
            cout << "\n\n\t\tRemove Friend\n\n";
            string userName1, userName2;
            cout << "Enter user name from whom to remove friend: ";
            cin >> userName1;
            cout << "Enter user name of the friend to remove: ";
            cin >> userName2;
            cout << "Removing friend " << userName2 << " from user " << userName1 << "!\n";
            analyzer.removeFriend(userName1, userName2);
            delay(2000);
            clearScreen();
            break;
        }
        case 5: {
            cout << "\n\n\t\tAdd Post\n\n";
            string userName, postName, postDes;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Enter post name: ";
            cin >> postName;
            cout << "Enter post description: ";
            cin.ignore(); // Ignore the newline character in the buffer
            getline(cin, postDes);
            cout << "Creating post " << postName << " for user " << userName << "!\n";
            analyzer.addPost(userName, postName, postDes);
            delay(2000);
            clearScreen();
            break;
        }
        case 6: {
            cout << "\n\n\t\tEdit Post\n\n";
            string userName, oldPostName, newPostName, newPostDes;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Enter old post name: ";
            cin >> oldPostName;
            cout << "Enter new post name: ";
            cin >> newPostName;
            cout << "Enter new post description: ";
            cin.ignore(); // Ignore the newline character in the buffer
            getline(cin, newPostDes);
            cout << "Editing post " << oldPostName << " for user " << userName << "!\n";
            analyzer.editPost(userName, oldPostName, newPostName, newPostDes);
            delay(2000);
            clearScreen();
            break;
        }
        case 7: {
            cout << "\n\n\t\tRemove Post\n\n";
            string userName, postName;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Enter post name to remove: ";
            cin >> postName;
            cout << "Removing post " << postName << " for user " << userName << "!\n";
            analyzer.removePost(userName, postName);
            delay(2000);
            clearScreen();
            break;
        }
        case 8: {
            cout << "\n\n\t\tDisplay Posts\n\n";
            string userName;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Displaying " << userName << "'s posts!\n";
            analyzer.displayUserPosts(userName);
            delay(2000);
            clearScreen();
            break;
        }
        case 9: {
            cout << "\n\n\t\tDisplay Freinds\n\n";
            string userName;
            cout << "Enter user name: ";
            cin >> userName;
            cout << "Displaying friends of " << userName << "!\n";
            analyzer.displayFriends(userName);
            delay(2000);
            clearScreen();
            break;
        }
        case 10: {
            cout << "\n\n\t\tFind Mutual Friends\n\n";
            string userName1, userName2;
            cout << "Enter user name 1: ";
            cin >> userName1;
            cout << "Enter user name 2: ";
            cin >> userName2;
            cout << "Displaying friends of " << userName1 << "& " << userName2 << "!" << endl;
            analyzer.findMutualFriends(userName1, userName2);
            delay(2000);
            clearScreen();
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        delay(1000);
        clearScreen();

    } while (choice != 0);
    return 0;
}