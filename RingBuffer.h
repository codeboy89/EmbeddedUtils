#pragma once
#include <iostream>
/*
Example 
RingBuffer<double>* rb = new RingBuffer<double>(10, true);
RingBuffer<double> rb(10, true);
*/

template <typename T>
class RingBuffer
{
private:
	T* objectBuffer = nullptr;
	T currentObject = NULL;
	bool overwriteMode = false;
	int bufferCapacity = 0;
	int remainingCapacity = 0;
	int bufferSize = 0;
	int headPos = 0;
	int tailPos = 0;

	RingBuffer() {
		this->bufferCapacity = 10;
		this->remainingCapacity = 10;
		this->overwriteMode = false;
		this->objectBuffer = new T[10];
	}

public:
	// Constructor
	RingBuffer(int capacity, bool overwriteMode) {
		this->bufferCapacity = capacity;
		this->remainingCapacity = capacity;
		this->overwriteMode = overwriteMode;
		this->objectBuffer = new T[capacity];
	}

	// General Methods
	bool reset() {
		this->remainingCapacity = this->bufferCapacity;
		this->bufferSize = 0;
		this->headPos = 0;
		this->tailPos = 0;
		for (int i = 0; i < this->bufferCapacity; i++)
		{
			this->objectBuffer[i] = NULL;
		}

		return false;
	}

	bool put(T object) {



		// is space avalible
		if (!this->overwriteMode && this->remainingCapacity < 1) {
			//std::cout << " Cannot Add " << object << std::endl;
			return false;
		}
		else {
			int nextPosition;
			// Check if at the end
			if (headPos + 1 != this->bufferCapacity) {
				nextPosition = headPos + 1;
				//std::cout << " Head not at end " << headPos << std::endl;
			}
			else {
				nextPosition = 0;
				//std::cout << " Head at end " << headPos << std::endl;
			}
			//std::cout << "Added " << object << std::endl;
			// insert new object
			this->objectBuffer[headPos] = object;
			// advance head pointer
			this->headPos = nextPosition;

			if (overwriteMode && this->remainingCapacity < 1) {

				int nextTailPosition;
				// Check if at the end
				if (tailPos + 1 != this->bufferCapacity) {
					nextTailPosition = tailPos + 1;
					//std::cout << " Tail not at end " << tailPos << std::endl;
				}
				else {
					nextTailPosition = 0;
					//std::cout << " Tail not at end " << tailPos << std::endl;
				}

				tailPos = nextTailPosition;
			}
			else {
				this->bufferSize++;
				this->remainingCapacity--;
			}
			return true;

		}
	}

	T take() {
		// if the head == tail, no data availible
		if (this->bufferSize < 1) {
			//std::cout << "head == tail, no data availible Head: " << headPos << " Tail: " << tailPos << std::endl;
			return NULL;
		}

		else {

			int nextPosition;
			// Check if at the end
			if (tailPos + 1 != this->bufferCapacity) {
				nextPosition = tailPos + 1;
				//std::cout << " Tail not at end " << tailPos << std::endl;
			}
			else {
				nextPosition = 0;
				//std::cout << " Tail not at end " << tailPos << std::endl;
			}

			this->currentObject = this->objectBuffer[this->tailPos];
			this->objectBuffer[this->tailPos] = NULL;
			this->tailPos = nextPosition;
			this->bufferSize--;
			this->remainingCapacity++;
			return this->currentObject;
		}
	}
	// Setters
	bool setOverwriteMode(bool overwriteMode) {
		this->overwriteMode = overwriteMode;
		return this->overwriteMode;
	}

	// Getters
	bool isSpaceAvailible() {
		if (this->headPos == this->tailPos) {
			return false;
		}
		else
		{
			return true;
		}
	}

	bool isOverwriteMode() {
		return this->overwriteMode;
	}

	int getRemainingCapacity() {

		return this->remainingCapacity;
	}

	int getBufferCapacity() {
		return this->bufferCapacity;
	}

	int getBufferSize() {
		return this->bufferSize;
	}

	int getHeadPosition() {
		return this->headPos;
	}

	int getTailPosition() {
		return this->tailPos;
	}

	void printBuffer() {
		for (int i = 0; i < this->bufferCapacity; i++)
		{
			std::cout << "Item " << i << ": " << &this->objectBuffer[i] << std::endl;
		}
	}
};




// Test Code
/*

	MessageFrame* mf1 = new MessageFrame(45);
	MessageFrame* mf2 = new MessageFrame(35);
	MessageFrame* mf3 = new MessageFrame(85);
	MessageFrame* mf4 = new MessageFrame(12);
	MessageFrame* mf5 = new MessageFrame(23);
	MessageFrame* mf6 = new MessageFrame(54);
	MessageFrame* mf7 = new MessageFrame(65);
	RingBuffer<MessageFrame*>* rb = new RingBuffer<MessageFrame*>(10, true);
	Logger logger(true, false);

	rb->printBuffer();
	logger.Log(rb->put(mf1));
	logger.Log(rb->put(mf1));
	logger.Log(rb->put(mf1));
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	delete mf1;
	logger.Log((int) rb->take()->getSourceAddress());
	logger.Log(rb->put(mf2));
	logger.Log(rb->put(mf3));
	logger.Log(rb->put(mf4));
	logger.Log(rb->put(mf5));
	logger.Log(rb->put(mf6));
	logger.Log(rb->put(mf7));
	logger.Log(rb->put(mf7));
	logger.Log(rb->put(mf6));
	logger.Log(rb->put(mf5));
	logger.Log(rb->put(mf4));
	logger.Log(rb->put(mf3));
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());
	logger.Log((int)rb->take()->getSourceAddress());

logger.Log("RB Cap");
	logger.Log(rb.getBufferCapacity());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	rb.printBuffer();
	logger.Log("RB Reset");
	rb.reset();
	rb.printBuffer();
	logger.Log("RB Added 1");
	logger.Log(rb.put(1));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 2");
	logger.Log(rb.put(2));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 3");
	logger.Log(rb.put(3));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 4");
	logger.Log(rb.put(4));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 5");
	logger.Log(rb.put(5));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 6");
	logger.Log(rb.put(6));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 7");
	logger.Log(rb.put(7));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 8");
	logger.Log(rb.put(8));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 9");
	logger.Log(rb.put(9));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 10");
	logger.Log(rb.put(10));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 11");
	logger.Log(rb.put(11));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	rb.printBuffer();
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 12");
	logger.Log(rb.put(12));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 13");
	logger.Log(rb.put(13));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	rb.printBuffer();
	logger.Log("\n");
	logger.Log("RB Added 14");
	logger.Log(rb.put(14));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Added 15");
	logger.Log(rb.put(15));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	rb.printBuffer();
	logger.Log("RB Reset");
	rb.reset();
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	rb.printBuffer();
	logger.Log("\n");
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Added 13");
	logger.Log(rb.put(13));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Added 14");
	logger.Log(rb.put(14));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 15");
	logger.Log(rb.put(15));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 16");
	logger.Log(rb.put(16));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 17");
	logger.Log(rb.put(17));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 18");
	logger.Log(rb.put(18));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 19");
	logger.Log(rb.put(19));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Added 20");
	logger.Log(rb.put(20));
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());

	rb.printBuffer();

	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Take");
	logger.Log(rb.take());
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	rb.printBuffer();
	logger.Log("\n");
	logger.Log("RB Added 21");
	logger.Log(rb.put(21));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 22");
	logger.Log(rb.put(22));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 23");
	logger.Log(rb.put(23));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 24");
	logger.Log(rb.put(24));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	rb.printBuffer();

	logger.Log("\n");
	logger.Log("RB Added 25");
	logger.Log(rb.put(25));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 26");
	logger.Log(rb.put(26));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("\n");
	logger.Log("RB Added 27");
	logger.Log(rb.put(27));
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());
	logger.Log("RB Remaining Cap");
	logger.Log(rb.getRemainingCapacity());
	logger.Log("RB Size");
	logger.Log(rb.getBufferSize());

	rb.printBuffer();*/