#ifndef MM_INPUT_H
#define MM_INPUT_H

#include "MM_Object_Base.h"
#include "MM_Util.h"

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

		// Overload functions included from MM_Util.h
		MM_OVERLOADS

	private:
		char unit[16] = "";
};

#endif