#include <iostream>
using namespace std;

// Class for user
class user {
private:
	// Login credentials
	string userName;
	string userPassword;
	// Connectivity
	user* userFriends;
						// Posts array
	// Constants
	int userId;
	int currentPostsCount;
	int currentFriendsCount;
	int postsCapacity;
	int friendsCapacity;

public:
    void setUserName(const string& receiveUserName) { userName = receiveUserName; }
    void setUserPassword(const string& password) { userPassword = password; }
    void setUserId(int id) { userId = id; } // Needs work
    void setCurrentPostsCount(const int& receiveCurrentPostsCount) { currentPostsCount = receiveCurrentPostsCount; }
    void setCurrentFriendsCount(const int& receiveCurrentFriendsCount) { currentFriendsCount = receiveCurrentFriendsCount; }
    void setPostsCapacity(const int& receivePostsCapacity) { postsCapacity = receivePostsCapacity; }
    void setFriendsCapacity(const int& receiveFriendsCapacity) { friendsCapacity = receiveFriendsCapacity; }

    string getUserName() const { return userName; }
    string getUserPassword() const { return userPassword; }
    User* getUserFriends() const { return userFriends; } // Needs work
    int getUserId() const { return userId; }
    int getCurrentPostsCount() const { return currentPostsCount; }
    int getCurrentFriendsCount() const { return currentFriendsCount; }
    int getPostsCapacity() const { return postsCapacity; }
    int getFriendsCapacity() const { return friendsCapacity; }
};

