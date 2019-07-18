#ifndef MM_INPUT_H
#define MM_INPUT_H

#include "MM_Object_Base.h"

template<typename T>
class MM_Input : public MM_Object_Base<T>
{
	public:
		MM_Input(const char* _name, const T& _value);
		MM_Input(const char* _name);

		// min, max and default paramaters
		struct 
		{
			T value;
			bool defined = false;

			const T& operator = (const T& _value) { value = _value; }
			operator const T& () const { return value; }
		} min, max, def;

	private:
		char unit[16] = "";
};

#endif