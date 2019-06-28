#ifndef MM_MANAGER_H
#define MM_MANAGER_H

#include "MM_Config.h"
#include <stdio.h>

class MM_Manager
{
	public:
		MM_Manager(){}

		void test()
		{
			char buffer[100];
			sprintf(buffer, "Testing %d\n", 1);
			MM_Serial_Print(buffer);
		}

	private:
};

extern MM_Manager manager;

#endif
