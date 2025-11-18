#include <stdexcept>
#include <unordered_set>

#include "list.h"

List::List() : _size(0), head(nullptr), tail(nullptr) {}

List::List(const List& other) : _size(0), head(nullptr), tail(nullptr) {
    copy(other);
}

List::List(std::vector<int> array) : _size(0), head(nullptr), tail(nullptr) {
    for (int arr : array) {
        push_back(arr);
    }
}

List::~List() {
    clear();
}

int List::front() {
    return head -> value;
}

int List::back() {
    return tail -> value;
}

void List::push_back(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }
    _size++;
}

void List::push_front(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    _size++;
}

void List::insert(Node* pos, int value) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    if (pos == tail) {
        push_back(value);
    } else {
        Node* newNode = new Node(value);
        newNode->next = pos->next;
        newNode->prev = pos;
        pos->next->prev = newNode;
        pos->next = newNode;
        _size++;
    }
}

void List::pop_front() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* oldHead = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete oldHead;
    _size--;
}

void List::pop_back() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* oldTail = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete oldTail;
    _size--;
}

void List::erase(Node* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    if (pos == head) {
        pop_front();
    } else if (pos == tail) {
        pop_back();
    } else {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos;
        _size--;
    }
}

void List::clear() {
    while (!empty()) {
        pop_front();
    }
}

void List::reverse() {
    Node* current = head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != nullptr) {
        head = temp->prev;
    }
}

void List::remove_duplicates() {
    Node* current = head;
    std::unordered_set<int> duplicates;
    while (current) {
        if (duplicates.find(current -> value) != duplicates.end()) {
            Node* dupl = current;
            current = current -> next;
            erase(dupl);
        } else {
            duplicates.insert(current -> value);
            current = current -> next;
        }
    }
}

void List::replace(int old_value, int new_value) {
    Node* oldNode = head;
    while (oldNode != nullptr) {
        if (oldNode -> value == old_value) {
            oldNode -> value = new_value;
        }
        oldNode = oldNode -> next;
    }
}

void List::merge(const List& other) {
    Node* mergeHead = other.head;
    while (mergeHead != nullptr) {
        push_back(mergeHead -> value);
        mergeHead = mergeHead -> next;
    }
}

bool List::check_cycle() const {
    Node* hare = head;
    Node* turtle = head;
    while (hare != nullptr && hare -> next != nullptr) {
        turtle = turtle -> next;
        hare = hare -> next -> next;
        if (hare == turtle) {
            return true;
        }
    }
    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const{
    return _size == 0;
}

void List::copy(const List& other) {
    clear();
    Node* current = other.head;
    while (current != nullptr) {
        push_back(current->value);
        current = current -> next;
    }
}
