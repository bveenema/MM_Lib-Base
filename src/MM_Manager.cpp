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

void MM_Manager::OnReady(void (*_OnReady)())
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

	if(commandNum == 0) // keyBuffer was string
	{
		if(strcmp(keyBuffer, "MICROMANAGER") == 0) // App sends micro manager when first connected, send "READY" as response
		{
			MM_Serial_Print("READY\r\n");
			onReady(); // call onReady callback
		}
		else if(strcmp(keyBuffer, "CONFIG") == 0) // App is requesting the configuration JSON string
		{
			char ConfigJSON[1024] = "CONFIG:{\"baud\":9600,\"name\":\"Amphora\",\"settings\":[{\"n\":\"Volume\",\"t\":\"slider\",\"c\":1,\"l\":20,\"h\":30,\"d\":20,\"r\":22,\"f\":0,\"i\":\"dB\"},{\"n\":\"MotorSeed\",\"t\":\"input\",\"c\":3,\"l\":0,\"h\":10,\"d\":1,\"r\":2,\"f\":0,\"i\":\"RPM\"},{\"n\":\"Direction\",\"t\":\"picker\",\"c\":5,\"d\":\"Left\",\"r\":\"Right\",\"o\":[\"Left\",\"Right\",\"Up\",\"Down\"]}],\"state\":[{\"n\":\"Temperature\",\"t\":\"output\",\"c\":8,\"l\":50,\"h\":90,\"u\":3000},{\"n\":\"Reset\",\"t\":\"button\",\"c\":10,\"b\":\"warning\",\"u\":10000},{\"n\":\"Light\",\"t\":\"toggle\",\"c\":12,\"u\":5000},{\"n\":\"LongProcess\",\"t\":\"process\",\"c\":14,\"u\":3000}]}\r\n";
			//TODO compile JSON string
			MM_Serial_Print(ConfigJSON);
		}
		else
		{
			MM_Serial_Print("ERROR: INVALID STRING COMMAND");
		}
	}
	else if(commandNum < CommandMap.size)// keyBuffer was a command and in range of valid MM_Objects
	{
		// Retrive string value the MM_Object corresponding to the command
		char valBuffer[64];
        CommandMap.objects[commandNum]->sValue(valBuffer);

		// Format and return Output
		char buffer[128];
		sprintf(buffer, "%d:%s\r\n", commandNum, valBuffer);
		MM_Serial_Print(buffer);
	}
	else // invalid command key
	{
		MM_Serial_Print("ERROR: INVALID COMMAND NUMBER");
	}

	valueBuffer[0] = 0; // reset the value buffer
	FLAG_NoRead = false; // Allow new messages
}

void MM_Manager::test()
{
    char buffer[100];
    sprintf(buffer, "0:CommandMap:\n"
                    "  size: %d\n"
                    "  max size: %d\n"
                    "  Elements:\n", CommandMap.size, CommandMap.max_size);
    for(unsigned i=0; i<CommandMap.size; i++)
    {
        char valBuffer[12];
        CommandMap.objects[i]->sValue(valBuffer);
        sprintf(buffer + strlen(buffer), "    %s\r\n", valBuffer);
    }
    
    MM_Serial_Print(buffer);
}
