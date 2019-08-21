#include "MM_Config.h"
#include "MM_Manager.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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

void MM_Manager::DebugPrintf(const char* format, ...)
{
	// Add "0:" (Debug Designator) to beginning of output string
	char outputBuffer[1024] = "0:"; 

	// Concatenate format to output string and apply the args
	va_list args;
	va_start(args, format);
		vsprintf(outputBuffer + strlen(outputBuffer), format, args);
	va_end(args);
	
	// Add "\r\n" (end message designator) to end of output string
	strcat(outputBuffer, "\r\n");

	MM_Serial_Print(outputBuffer);
}

void MM_Manager::OnReady(std::function<void()> _OnReady)
{
	onReady = _OnReady;
}

void MM_Manager::Read(char c)
{
    /*
    Serial Stream comes in form of:
        {key}:{value} for a write, and
        {key} (with no ":") for a read
    followed by a newline character.

    ex. WRITE   --> 1:250
        READ    --> 1
        SPECIAL --> CONFIG
    */
	if(messageIndex >= messageBufferSize) messageIndex = 0; // prevent overflow

	if(FLAG_NoRead) return; // ignore stream while handling current message (prevents value and key buffer from changing while handling)

	if(c != '\n' && c != ':') // Regular characters
	{
		messageBuffer[messageIndex++] = c;
	}

	else if(c == ':') // key/value separator (write signifier)
	{
		messageBuffer[messageIndex] = 0; // Null terminate string
		FLAG_isWrite = true; // Next Stream is value to write
		strcpy(keyBuffer, messageBuffer); // Stream was a key
		messageIndex = 0; // reset buffer position
	}

	else // \n character (End transmission signifier)
	{
		messageBuffer[messageIndex] = 0; // Null terminate string
		if(FLAG_isWrite)
		{
			strcpy(valueBuffer, messageBuffer); // Stream was new value
		}
		else
		{
			strcpy(keyBuffer, messageBuffer); // Stream was a key
		}
		messageIndex = 0; // reset buffer position

		// Interpet the completed command
		MessageHandler();
	}
}

void MM_Manager::MessageHandler()
{
	FLAG_NoRead = true; // Prevent reading new strings into key and value buffer while Handler is running

	unsigned commandNum = atol(keyBuffer); // Attempt to convert the key to a number

	// DebugPrintf("Recieved: %s,(%u) - %s", keyBuffer, commandNum, valueBuffer);

	if(commandNum == 0) // keyBuffer was string
	{
		if(strcmp(keyBuffer, "MICROMANAGER") == 0) // App sends micro manager when first connected, send "READY" as response
		{
			MM_Serial_Print("READY\r\n");
			if(onReady) onReady(); // call onReady callback
		}
		else if(strcmp(keyBuffer, "CONFIG") == 0) // App is requesting the configuration JSON string
		{
			// Print Header info (Baud, Name, etc)
			char buffer[256] = "CONFIG:{";
			sprintf(buffer + strlen(buffer), "\"baud\":%u,\"name\":\"%s\"", 9600, "MM_Test");
			MM_Serial_Print(buffer);

			// Print Settings
			if(CommandMap.size > 0)
			{
				strcpy(buffer, ",\"settings\":[");
				MM_Serial_Print(buffer);

				for(unsigned i=0; i<CommandMap.size; i++)
				{
					CommandMap.objects[i]->sConfig(buffer);
					sprintf(buffer + strlen(buffer), ",\"c\":%u},", i+1);
					// replace the last comma with a ] to terminate the array
					if(i == CommandMap.size - 1) buffer[strlen(buffer)-1] = ']';
					MM_Serial_Print(buffer);
				}
			}

			// Signal End of Config
			MM_Serial_Print("}\r\n");
		}
		else
		{
			DebugPrintf("ERROR: INVALID STRING COMMAND");
		}
	}
	else if(commandNum <= CommandMap.size)// keyBuffer was a command and in range of valid MM_Objects
	{
		// Update the value of the object
		if(FLAG_isWrite) 
		{
			CommandMap.objects[commandNum-1]->sUpdate(valueBuffer);
			FLAG_isWrite = false;
		}

		// Retrive string value the MM_Object corresponding to the command
		char valBuffer[64];
        CommandMap.objects[commandNum-1]->sValue(valBuffer);

		// Format and return Output
		char buffer[128];
		sprintf(buffer, "%d:%s\r\n", commandNum, valBuffer);
		MM_Serial_Print(buffer);

		DebugPrintf("Processed: %u, ", commandNum);
		DebugPrintf("\tValue: %s", valueBuffer);
		DebugPrintf("\tReturned: %d:%s", commandNum, valBuffer);
	}
	else // invalid command key
	{
		DebugPrintf("ERROR: INVALID COMMAND NUMBER");
	}

	valueBuffer[0] = 0; // reset the value buffer
	FLAG_NoRead = false; // Allow new messages
}

void MM_Manager::test()
{
	char buffer[256] = "0:{";
	sprintf(buffer + strlen(buffer), "\"baud\":%u,\"name\":\"%s\"", 9600, "MM_Test");
	MM_Serial_Print(buffer);

	// Print Settings
	if(CommandMap.size > 0)
	{
		strcpy(buffer, ",\"settings\":[");
		MM_Serial_Print(buffer);

		for(unsigned i=0; i<CommandMap.size; i++)
		{
			CommandMap.objects[i]->sConfig(buffer);
			sprintf(buffer + strlen(buffer), ",\"c\":%u},", i+1);
			// replace the last comma with a ] to terminate the array
			if(i == CommandMap.size - 1) buffer[strlen(buffer)-1] = ']';
			MM_Serial_Print(buffer);
		}
	}

	// Signal End of Config
	MM_Serial_Print("}\r\n");
	

    // char buffer[100];
    // sprintf(buffer, "CommandMap:\n"
    //                 "  size: %d\n"
    //                 "  max size: %d\n"
    //                 "  Elements:\n", CommandMap.size, CommandMap.max_size);
    // for(unsigned i=0; i<CommandMap.size; i++)
    // {
    //     char valBuffer[12];
    //     CommandMap.objects[i]->sValue(valBuffer);
    //     sprintf(buffer + strlen(buffer), "    %s\n", valBuffer);
    // }
	// DebugPrintf(buffer);
}
