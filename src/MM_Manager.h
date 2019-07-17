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

		// Read
		// Reads and interprets character stream. Calls Message Handler when completed message is recieved
		// \param [char] c - The latest read character from the Serial Stream
		void Read(char c);

		// OnReady
		// Register a callback funciton to run after READY is sent to the app
		// \param[func] OnReady - callback, must accept void param and return void
		void OnReady(void (*_OnReady)());

		void test();

	private:
		// Message Variables
		const size_t messageBufferSize = 128;
		char messageBuffer[128];
		char keyBuffer[32];
		char valueBuffer[64];
		uint8_t messageIndex = 0;
		bool FLAG_isWrite = false;
		bool FLAG_NoRead = false;
		
		// Command Map Definition
		struct {
			ObjectInterface** objects = nullptr;
			unsigned size = 0;
			unsigned max_size = 0;
		} CommandMap;

		// Message Handler
		// Interprets messages interfaces with MM_Objects and sends responses to the app.
		void MessageHandler();
		void (*onReady)();

};

#endif
