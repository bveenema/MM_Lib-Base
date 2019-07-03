#include "MM_Config.h"
#include "MM_Manager.h"

#include <stdio.h>

MM_Manager::MM_Manager(const size_t numObjects)
{
    CommandMap.objects = new ObjectInterface*[numObjects];
    CommandMap.max_size = numObjects;
}

bool MM_Manager::Add(ObjectInterface& Object)
{
    // Out of bounds check
    if(CommandMap.size >= CommandMap.max_size) return false;

    // Add the object to the next position in the CommandMap
    CommandMap.objects[CommandMap.size] = &Object;
    CommandMap.size += 1;
    return true;
}

void MM_Manager::test()
{
    char buffer[100];
    sprintf(buffer, "CommandMap:\n"
                    "  size: %d\n"
                    "  max size: %d\n"
                    "  Elements:\n", CommandMap.size, CommandMap.max_size);
    for(unsigned i=0; i<CommandMap.size; i++)
    {
        char valBuffer[12];
        CommandMap.objects[i]->StringValue(valBuffer);
        sprintf(buffer + strlen(buffer), "    %s\n", valBuffer);
    }
    
    MM_Serial_Print(buffer);
}
