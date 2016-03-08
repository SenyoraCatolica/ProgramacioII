#ifndef __p2String_H__
#define __p2String_H__

//#include <stdlib.h>
//#include <stdarg.h>
#include <string.h>
#include "p2Defs.h"

class p2String
{
public:

	// Constructors
	p2String()
	{
		Alloc(1);
		clear();
	}

	p2String(uint max_capacity)
	{
		Alloc(MAX(1,max_capacity));
		clear();
	}

	p2String(const p2String& string)
	{
		Alloc(string.length() + 1);
		strcpy_s(str, max_capacity, string.str);
	}

	p2String(const char *string)
	{
		if(string != nullptr)
		{
			Alloc(strlen(string) + 1);
			strcpy_s(str, max_capacity, string);
		}
		else
		{
			Alloc(1);
			clear();
		}
	}
	
	// Destructor
	virtual ~p2String()
	{
		RELEASE_ARRAY(str);
	}

	// Operators
	bool operator== (const p2String& string) const
	{
		return strcmp(string.str, str) == 0;
	}

	bool operator== (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) == 0;
		return false;
	}

	bool operator!= (const p2String& string) const
	{
		return strcmp(string.str, str) != 0;
	}

	bool operator!= (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) != 0;
		return true;
	}
	
	const p2String& operator= (const p2String& string)
	{
		if(string.length() + 1 > this->max_capacity)
		{
			RELEASE_ARRAY(str);
			Alloc(string.length() + 1);
		}

		strcpy_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator= (const char* string)
	{
		if(string != nullptr)
		{
			if(strlen(string) + 1 > max_capacity)
			{
				RELEASE_ARRAY(str);
				Alloc(strlen(string)+1);
			}

			strcpy_s(str, max_capacity, string);
		}
		else
			clear();

		return(*this);
	}
	
	const p2String& operator+= (const p2String& string)
	{
		unsigned int need_max_capacity = string.length() + length() + 1;

		if(need_max_capacity > max_capacity)
		{
			char* tmp = str;
			Alloc(need_max_capacity);
			strcpy_s(str, max_capacity, tmp);
			RELEASE_ARRAY(tmp);
		}

		strcat_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator+= (const char* string)
	{
		if(string != nullptr)
		{
			unsigned int need_max_capacity = strlen(string) + length() + 1;

			if(need_max_capacity > max_capacity)
			{
				char* tmp = str;
				Alloc(need_max_capacity);
				strcpy_s(str, max_capacity, tmp);
				RELEASE_ARRAY(tmp);
			}

			strcat_s(str, max_capacity, string);
		}

		return(*this);
	}

	p2String& Prefix(p2String& second_string)
	{
		char tmp[4096];

		strcpy_s(tmp, 4096, second_string.str);
		strcat_s(tmp, 4096, str);

		unsigned int need_size = strlen(tmp) + 1;

		if (need_size > size())
		{
			delete[] str;
			Alloc(need_size);
		}

		strcpy_s(str, size(), tmp);
		return(*this);
	}

	p2String& Cut(unsigned int start, unsigned int end)
	{
		if (start < size())
		{
			if (start < end)
			{
				char tmp[4096];
				unsigned int x = start;

				for (unsigned int i = 0; i < start; i++)
				{
					tmp[i] = str[i];
				}

				for (unsigned int i = end; i < size(); i++)
				{
					tmp[x] = str[i];
					x++;
				}

				strcpy_s(str, 4096, tmp);

			}
		}

		return *(this);
	}

	bool CheckForNumbers()
	{
		for (uint i = 0; i < size(); i++)
		{
			if (str[i] == 0 || str[i] == 1 || str[i] == 2 || str[i] == 3 || str[i] == 4 || str[i] == 5 || str[i] == 6 || str[i] == 7 || str[i] == 8 || str[i] == 9)
				return true;
		}
		return false;
	}

	// Utils
	uint length() const
	{
		return strlen(str);
	}

	uint size() const
	{
		return strlen(str);
	}

	bool empty() const
	{
		return strlen(str) == 0;
	}

	void clear()
	{
		str[0] = '\0';
	}

	char* c_str() const
	{
		return str;
	}

	uint capacity() const
	{
		return max_capacity;
	}

	int SearchForChar(char find)
	{
		uint ret = 0;
		for (uint i = 0; i < length(); i++)
		{
			if (str[i] == find)
				ret++;
		}

		return ret;
	}

	int SearchForString(const char* find)const
	{
		uint ret = 0;
		uint len = strlen(find);

		for (uint i = 0; i < max_capacity; i++)
			if (str[i] == find[0])
				if (strncmp(find, &str[i], len) == 0)
					ret++;
		return ret;
	}

	void Trim()
	{
		//cut right --
		char* end = str + size();
		while (*--end == ' ')
			*end = '\0';

		//cut left --
		char* start = str;
		while (*++start == ' ');

		uint s = strlen(start);
		for (uint i = 0; i < s; i++)
			str[i] = start[i];
	}


/*	uint DoubleVocals()
	{
		uint ret = 0;

		for (uint i = 0; i < size(); i++)
		{
			if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			{


				for (uint j = size(); j > i; j--)
				{
					str[j + 1] = str[j];
				}

				str[i + 1] = str[i];
				i++;
				ret++;
			}
		}

		str[size()] = '\0';
		return ret;
	}*/


private:

	void Alloc(unsigned int required_memory)
	{
		max_capacity = required_memory;
		str = new char[max_capacity];
	}

private:

	char* str;
	uint max_capacity;

};

#endif // __p2String_H__