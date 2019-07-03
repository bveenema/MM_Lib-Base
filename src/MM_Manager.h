#ifndef MM_MANAGER_H
#define MM_MANAGER_H

#include "MM_Object_Base.h"

#include <stdio.h>

class MM_Manager
{
	public:
		MM_Manager(const size_t numObjects);

		// Add
		// Adds a new Object to the CommandMap. Returns false if new element cannot be added
		// \param [ObjectInterface*] Object - Pointer to the new Object
		// \return [bool] - false if out of bounds, true if added
		bool Add(ObjectInterface& Object);

		void test();

	private:
		struct {
			ObjectInterface** objects = nullptr;
			unsigned size = 0;
			unsigned max_size = 0;
		} CommandMap;

};

#endif
