#ifndef LINKED_LIST_H
#define LINKED_LIST_H


template <class dataType>
class listNode {
public:
    dataType data;
    listNode* next;
    listNode() : data(), next(nullptr) {}
    listNode(dataType value) : data(value), next(nullptr) {}
};

template <class dataType>
class linkedList {
private:
    listNode<dataType>* head;
public:
    listNode<dataType>* getHead() { return head; }
    void setHead(listNode<dataType>* newHead) { head = newHead; }
    linkedList() : head(nullptr) {}
    ~linkedList() {
        clear();
    }
    void insert(dataType receiveValue) {
        listNode<dataType>* newNode = new listNode<dataType>(receiveValue);
        if (!head) {
            head = newNode;
        }
        else {
            listNode<dataType>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void remove(dataType receiveValue) {
        if (!head) {
            return;
        }
        if (head->data == receiveValue) {
            listNode<dataType>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        listNode<dataType>* dummy = head;
        while (dummy->next && dummy->next->data != receiveValue) {
            dummy = dummy->next;
        }

        if (dummy->next) {
            listNode<dataType>* temp = dummy->next;
            dummy->next = dummy->next->next;
            delete temp;
        }
    }
    void display() {
        listNode<dataType>* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    bool search(dataType receiveValue) {
        listNode<dataType>* temp = head;
        while (temp) {
            if (temp->data == receiveValue) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    void clear() {
        while (head) {
            listNode<dataType>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif