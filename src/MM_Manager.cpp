#include "MM_Config.h"
#include "MM_Manager.h"

#include <stdio.h>

MM_Manager::MM_Manager(const size_t numObjects)
{
    CommandMap.objects = new ObjectInterface*[numObjects];
    CommandMap.max_size = numObjects;
}

// Add
// Adds a new Object to the CommandMap. Returns false if new element cannot be added
// \param [void*] Object - Pointer to the new Object
// \return [bool] - false if out of bounds, true if added
bool MM_Manager::Add(ObjectInterface* Object)
{
    // Out of bounds check
    if(CommandMap.size >= CommandMap.max_size) return false;

    // Add the object to the next position in the CommandMap
    CommandMap.objects[CommandMap.size] = Object;
    CommandMap.size += 1;
    return true;
}

void MM_Manager::test()
{
    char buffer[100];
    sprintf(buffer, "CommandMap:\n"
                    "\tsize: %d\n"
                    "\tmax size: %d\n"
                    "Elements:\n"
                    "\t\tvalue: %s", CommandMap.size, CommandMap.max_size, CommandMap.objects[0]->StringValue());
    MM_Serial_Print(buffer);
}
