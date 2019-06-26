#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "MM_Manager.h"

extern MM_Manager Manager;

template<typename T>
class MM_Object_Base
{
	public:
		MM_Object_Base(const T& value)
		: _value(value)
		{}
		
		operator const T& () const { return value; } // Return value when object name is used

		// write to value when assigning to instance
		const T& operator = (const T& value)
		{
			_value = value;
			return _value;
		}

	private:
		T _value; // RAM value of the  Object
};

#endif