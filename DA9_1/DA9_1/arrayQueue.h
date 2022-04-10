#pragma once
#include <iostream>
#include "queue.h"
#include "myExceptions.h"

//using std::cout;

template <class T>
class arrayQueue :
	public queue<T>
{
protected:
	T* queue;
	int arrayLength;
	int theBack;
	int theFront;

public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
	bool empty()const { return theBack == theFront; }
	int size()const { return (theBack - theFront + arrayLength) % arrayLength; }
	T& back() { if (theBack == theFront) throw queueEmpty(); return queue[theBack]; }
	T& front() { if (theBack == theFront) throw queueEmpty(); return queue[(theFront + 1) % arrayLength]; }
	void pop();
	void push(const T& theElement);
};

template<class T>
inline arrayQueue<T>::arrayQueue(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be > 0");
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template<class T>
inline void arrayQueue<T>::pop()
{
	if (theBack == theFront)
		throw queueEmpty();
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();
}

template<class T>
inline void arrayQueue<T>::push(const T & theElement)
{
	if ((theBack + 1) % arrayLength == theFront)
	{
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;//startָ���һ��Ԫ��λ�ã������ǵ�һ��Ԫ��ǰһλ
		if (start < 2)
			copy(queue + start, queue + start + arrayLength - 1, newQueue);//-1��Ϊ�˱���start��1ʱ���µ�����Խ��,start=0ʱ������ٸ��ƶ����еĿ�λ
		else
		{
			copy(queue + start, queue + arrayLength, newQueue);
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);//+1����Ϊcopy������β������ҿ�
		}
		/*copy(queue + start, queue + arrayLength, newQueue);//����д������࣬���ǿɶ��Բ�һ�㣬���Ҷิ���˿�λ��Ч���ϲ�һ���
		if (start > 1)
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);*/
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		delete[] queue;
		queue = newQueue;
	}
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}
