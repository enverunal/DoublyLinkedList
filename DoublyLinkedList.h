#pragma once
#include <string>
#include <initializer_list>
#include <functional>
#include <cmath>
#include "llUtility.h"

namespace Doubley {
	template <typename T>
	struct node {
		T m_value{};
		node* next{ nullptr };
		node* prev{ nullptr };
	};
}

template <typename T>
class DoublyLinkedList
{
private:
	Doubley::node<T>* startPointer{};
	Doubley::node<T>* lastPointer{};
	Doubley::node<T>* currentPointer{};
	int_fast64_t currentPos{ 0 };
	int_fast64_t m_size{ 0 };
public:
	DoublyLinkedList() noexcept;
	DoublyLinkedList(std::initializer_list<T> list) noexcept;
	DoublyLinkedList(int_fast64_t size);
	~DoublyLinkedList() noexcept;
	int_fast64_t length() noexcept;
	T elementAt(int_fast64_t position);
	void append(const T &value);
	void append(std::initializer_list<T> init_list);
	void insert(const T& value, int_fast64_t position);
	void merge(const DoublyLinkedList<T>& doublyLinkedList) noexcept;
	void removeAt(int_fast64_t position);
	void removeValueFirst(const T& value) noexcept;
	bool contains(const T& value) noexcept;
	bool every(std::function<bool(const T& element)> test) const noexcept;
	void forEach(std::function<void(T& element)> function) noexcept;
	void pop();
	T first() const;
	T last() const;
	bool isEmpty() const noexcept;
	void clear();
	std::string join(const std::string& seperator) const noexcept;
	std::string toString() const noexcept;
	bool operator==(DoublyLinkedList<T>& comparedList)const noexcept;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept{

}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> list) noexcept {
	for (auto i : list) {
		this->append(i);
	}
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(int_fast64_t size) {
	if (size < 0) {
		throw "DoublyLinkedList size cannot be negative number";
	}
	Doubley::node<T>* tempPointer{};
	for (int i{ 0 }; i < size; ++i) {
		if (i == 0) {
			Doubley::node<T>* newnode = new Doubley::node<T>();
			startPointer = newnode;
			lastPointer = newnode;
			tempPointer = newnode;
			++m_size;
		}
		else {
			Doubley::node<T>* newnode = new Doubley::node<T>();
			newnode->prev = tempPointer;
			tempPointer->next = newnode;
			lastPointer = newnode;
			tempPointer = newnode;
			++m_size;
		}
	}
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() noexcept {
	clear();
}

template <typename T>
void DoublyLinkedList<T>::clear() {
	Doubley::node<T>* tempPointer{ nullptr };
	while (startPointer != nullptr) {
		tempPointer = startPointer;
		startPointer = startPointer->next;
		delete tempPointer;
	}
	startPointer = nullptr;
	lastPointer = nullptr;
	m_size = 0;
}

template <typename T>
int_fast64_t DoublyLinkedList<T>::length() noexcept {
	return m_size;
}

template <typename T>
T DoublyLinkedList<T>::elementAt(int_fast64_t position) {
	if (position > m_size || position < 0) {
		throw "DoublyLinkedList cannot reach to this position";
	}
	if (std::abs(currentPos - position) < position) {
		bool backward{ false };
		if (currentPos > position) {
			backward = true;
		}
		for (; backward ? currentPos > position : currentPos < position; backward ? --currentPos : ++currentPos) {
			currentPointer = backward ? currentPointer->prev : currentPointer->next;
			
		}
		return currentPointer->m_value;
	}
	else {
		currentPointer = startPointer;
		currentPos = 0;
		for (; currentPos < position; ++currentPos) {
			currentPointer = currentPointer->next;
		}
		return currentPointer->m_value;
	}
}

template <typename T>
void DoublyLinkedList<T>::append(const T& value) {
	if (m_size == INT_FAST64_MAX) {
		throw "maximum size has been reached already";
		return;
	}
	if (m_size == 0) {
		Doubley::node<T>* newnode = new Doubley::node<T>();
		newnode->m_value = value;
		startPointer = newnode;
		lastPointer = newnode;
		++m_size;
	}
	else {
		Doubley::node<T>* newnode = new Doubley::node<T>();
		newnode->m_value = value;
		lastPointer->next = newnode;
		newnode->prev = lastPointer;
		lastPointer = newnode;
		++m_size;
	}
}

template <typename T>
void DoublyLinkedList<T>::append(std::initializer_list<T> init_list) {
	if (static_cast<int_fast64_t>((m_size + init_list.size())) < m_size) {
		throw "maximum size will be exceded process stopped.";
		return;
	}
	for (auto i : init_list) {
		this->append(i);
	}
}

template <typename T>
void DoublyLinkedList<T>::insert(const T& value, int_fast64_t position) {
	if (position > m_size || position < 0) {
		throw "unexcepted position";
	}
	if (m_size == INT_FAST64_MAX) {
		throw "maximum size has been reached already";
	}

	if (position == m_size) {
		this->append(value);
		return;
	}

	if (position == 0) {
		Doubley::node<T>* newnode = new Doubley::node<T>();
		newnode->m_value = value;
		startPointer->prev = newnode;
		newnode->next = startPointer;
		startPointer = newnode;
		++m_size;
		return;
	}

	std::cout << "searching.." << std::endl;
	if (std::abs(currentPos - position) < position) {
		bool backward{ false };
		if (currentPos > position) {
			backward = true;
		}
		for (; backward ? currentPos > position : currentPos < position; backward ? --currentPos : ++currentPos) {
			currentPointer = backward ? currentPointer->prev : currentPointer->next;
			std::cout << currentPos << " " << std::endl;
		}
		std::cout << "search ended" << std::endl;
	}
	else {
		currentPointer = startPointer;
		currentPos = 0;
		for (; currentPos < position; ++currentPos) {
			currentPointer = currentPointer->next;
			std::cout << currentPos << " " << std::endl;
		}
		std::cout << "search ended" << std::endl;
	}

	Doubley::node<T>* newnode = new Doubley::node<T>();
	newnode->m_value = value;
	currentPointer->prev->next = newnode;
	newnode->prev = currentPointer->prev;
	newnode->next = currentPointer;
	currentPointer->prev = newnode;
	currentPointer = newnode;
	currentPos = position;
	++m_size;
}

template <typename T>
void DoublyLinkedList<T>::merge(const DoublyLinkedList<T>& doublyLinkedList) noexcept {
	Doubley::node<T>* tempPointer{ doublyLinkedList.startPointer };
	for (auto i{ 0 }; i < doublyLinkedList.m_size; ++i) {
		this->append(tempPointer->m_value);
		tempPointer = tempPointer->next;
	}
}

template <typename T>
T  DoublyLinkedList<T>::first() const {
	if (m_size > 0) {
		return startPointer->m_value;
	}else {
		throw "empty";
	}
}

template <typename T>
T  DoublyLinkedList<T>::last() const {
	if (m_size > 0) {
		return lastPointer->m_value;
	}
	else {
		throw "empty";
	}
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const noexcept {
	return m_size > 0 ? false : true;
}

template <typename T>
void DoublyLinkedList<T>::pop() {
	if (m_size == 0) {
		throw "cannot pop DoublyLinkedList size is 0\n";
	}
	if (m_size == 1) {
		delete lastPointer;
		lastPointer = nullptr;
		startPointer = nullptr;
		currentPointer = nullptr;
		currentPos = 0;
		--m_size;
		return;
	}
	if (currentPointer == lastPointer) {
		currentPointer = lastPointer->prev;
	}
	Doubley::node<T>* tempPointer{ lastPointer };
	lastPointer = lastPointer->prev;
	lastPointer->next = nullptr;
	--m_size;
	delete tempPointer;
}

template <typename T>
void DoublyLinkedList<T>::removeAt(int_fast64_t position) {
	if (position < 0 || position > m_size - 1) {
		throw "cannot remove DoublyLinkedList position is not suitable";
	}

	if (position == m_size - 1) {
		this->pop();
		return;
	}

	if (position == 0) {
		std::cout << "deleting" << m_size << std::endl;
		Doubley::node<T>* tempPointer{ startPointer };
		startPointer = startPointer->next;
		startPointer->prev = nullptr;
		delete tempPointer;
		--m_size;
		return;
	}


	std::cout << "searching.." << std::endl;
	if (std::abs(currentPos - position) < position) {
		bool backward{ false };
		if (currentPos > position) {
			backward = true;
		}
		for (; backward ? currentPos > position : currentPos < position; backward ? --currentPos : ++currentPos) {
			currentPointer = backward ? currentPointer->prev : currentPointer->next;
			std::cout << currentPos << " " << std::endl;
		}
		std::cout << "search ended" << std::endl;
	}
	else {
		currentPointer = startPointer;
		currentPos = 0;
		for (; currentPos < position; ++currentPos) {
			currentPointer = currentPointer->next;
			std::cout << currentPos << " " << std::endl;
		}
		std::cout << "search ended" << std::endl;
	}
	
	Doubley::node<T>* tempPointer{ currentPointer };
	currentPointer->prev->next = currentPointer->next;
	currentPointer->next->prev = currentPointer->prev;
	currentPointer = currentPointer->next;
	--m_size;
	delete tempPointer;


}

template <typename T>
void DoublyLinkedList<T>::removeValueFirst(const T& value) noexcept {
	Doubley::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (tempPointer->m_value == value) {
			this->removeAt(i);
			return;
		}
		tempPointer = tempPointer->next;
	}
}

template <typename T>
bool DoublyLinkedList<T>::contains(const T& value) noexcept {
	Doubley::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (tempPointer->m_value == value) {
			return true;
		}
		tempPointer = tempPointer->next;
	}
	return false;
}

template <typename T>
bool DoublyLinkedList<T>::every(std::function<bool(const T& element)> test) const noexcept{
	Doubley::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (!test(tempPointer->m_value)) {
			return false;
		}
		tempPointer = tempPointer->next;
	}
	return true;
}

template <typename T>
void DoublyLinkedList<T>::forEach(std::function<void(T& element)> function) noexcept {
	Doubley::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		function(tempPointer->m_value);
		tempPointer = tempPointer->next;
	}
}

template <typename T>
std::string DoublyLinkedList<T>::join(const std::string& seperator) const noexcept {
	std::string result{};
	if (m_size == 0) {
		result = "-";
		return result;
	}
	else {
		result.reserve(m_size * 4);
		Doubley::node<T>* tempPointer = startPointer;
		for (auto i{ 0 }; i < m_size; ++i) {
			result.append(llUtility::to_string(tempPointer->m_value) + seperator);
			tempPointer = tempPointer->next;
		}
		return result;
	}
}

template <typename T>
std::string DoublyLinkedList<T>::toString() const noexcept {
	std::string result{};
	if (m_size == 0) {
		result = "-";
		return result;
	}
	else {
		result.reserve(m_size * 4);
		Doubley::node<T>* tempPointer = startPointer;
		for (auto i{ 0 }; i < m_size; ++i) {
			result.append(llUtility::to_string(tempPointer->m_value) + "->");
			tempPointer = tempPointer->next;
		}
		return result;
	}
}


template <typename T>
bool DoublyLinkedList<T>::operator==(DoublyLinkedList<T>& comparedList)const noexcept {
	if (this->m_size == comparedList.m_size) {
		Doubley::node<T>* tempPointer1{ this->startPointer };
		Doubley::node<T>* tempPointer2{ comparedList.startPointer };
		for (auto i{ 0 }; i < m_size; ++i) {
			if (tempPointer1->m_value != tempPointer2->m_value) {
				return false;
			}
			tempPointer1 = tempPointer1->next;
			tempPointer2 = tempPointer2->next;
		}
		return true;
	}
	else {
		return false;
	}
}