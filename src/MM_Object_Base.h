#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "MM_Config.h"

void ToString(char* buffer, int value);
void ToString(char* buffer, unsigned value);
void ToString(char* buffer, float value);
void ToString(char* buffer, double value);
void ToString(char* buffer, char* value);

class ObjectInterface
{
	public:
		virtual void sValue(char * buffer) = 0;
		// virtual bool PrintConfig() = 0;
};

template<typename T>
class MM_Object_Base : public ObjectInterface
{
	public:
		const char* name; // the name of the object as will appear in MM app

		MM_Object_Base(const char* _name, const T& _value)
		: name(_name)
		, val(_value)
		{
		}

		MM_Object_Base(const char* _name)
		: name(_name)
		{
		}

		void sValue(char * buffer)
		{
			ToString(buffer, val);
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
};

#endif