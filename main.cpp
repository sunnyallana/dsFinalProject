#include "post.h"
#include "user.h"
#include "networkAnalyzer.h"
#include "avlTree.h"

int main(void) {
    /*user* uOne = new user("Sunny", "sunny123");
    user* uTwo = new user("Allana", "allana123");
    post* pOne = new post(uOne, "The start", "I started something");*/
    
    
    /*avlTree<string> aOne;
    aOne.buildTreeFromDictionary("dictionary.csv");
    cout << aOne.isPasswordStrong("apple") << endl;*/


    NetworkAnalyser nOne;
    nOne.addUser("Sunny", "123");
    nOne.displayUsers();


    //uOne->addFriend(uTwo);
    //pOne->likePost(uOne);
    //pOne->likePost(uTwo);
    //cout << ((pOne->isOwner(uOne)) ? "Yes" : "No") << endl;
    //cout << ((pOne->isOwner(uTwo)) ? "Yes" : "No") << endl;
    //uOne->displayFriends();
    //uTwo->displayFriends();
    //pOne->display();
    //cout << uOne->getCurrentFriendsCount() << endl;
    //delete uOne;
    //delete uTwo;
}