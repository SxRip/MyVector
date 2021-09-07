#pragma once
#include <iostream>

using namespace std;

template<class _Ty>
class vector
{
public:
	class vector_iterator;
	vector()
	{
		arr = nullptr;
		SIZE = 0;
	}

	vector(const int _Val, const _Ty _FillVal)
	{
		arr = new _Ty[_Val];

		for (size_t i = 0; i < _Val; i++)
		{
			arr[i] = _FillVal;
		}

		SIZE = _Val;
	}

	~vector()
	{
		if (arr != nullptr)
		{
			delete[] arr;
		}
	}

	void push_back(_Ty&& _Val)
	{
		if (!SIZE)
		{
			arr = new _Ty[++SIZE];

			arr[0] = _Val;
		}
		else
		{
			_Ty* tArr = new _Ty[++SIZE];

			for (size_t i = 0; i < SIZE; i++)
			{
				if ((tArr + i) == (tArr + SIZE - 1))
				{
					tArr[i] = _Val;
				}
				else
				{
					tArr[i] = arr[i];
				}
			}
			delete[] arr;

			arr = tArr;
		}
	}
	void push_front(_Ty&& _Val)
	{
		if (!SIZE)
		{
			arr = new _Ty[++SIZE];

			arr[0] = _Val;
		}
		else
		{
			_Ty* tArr = new _Ty[++SIZE];
			size_t i = 1;

			for (size_t j = 0; j < SIZE - 1; i++, j++)
			{
				tArr[i] = arr[j];
			}
			tArr[0] = _Val;

			delete[] arr;

			arr = tArr;
		}
	}
	void pop_back()
	{
		if (SIZE)
		{
			_Ty* tArr = new _Ty[--SIZE];

			for (size_t i = 0; i < SIZE; i++)
			{
				tArr[i] = arr[i];
			}

			delete[] arr;

			arr = tArr;
		}
	}
	void pop_front()
	{
		if (SIZE)
		{
			_Ty* tArr = new _Ty[--SIZE];
			size_t j = 1;

			for (size_t i = 0; i < SIZE; i++)
			{
				tArr[i] = arr[j];
				j++;
			}

			delete[] arr;

			arr = tArr;
		}
	}

	void resize(const int _Val)
	{
		if (SIZE)
		{
			_Ty* tArr = new _Ty[_Val];

			for (size_t i = 0; i < SIZE; i++)
			{
				tArr[i] = arr[i];
			}

			SIZE = _Val;

			delete[] arr;

			arr = tArr;
		}
		else
		{
			_Ty* arr = new _Ty[_Val];
		}
	}
	void resize(const int _Val, const _Ty&& _FillVal, bool _Save)
	{
		if (SIZE)
		{
			_Ty* tArr = new _Ty[_Val];

			if (_Save)
			{
				size_t i = 0;

				for (; i < SIZE; i++)
				{
					tArr[i] = arr[i];
				}

				for (; i < _Val; i++)
				{
					tArr[i] = _FillVal;
				}

				delete[] arr;

				arr = tArr;
			}
			else
			{
				for (size_t i = 0; i < _Val; i++)
				{
					tArr[i] = _FillVal;
				}

				delete[] arr;

				arr = tArr;
			}

			SIZE = _Val;
		}
		else
		{
			arr = new _Ty[_Val];

			for (size_t i = 0; i < _Val; i++)
			{
				arr[i] = _FillVal;
			}
			SIZE = _Val;
		}
	}
	void insert(int&& _Indx, _Ty&& _Val)
	{
		if (!SIZE)
		{
			arr = new _Ty[++SIZE];

			arr[0] = _Val;
		}
		else
		{
			int it = 0;
			_Ty* tArr = new _Ty[++SIZE];
			_Ty tmp = _Ty();

			for (size_t i = 0; i < SIZE; i++)
			{
				if ((tArr + i) == (tArr + _Indx))
				{
					tmp = arr[i];
					tArr[i] = _Val;
					tArr[i + 1] = tmp;
					i++; it++;
				}
				else
				{
					tArr[i] = arr[it];
					it++;
				}
			}

			delete[] arr;

			arr = tArr;
		}
	}
	void erase(int&& _Indx)
	{
		if (SIZE)
		{
			_Ty* tArr = new _Ty[--SIZE];

			int it = 0;

			for (size_t i = 0; i < SIZE + 1; i++, it++)
			{
				if ((tArr + i) != (tArr + _Indx))
				{
					tArr[it] = arr[i];
				}
				else
				{
					it--;
				}
			}

			delete[] arr;

			arr = tArr;
		}
	}
	void clear()
	{
		while (SIZE != 0)
		{
			pop_back();
		}
	}

	int size() const { return SIZE; }

	_Ty& back() const { return arr[SIZE - 1]; }

	_Ty& at(const int _Pos) const
	{
		if (_Pos > SIZE - 1)
			_THROW(exception("out of range"));
		else
			return arr[_Pos];
	}

	vector_iterator begin() { return arr; }
	vector_iterator end() { return arr + SIZE; }

	_Ty& operator[](const int _Pos) { return arr[_Pos]; }
private:
	class vector_iterator
	{
	public:
		vector_iterator(_Ty* TmpIt)
		{
			it = TmpIt;
		}
		_Ty& operator+(int _Val) { return *(it + _Val); }
		_Ty& operator-(int _Val) { return *(it - _Val); }

		_Ty& operator++(int) { return *it++; }
		_Ty& operator--(int) { return *it--; }

		_Ty& operator++() { return *it++; }
		_Ty& operator--() { return *it--; }

		bool operator==(const vector_iterator& tmpIt) { return tmpIt.it == it; }
		bool operator!=(const vector_iterator& tmpIt) { return tmpIt.it != it; }

		_Ty& operator*() { return *it; }
	private:
		_Ty* it;
	};

	_Ty* arr;
	int SIZE;
};
//MY VECTOR 07.09.21
