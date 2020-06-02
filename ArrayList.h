#pragma once
#include <iostream>
template <typename E>
class ArrayList
{
private:
	E* elementBuffer = nullptr;
	E* tempElementBuffer = nullptr;
	int resizeFactor = 2;
	int bufferSize = 0;
	int size = 0;
	bool isArrayEmpty = true;

	void increaseSize() {
		std::cout << "Resizing from " << this->bufferSize;
		if (this->size == this->bufferSize && this->elementBuffer != nullptr) {

			this->tempElementBuffer = new E[this->bufferSize];

			for (int i = 0; i < this->bufferSize; i++) {
				this->tempElementBuffer[i] = this->elementBuffer[i];
			}

			delete[] this->elementBuffer;

			this->elementBuffer = new E[this->bufferSize * this->resizeFactor];

			for (int i = 0; i < this->bufferSize; i++) {
				this->elementBuffer[i] = this->tempElementBuffer[i];
			}

			delete[] this->tempElementBuffer;

			tempElementBuffer = nullptr;

			int newBufferSize = this->bufferSize * this->resizeFactor; 
			this->bufferSize = newBufferSize;
		}

		std::cout << " To " << this->bufferSize << std::endl;
	}
public:

	ArrayList(int initialCapacity) {
		this->bufferSize = initialCapacity;
		this->elementBuffer = new E[this->bufferSize];
	}
	ArrayList() {
		this->bufferSize = 10;
		this->elementBuffer = new E[this->bufferSize];
	}

	~ArrayList() {
	}

	bool add(E element) {
		this->isArrayEmpty = false;
		if (this->size == this->bufferSize) {
			increaseSize();
		}
		this->elementBuffer[size] = element;
		this->size++;
		return true;
	}

	bool add(int index, E element) {
		this->isArrayEmpty = false;
		if (this->size == this->bufferSize) {
			increaseSize();
		}
		for (int i = size - 1; i >= index; i--) {
			this->elementBuffer[i + 1] = this->elementBuffer[i];
		}
		this->elementBuffer[index] = element;
		this->size++;
		return true;
	}

	bool addAll(int index, E* elements, int arraySize) {
		this->isArrayEmpty = false;
		for (int i = 0; i < arraySize; i++)	{
			add(index + i, elements[i]);
		}
		return true;
	}

	void clear() {
		std::cout << "Clearing " << this->bufferSize;
		this->isArrayEmpty = true;
		this->bufferSize = 10;
		this->size = 0;
		delete[] this->elementBuffer;
		this->elementBuffer = new E[bufferSize];
		std::cout << " to " << this->bufferSize << std::endl;
	}

	bool contains(E element) {
		if (this->size > 0) {
			for (int i = 0; i < size; i++)
			{
				if (elementBuffer[i] == element) {
					return true;
				}
			}
			return false;
		}
		else {
			return false;
		}
	}

	E get(int index) {
		if (this->size > 0 && index < this->size) {
			return elementBuffer[index];
		}
		else {
			return NULL;
		}
	}

	int indexOf(E element) {
		if (this->size > 0) {
			for (int i = 0; i < size; i++)
			{
				if (elementBuffer[i] == element) {
					return i;
				}
			}
			return -1;
		}
		else {
			return -1;
		}
	}

	bool isEmpty() {
		return this->isArrayEmpty;
	}

	int lastIndexOf(E element) {
		if (this->size > 0) {
			for (int i = size; i > -1; i--)	{
				if (elementBuffer[i] == element) {
					return i;
				}
			}
			return -1;
		}
		else {
			return -1;
		}
	}

	E remove(E element) {
		E temp = NULL;
		int foundIndex = -1;
		if (size > 0) {
			for (int i = 0; i < size; i++)
			{
				if (elementBuffer[i] == element) {
					foundIndex = i;
					temp = elementBuffer[i];
					break;
				}
			}
			if (foundIndex >= 0) {
				for (int i = foundIndex; i < size; i++)
				{
					elementBuffer[i] = elementBuffer[i + 1];
				}
				elementBuffer[size] = NULL;
				size--;
				return temp;
			}
			else
			{
				return NULL;
			}
		}
		else {
			return NULL;
		}
	}

	E set(int index, E element) {
		if (size >= index) {
			elementBuffer[index] = element;
			return elementBuffer[index];
		}
		else {
			return NULL;
		}
	}

	int getSize() {
		return this->size;
	}

	E* toArray() {
		return this->elementBuffer;
	}

	void print() {
		if (size > 0) {
			for (int i = 0; i < size; i++)
			{
				std::cout << (int)this->elementBuffer[i] << std::endl;
			}
		}
		else {
			std::cout << "Empty ArrayList!" << std::endl;
		}
	}
};


/*
Test Code 

ArrayList<int> list(10);
	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("Is Empty: " + std::to_string(list.isEmpty()));
	list.print();
	logger.Log("Add: " + std::to_string(list.add(12)));
	logger.Log("Add: " + std::to_string(list.add(13)));
	logger.Log("Add: " + std::to_string(list.add(14)));
	logger.Log("Add: " + std::to_string(list.add(15)));
	logger.Log("Get: 3 index " + std::to_string(list.get(3)));
	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("Is Empty: " + std::to_string(list.isEmpty()));
	list.print();
	logger.Log("Add: " + std::to_string(list.add(16)));
	logger.Log("Add: " + std::to_string(list.add(17)));
	logger.Log("Add: " + std::to_string(list.add(18)));
	logger.Log("Add: " + std::to_string(list.add(19)));
	logger.Log("Add: " + std::to_string(list.add(20)));
	logger.Log("Add: " + std::to_string(list.add(21)));
	logger.Log("Add: " + std::to_string(list.add(22)));
	logger.Log("Add: " + std::to_string(list.add(23)));
	logger.Log("List Size: " + std::to_string(list.getSize()));
	list.print();

	logger.Log("Get: 7 index " + std::to_string(list.get(7)));
	logger.Log("Add: " + std::to_string(list.add(116)));
	logger.Log("Add: " + std::to_string(list.add(117)));
	logger.Log("Add: " + std::to_string(list.add(118)));
	logger.Log("Add: " + std::to_string(list.add(119)));
	logger.Log("Add: " + std::to_string(list.add(120)));
	logger.Log("Add: " + std::to_string(list.add(121)));
	logger.Log("Add: " + std::to_string(list.add(122)));
	logger.Log("Add: " + std::to_string(list.add(123)));
	logger.Log("List Size: " + std::to_string(list.getSize()));

	list.print();
	logger.Log("Get: 12 index " + std::to_string(list.get(12)));
	logger.Log("Add: " + std::to_string(list.add(216)));
	logger.Log("Add: " + std::to_string(list.add(217)));
	logger.Log("Add: " + std::to_string(list.add(218)));
	logger.Log("Add: " + std::to_string(list.add(219)));
	logger.Log("Add: " + std::to_string(list.add(220)));
	logger.Log("Add: " + std::to_string(list.add(221)));
	logger.Log("Add: " + std::to_string(list.add(222)));
	logger.Log("Add: " + std::to_string(list.add(223)));
	logger.Log("List Size: " + std::to_string(list.getSize()));
	list.print();

	logger.Log("Is Empty: " + std::to_string(list.isEmpty()));
	list.clear();

	logger.Log("Is Empty: " + std::to_string(list.isEmpty()));
	logger.Log("Add: " + std::to_string(list.add(216)));
	logger.Log("Add: " + std::to_string(list.add(222)));
	logger.Log("Add: " + std::to_string(list.add(217)));
	logger.Log("Add: " + std::to_string(list.add(218)));
	logger.Log("Add: " + std::to_string(list.add(219)));
	logger.Log("Add: " + std::to_string(list.add(222)));
	logger.Log("Add: " + std::to_string(list.add(220)));
	logger.Log("Add: " + std::to_string(list.add(221)));
	logger.Log("Add: " + std::to_string(list.add(222)));
	logger.Log("Add: " + std::to_string(list.add(223)));
	logger.Log("List Size: " + std::to_string(list.getSize()));

	logger.Log("Is Empty: " + std::to_string(list.isEmpty()));
	list.print();

	logger.Log("Get: 0 index " + std::to_string(list.get(0)));
	logger.Log("Get: 3 index " + std::to_string(list.get(3)));
	logger.Log("Get: 5 index " + std::to_string(list.get(5)));
	logger.Log("Get: 7 index " + std::to_string(list.get(7)));
	logger.Log("Get: 8 index " + std::to_string(list.get(8)));
	logger.Log("contins: 221 index " + std::to_string(list.contains(221)));
	logger.Log("contins: 2221 index " + std::to_string(list.contains(2221)));
	logger.Log("indexof: 221 index " + std::to_string(list.indexOf(221)));
	logger.Log("indexof: 2221 index " + std::to_string(list.indexOf(2221)));
	logger.Log("lastindexof: 222 index " + std::to_string(list.lastIndexOf(222)));
	logger.Log("lastindexof: 2221 index " + std::to_string(list.lastIndexOf(2221)));
	logger.Log("set: lastindexof 222 to 987 " + std::to_string(list.set(list.lastIndexOf(222), 987)));

	list.print();
	logger.Log("lastindexof: 222 index " + std::to_string(list.lastIndexOf(222)));
	logger.Log("lastindexof: 2221 index " + std::to_string(list.lastIndexOf(2221)));
	logger.Log("set: lastindexof 222 to 9857 " + std::to_string(list.set(list.lastIndexOf(222), 9857)));

	list.print();
	logger.Log("lastindexof: 222 index " + std::to_string(list.lastIndexOf(222)));
	logger.Log("lastindexof: 2221 index " + std::to_string(list.lastIndexOf(2221)));
	logger.Log("set: lastindexof 222 to 97 " + std::to_string(list.set(list.lastIndexOf(222), 97)));

	list.print();
	logger.Log("lastindexof: 222 index " + std::to_string(list.lastIndexOf(222)));
	logger.Log("lastindexof: 2221 index " + std::to_string(list.lastIndexOf(2221)));
	logger.Log("set: lastindexof 222 to 917 + 20 " + std::to_string(list.set(list.lastIndexOf(222) + 20, 917)));

	list.print();
	logger.Log("lastindexof: 222 index " + std::to_string(list.lastIndexOf(222)));
	logger.Log("lastindexof: 2221 index " + std::to_string(list.lastIndexOf(2221)));

	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("removeing : 219  " + std::to_string(list.remove(219)));
	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("removeing : 216  " + std::to_string(list.remove(216)));
	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("removeing : 220  " + std::to_string(list.remove(220)));
	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("removeing : 2200  " + std::to_string(list.remove(2200)));
	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	list.print();
	logger.Log("Add: " + std::to_string(list.add(1265)));

	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
	logger.Log("Add: " + std::to_string(list.add(4, 23230)));

	list.print();

	logger.Log("List Size: " + std::to_string(list.getSize()));
		for (int i = 0; i < 1000; i++)
	{
		list.add(i);
	}
	logger.Log("array Size");
	logger.Log(list.getSize());
	list.print();
	for (int i = 245; i < 953; i++)
	{
		list.remove(i);
	}
	logger.Log("array Size");
	logger.Log(list.getSize());
	list.print();

	int newarray[1000];
	for (int i = 0; i < 1000; i++)
	{
		newarray[i] = i * 250;
	}
	logger.Log("array add all");
	logger.Log(list.addAll(0, newarray, 1001));
	logger.Log("array Size");
	logger.Log(list.getSize());
	list.print();
	for (int i = 245; i < 9530; i++)
	{
		list.remove(i);
	}
	logger.Log("array Size");
	logger.Log(list.getSize());
	list.print();
*/