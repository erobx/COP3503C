#pragma once
#include <iostream>
#include <exception>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Nested class
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};

	// Construction / Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	// Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	// Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

private:
	Node* head;
	Node* tail;
	unsigned int nodes;
};

// Constructor
template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	nodes = 0;
}

// Big three
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	this->head = nullptr;
	this->tail = nullptr;
	this->nodes = 0;
	Node* p1 = list.head;
	while (p1 != nullptr) {
		AddTail(p1->data);
		p1 = p1->next;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	this->Clear();

	this->nodes = rhs.nodes;
	Node* p1 = rhs.head;
	for (unsigned int i = 0; i < rhs.nodes; i++) {
		this->AddTail(p1->data);
		p1 = p1->next;
	}
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current->next;
		delete current;
		current = temp;
	}
}

// Behaviors
template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* current = head;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* current = tail;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->prev;
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node == nullptr)
		return;
	cout << node->data << endl;
	PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node == nullptr)
		return;
	cout << node->data << endl;
	PrintReverseRecursive(node->prev);
}

// Accessors
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return nodes;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	try {
		if (index < 0 || index > nodes)
			throw out_of_range("out_of_range");
	}
	catch (out_of_range const&) {
		return nullptr;
	}
	Node* current = head;
	int i = 0;
	while (current != nullptr) {
		if (i == index)
			return current;
		i++;
		current = current->next;
	}
	return current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	try {
		if (index < 0 || index > nodes)
			throw out_of_range("out_of_range");
	}
	catch (out_of_range const&) {
		return nullptr;
	}
	Node* current = head;
	unsigned int i = 0;
	while (current != nullptr) {
		if (i == index)
			return current;
		i++;
		current = current->next;
	}
	return current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == data)
			return current;
		else
			current = current->next;
	}
	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == data)
			return current;
		else
			current = current->next;
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == value) {
			outData.push_back(current);
			current = current->next;
		}
		else
			current = current->next;
	}
}

// Insertion
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	// Create new node
	Node* newNode = new Node;
	newNode->data = data;
	newNode->prev = nullptr;

	// Check if list is empty
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		nodes++;
	}
	// If not empty
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		nodes++;
	}
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = nullptr;

	// Check if list is empty
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		nodes++;
	}
	// If not empty
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		nodes++;
	}
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (int i = count - 1; i > -1; i--) {
		AddHead(data[i]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	if (node == nullptr)
		return;
	if (node == tail)
		AddTail(data);
	else {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = node->next;
		newNode->prev = node;
		node->next = newNode;
		nodes++;
	}
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	if (node == nullptr)
		return;
	if (node == head)
		AddHead(data);
	else {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->prev = node->prev;
		node->prev->next = newNode;
		newNode->next = node;
		node->prev = newNode;
		nodes++;
	}
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	Node* node = GetNode(index);
	if (node == nullptr) {
		AddTail(data);
	}
	else if (index == 0) {
		AddHead(data);
	}
	else {
		for (unsigned int i = nodes; i > index - 1; i--) {
			node = GetNode(i);
		}
		InsertBefore(node, data);
	}
}

// Removal
template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (head == nullptr)
		return false;
	Node* temp = head->next;
	delete head;
	head = temp;
	if (head != nullptr)
		head->prev = nullptr;
	nodes--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail == head) {
		this->RemoveHead();
		return false;
	}
	Node* prev = tail->prev;
	delete tail;
	tail = prev;
	if (tail != nullptr)
		tail->next = nullptr;
	nodes--;
	return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	unsigned int count = 0;
	Node* current = head;
	Node* temp = nullptr;

	while (current != nullptr) {
		if (current->data == data) {
			count++;
			temp = current->next;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			delete current;
			current = temp;
			nodes--;
		}
		else {
			temp = current;
			current = current->next;
		}
	}
	return count;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	Node* current = GetNode(index);
	if (current == nullptr)
		return false;
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		nodes--;
		return true;
	}
}

template <typename T>
void LinkedList<T>::Clear() {
	this->~LinkedList();
	nodes = 0;
	head = nullptr;
	tail = nullptr;
}

// Operators
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	return GetNode(index)->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	return GetNode(index)->data;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	Node* p1 = head;
	Node* p2 = rhs.head;
	while (p1 != nullptr) {
		if (p1->data != p2->data)
			return false;
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}