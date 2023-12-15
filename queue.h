#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <class T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue." << std::endl;
            exit(EXIT_FAILURE);
        }

        T value = front->data;
        Node<T>* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
        }

        delete temp;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot peek." << std::endl;
            exit(EXIT_FAILURE);
        }

        return front->data;
    }

    void display() const {
        Node<T>* temp = front;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};