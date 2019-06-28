#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "Particle.h"
#include "MM_Config.h"
#include "MM_Manager.h"

template<typename T>
class MM_Object_Base
{
	public:
		const char* name; // the name of the object as will appear in MM app

		MM_Object_Base(const char* _name, const T& _value)
		: name(_name)
		, value(_value)
		{
		}
		
		// Conversion Operator
		// Second const is a promise to not modify MM_Object_Base
		// \return [const T&], returns const ref to value to prevent caller from modifying
		operator const T& () const { 
			char buffer[100];
			sprintf(buffer, "Get Value: %d\n", value);
			MM_Serial_Print(buffer);
			return value; }

		// Assignment Operator
		// \param [T&] value, the new value to assign to base
		// \return [const T&], returns const ref to value instead of copy
		const T& operator = (const T& _value)
		{
			value = _value;
			char buffer[100];
			sprintf(buffer, "Update Value: %d, %d\n", value, _value);
			MM_Serial_Print(buffer);
			return value;
		}

	private:
		T value; // RAM value of the  Object
};

#endif