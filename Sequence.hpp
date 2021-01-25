#pragma once
template <class T>
class Sequence
{
public:
	virtual int GetLength() const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(const int i) const = 0;
	virtual int GetIndex(const T value) const  = 0;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const = 0;
public:
	virtual void Set(const int index, T value) = 0;
	virtual void Append(T value) = 0;
	virtual void Prepend(T value) = 0;
	virtual void InsertAt(const int index, T value) = 0;
	virtual void RemoveAt(const int index) = 0;
	virtual void Remove(T value) = 0;
	virtual void RemoveAll(T value) = 0;
	virtual bool Has(T value) = 0;
	
	virtual Sequence<T>* Concatination(Sequence<T>* other) = 0;
	virtual Sequence<T>* Copy() = 0;
	virtual Sequence<T>* CopyTo(Sequence<T>* target, int startIndex) = 0;
public:
	virtual ~Sequence() {}
};