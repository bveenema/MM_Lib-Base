#ifndef MM_MANAGER_H
#define MM_MANAGER_H

#include "MM_Config.h"
#include "MM_Object_Base.h"

#include <stdio.h>

class ObjectInterface;

class MM_Manager
{
	public:
		MM_Manager(const size_t numObjects)
		{
			CommandMap.objects = new ObjectInterface*[numObjects];
			CommandMap.max_size = numObjects;
		}

		// Add
		// Adds a new Object to the CommandMap. Returns false if new element cannot be added
		// \param [void*] Object - Pointer to the new Object
		// \return [bool] - false if out of bounds, true if added
		bool Add(ObjectInterface* Object)
		{
			// Out of bounds check
			if(CommandMap.size >= CommandMap.max_size) return false;

			// Add the object to the next position in the CommandMap
			CommandMap.objects[CommandMap.size] = Object;
			CommandMap.size += 1;
			return true;
		}

		void test()
		{
			char buffer[100];
			sprintf(buffer, "CommandMap:\n"
							"\tsize: %d\n"
							"\tmax size: %d\n"
							"Elements:\n"
							"\t\tvalue: %s", CommandMap.size, CommandMap.max_size, CommandMap.objects[0]->StringValue());
			MM_Serial_Print(buffer);
		}

	private:
		struct {
			ObjectInterface** objects = nullptr;
			unsigned size = 0;
			unsigned max_size = 0;
		} CommandMap;

};

#endif
