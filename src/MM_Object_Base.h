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

		MM_Object_Base(const MM_Manager& _Manager, const char* _name, const T& _value)
		: Manager(_Manager)
		, name(_name)
		, value(_value)
		{
			Manager.Add(this);
		}

		// Value (Getter)
		// Getter for value. Can be used instead of Conversion operator
		// \return [const T&] value - a const reference to the specified value
		const T& value(){ return value; }

		// Value (Setter)
		// Setter for value. Can be used instead of Assignment operator
		// \param [const T&] _value - a const reference to the new value
		// \return [const T&] value - a const reference to the updated value
		const T& value(const T& _value)
		{
			value = _value;
			return value;
		}
		
		// Conversion Operator
		// Second const is a promise to not modify MM_Object_Base
		// \return [const T&], returns const ref to value to prevent caller from modifying
		operator const T& () const { return value; }

		// Assignment Operator
		// \param [T&] value, the new value to assign to base
		// \return [const T&], returns const ref to value instead of copy
		const T& operator = (const T& _value)
		{
			value = _value;
			return value;
		}

	private:
		T value; // RAM value of the  Object
		MM_Manager& Manager;
};

#endif