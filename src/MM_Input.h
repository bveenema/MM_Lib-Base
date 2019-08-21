#ifndef MM_INPUT_H
#define MM_INPUT_H

#include "MM_Object_Base.h"
#include "MM_Util.h"

template<typename T>
class MM_Input : public MM_Object_Base<T>
{
	public:
		MM_Input(const char* _name, const T& _value)
		: MM_Object_Base<T> (_name, _value)
		{
		}

		MM_Input(const char* _name)
		: MM_Object_Base<T> (_name)
		{
		}

		char unit[16] = "";

		void sConfig(char * buffer)
		{
			// Create JSON Object
			// Add name, type and current value
			char buf[16];
			ToString(buf, this->val);
			sprintf(buffer, "{\"n\":\"%s\",\"t\":\"input\",\"r\":%s", this->name, buf);
			
			// Add low value
			if(min.defined)
			{
				char tempBuffer[16];
				ToString(tempBuffer, min.value);
				sprintf(buffer + strlen(buffer), ",\"l\":%s", tempBuffer);
			}

			// Add high value
			if(max.defined)
			{
				char tempBuffer[16];
				ToString(tempBuffer, max.value);
				sprintf(buffer + strlen(buffer), ",\"h\":%s", tempBuffer);
			}

			// Add default value
			if(def.defined)
			{
				char tempBuffer[16];
				ToString(tempBuffer, def.value);
				sprintf(buffer + strlen(buffer), ",\"d\":%s", tempBuffer);
			}

			// Add unit
			sprintf(buffer + strlen(buffer), ",\"i\":\"%s\"", unit);
		}

		// min, max and default paramaters
		MM_Object_Parameter<T> min, max, def;

		// Overload functions included from MM_Util.h
		MM_OVERLOADS
};

#endif