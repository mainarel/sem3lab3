#pragma once
#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T >
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T>* items;
	int count;
public:
	ListSequence()
	{
		this->items = new LinkedList<T>();
	}
	ListSequence(LinkedList<T>* items, int count)
	{
		this->count = count;
		this->items = new LinkedList<T>();
		for (size_t i = 0; i < count; i++)
		{
			this->Prepend(items->Get(i));
		}
	};
	ListSequence(const ListSequence<T>& other)
	{
		this->count = other.count;
		this->items = new LinkedList<T>(other.GetLength());
		for (size_t i = 0; i < other.GetLength(); i++)
		{
			this->Prepend(other.Get(i));
		}

	};
public:
	virtual int GetLength() const override
	{
		return this->items->Getsize();
	}
	virtual T GetFirst() const override
	{
		return this->items->GetFirst();
	}
	virtual T GetLast() const override
	{
		return this->items->GetLast();
	}
	virtual T Get(const int index) const override
	{
		if (index < 0 || index >= this->count)
			throw std::out_of_range("undefined index");
		return this->items->Get(index);
	}

	virtual int GetIndex(const T value) const override
	{
		return this->items->GetIndex(value);
	}
public:


	virtual void Set(int index, T value) override {
		this->items->Set(index, value);
	}
	virtual void Append(T const value)  override
	{
		this->items->Apend(value);
		this->count++;
	}
	virtual void Prepend(T const value)  override
	{
		this->items->Prepend(value);
		this->count++;
	}
	virtual void InsertAt(const int index, T const value)  override
	{
		this->items->InsertAt(index, value);
		this->count++;
	}
	virtual bool Has(T value) {
		int size = this->GetLength();
		for (int i = 0; i < size; i++) { 
			if (value == this->Get(i))
				return false;
			else
				return true;
			}
		
	}

	virtual void Remove(T value)  override
	{
		int size = this->GetLength();
		for (int i = 0; i < size; i++)
		{
			if (this->items->Get(i) == value)
			{
				this->items->Remove(i);
				break;
			}
		}
		this->count--;
	}
	virtual void RemoveAt(const int index)  override
	{
		if (index < 0 || index >= this->count)
			throw std::out_of_range("undefined index");
		this->items->Remove(index);
		this->count--;
	}
	virtual void RemoveAll(T value)  override
	{
		int size = this->GetLength();
		int j = 0;
		while (j < this->count)
		{
			if (this->items->Get(j) == value)
			{
				RemoveAt(j);
				j--;
			}
			j++;
		}
	}

	virtual Sequence<T>* GetSubsequence(const int begin, const int end)  const override
	{
		if (begin >= this->count || end >= this->count)
			throw std::out_of_range("undefined index ");
		ListSequence<T>* itemsSub;
		itemsSub = new ListSequence<T>();

		itemsSub->items = this->items->GetSubList(begin, end);
		itemsSub->count = itemsSub->GetLength();
		return itemsSub;
	}
	virtual Sequence<T>* Concatination(Sequence<T>* other)  override
	{
		int thissize = this->GetLength();
		int othersize = other->GetLength();
		ListSequence<T>* itemsconcat;
		itemsconcat = new ListSequence<T>();
		T* arrtemp;
		arrtemp = new T[thissize + othersize];
		for (size_t i = 0; i < this->GetLength(); i++)
		{
			arrtemp[i] = this->Get(i);
		}
		for (size_t i = 0; i < other->GetLength(); i++)
		{
			arrtemp[thissize + i] = other->Get(i);
		}
		for (size_t i = 0; i < thissize + othersize; i++)
		{
			itemsconcat->Prepend(arrtemp[i]);
		}

		return itemsconcat;
	}
	virtual Sequence<T>* Copy()  override
	{
		ListSequence<T>* itemstemp;
		itemstemp = new ListSequence<T>();
		for (int i = 0; i < this->count; i++)
		{
			itemstemp->items->Prepend(this->Get(i));
		}

		return itemstemp;
	}
	virtual Sequence<T>* CopyTo(Sequence<T>* target, int beginIndex)  override
	{
		if (beginIndex < 0)
			throw std::out_of_range("undefined index");
		ListSequence<T>* itemstemp;
		itemstemp = new ListSequence<T>();
		for (int i = beginIndex; i < target->GetLength(); i++)
		{
			itemstemp->items->Prepend(target->Get(i));
		}

		return itemstemp;
	}
	~ListSequence()
	{
		while (this->count)
		{
			this->items->PopFront();
		}
	}
};