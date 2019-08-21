#ifndef MM_OBJECT_BASE_H
#define MM_OBJECT_BASE_H

#include "MM_Config.h"
#include "MM_Util.h"

class ObjectInterface
{
	public:
		virtual void sValue(char * buffer) = 0;
		virtual void sConfig(char * buffer) = 0;
		virtual void sUpdate(char * buffer) = 0;
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

		void sUpdate(char * buffer)
		{
			val = ToValue(buffer, val);
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
	protected:
		T val; // RAM value of the  Object
};

#endif