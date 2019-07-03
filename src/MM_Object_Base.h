#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "MM_Config.h"
#include "MM_Manager.h"

#include <sstream>
#include <string>

class MM_Manager;

template<class T>
std::string toString(const T &value) 
{
    std::ostringstream os;
    os << value;
    return os.str();
}

class ObjectInterface
{
	public:
		virtual const char* StringValue() = 0;
		// virtual bool PrintConfig() = 0;
};

template<typename T>
class MM_Object_Base : ObjectInterface
{
	public:
		const char* name; // the name of the object as will appear in MM app

		MM_Object_Base(MM_Manager& _Manager, const char* _name, const T& _value)
		: name(_name)
		, val(_value)
		, Manager(_Manager)
		{
			Manager.Add(this);
		}

		const char* StringValue()
		{
			return toString(val).c_str();
		}

		// Value (Getter)
		// Getter for val. Can be used instead of Conversion operator
		// \return [const T&] val - a const reference to the specified val
		const T& value(){ return val; }

		// Value (Setter)
		// Setter for val. Can be used instead of Assignment operator
		// \param [const T&] _value - a const reference to the new val
		// \return [const T&] val - a const reference to the updated val
		const T& value(const T& _value)
		{
			val = _value;
			return val;
		}
		
		// Conversion Operator
		// Second const is a promise to not modify MM_Object_Base
		// \return [const T&], returns const ref to val to prevent caller from modifying
		operator const T& () const { return val; }

		// Assignment Operator
		// \param [T&] value, the new val to assign to base
		// \return [const T&], returns const ref to val instead of copy
		const T& operator = (const T& _value)
		{
			val = _value;
			return val;
		}

	private:
		T val; // RAM value of the  Object
		MM_Manager& Manager;
};

#endif