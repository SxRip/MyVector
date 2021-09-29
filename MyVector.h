#pragma once
#include <iostream>

#pragma warning (disable : 4018, 6386)

using namespace std;

template<typename _Ty>
class vector
{
public:
	class vector_iterator;
	vector()
	{
		m_pArr = nullptr;
		m_iSIZE = 0;
	}

	vector(const int _Val, const _Ty _FillVal)
	{
		m_pArr = new _Ty[_Val];

		for (size_t i = 0; i < _Val; i++)
		{
			m_pArr[i] = _FillVal;
		}

		m_iSIZE = _Val;
	}

	~vector()
	{
		if (m_pArr != nullptr)
		{
			delete[] m_pArr;
		}
	}

	void push_back(_Ty&& _Val)
	{
		if (!m_iSIZE)
		{
			m_pArr = new _Ty[++m_iSIZE];

			m_pArr[0] = _Val;
		}
		else
		{
			_Ty* tArr = new _Ty[++m_iSIZE];

			for (size_t i = 0; i < m_iSIZE - 1; i++)
			{
				tArr[i] = m_pArr[i];
			}

			tArr[m_iSIZE - 1] = _Val;

			delete[] m_pArr;

			m_pArr = tArr;
		}
	}
	void pop_back()
	{
		if (m_iSIZE)
		{
			_Ty* tArr = new _Ty[--m_iSIZE];

			for (size_t i = 0; i < m_iSIZE; i++)
			{
				tArr[i] = m_pArr[i];
			}

			delete[] m_pArr;

			m_pArr = tArr;
		}
	}

	void resize(const int _Val)
	{
		if (m_iSIZE)
		{
			_Ty* tArr = new _Ty[_Val];

			for (size_t i = 0; i < m_iSIZE; i++)
			{
				tArr[i] = m_pArr[i];
			}

			m_iSIZE = _Val;

			delete[] m_pArr;

			m_pArr = tArr;
		}
		else
		{
			m_pArr = new _Ty[_Val];
			m_iSIZE = _Val;
		}
	}
	void resize(const int _Val, const _Ty&& _FillVal, bool _Save)
	{
		if (m_iSIZE)
		{
			_Ty* tArr = new _Ty[_Val];

			if (_Save)
			{
				size_t i = 0;

				for (; i < m_iSIZE; i++)
				{
					tArr[i] = m_pArr[i];
				}

				for (; i < _Val; i++)
				{
					tArr[i] = _FillVal;
				}
			}
			else
			{
				for (size_t i = 0; i < _Val; i++)
				{
					tArr[i] = _FillVal;
				}
			}

			delete[] m_pArr;

			m_pArr = tArr;

			m_iSIZE = _Val;
		}
		else
		{
			m_pArr = new _Ty[_Val];

			for (size_t i = 0; i < _Val; i++)
			{
				m_pArr[i] = _FillVal;
			}
			m_iSIZE = _Val;
		}
	}
	void insert(int&& _Indx, _Ty&& _Val)
	{
		if (!m_iSIZE)
		{
			m_pArr = new _Ty[++m_iSIZE];

			m_pArr[0] = _Val;
		}
		else
		{
			int it = 0;
			_Ty* tArr = new _Ty[++m_iSIZE];
			_Ty tmp = _Ty();

			for (size_t i = 0; i < m_iSIZE; i++)
			{
				if ((tArr + i) == (tArr + _Indx))
				{
					tmp = m_pArr[i];
					tArr[i] = _Val;
					tArr[i + 1] = tmp;
					i++; it++;
				}
				else
				{
					tArr[i] = m_pArr[it];
					it++;
				}
			}

			delete[] m_pArr;

			m_pArr = tArr;
		}
	}
	void erase(int&& _Indx)
	{
		if (m_iSIZE)
		{
			_Ty* tArr = new _Ty[--m_iSIZE];

			int it = 0;

			for (size_t i = 0; i < m_iSIZE + 1; i++, it++)
			{
				if ((tArr + i) != (tArr + _Indx))
				{
					tArr[it] = m_pArr[i];
				}
				else
				{
					it--;
				}
			}

			delete[] m_pArr;

			m_pArr = tArr;
		}
	}
	void clear()
	{
		while (m_iSIZE != 0)
		{
			pop_back();
		}
	}

	int size() const { return m_iSIZE; }

	_Ty& back() const { return m_pArr[m_iSIZE - 1]; }

	_Ty& at(const int _Pos) const
	{
		if (_Pos > m_iSIZE - 1)
			_THROW(exception("out of range"));
		else
			return m_pArr[_Pos];
	}

	vector_iterator begin() const { return m_pArr; }
	vector_iterator end() const { return m_pArr + m_iSIZE; }

	_Ty& operator[](const int _Pos) const { return m_pArr[_Pos]; }

	bool operator==(const vector<_Ty>& vec) const
	{
		if (this->m_iSIZE != vec.size())
		{
			return false;
		}
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (this->m_pArr[i] != vec[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const vector<_Ty>& vec) const { return !(*this == vec); }
private:
	class vector_iterator
	{
	public:
		vector_iterator(_Ty* TmpIt)
		{
			m_pIt = TmpIt;
		}
		_Ty& operator+(int _Val) { return *(m_pIt + _Val); }
		_Ty& operator-(int _Val) { return *(m_pIt - _Val); }

		_Ty& operator++(int) { return *m_pIt++; }
		_Ty& operator--(int) { return *m_pIt--; }

		_Ty& operator++() { return *m_pIt++; }
		_Ty& operator--() { return *m_pIt--; }

		bool operator==(const vector_iterator& tmpIt) const { return tmpIt.m_pIt == m_pIt; }
		bool operator!=(const vector_iterator& tmpIt) const { return tmpIt.m_pIt != m_pIt; }

		_Ty& operator*() const { return *m_pIt; }
	private:
		_Ty* m_pIt;
	};

	_Ty* m_pArr;
	int m_iSIZE;
};
//MY VECTOR 07.09.21
