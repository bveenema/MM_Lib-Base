#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "MM_Manager.h"
extern MM_Manager Manager;

template<typename T>
class MM_Object_Base
{
	public:
		MM_Object_Base(const char* name, const T& value)
		: _value(value)
		, _name(name)
		{}
		
		// Conversion Operator
		// Second const is a promise to not modify MM_Object_Base
		// \return [const T&], returns const ref to _value to prevent caller from modifying
		operator const T& () const { return _value; }

		// Assignment Operator
		// \param [T&] value, the new value to assign to base
		// \return [const T&], returns const ref to value instead of copy
		const T& operator = (const T& value)
		{
			_value = value;
			return _value;
		}

	private:
		T _value; // RAM value of the  Object
		const char* _name; // the name of the object as will appear in MM app
};

#endif