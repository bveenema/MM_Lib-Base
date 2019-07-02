#ifndef MM_MANAGER_H
#define MM_MANAGER_H

#include "MM_Config.h"
#include <stdio.h>

class MM_Manager
{
	public:
		MM_Manager(const size_t numObjects)
		{
			CommandMap.data = new void*[numObjects];
			CommandMap.max_size = numObjects;
		}

		// Add
		// Adds a new Object to the CommandMap. Returns false if new element cannot be added
		// \param [void*] Object - Pointer to the new Object
		// \return [bool] - false if out of bounds, true if added
		bool Add(void* Object)
		{
			// Out of bounds check
			if(CommandMap.size >= CommandMap.max_size) return false;

			// Add the object to the next position in the CommandMap
			CommandMap.size += 1;
			CommandMap.data[CommandMap.size] = Object;
			return true;
		}

		void test()
		{
			char buffer[100];
			sprintf(buffer, "Testing %d\n", 1);
			MM_Serial_Print(buffer);
		}

	private:
		struct {
			void** data = nullptr;
			unsigned size = 0;
			unsigned max_size = 0;
		} CommandMap;

};

#endif
