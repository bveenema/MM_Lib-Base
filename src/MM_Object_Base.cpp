#include "MM_Object_Base.h"

void ToString(char * buffer, int value)
{
	sprintf(buffer, "%d", value);
}

void ToString(char* buffer, unsigned value)
{
	sprintf(buffer, "%u", value);
}

void ToString(char* buffer, float value)
{
	sprintf(buffer, "%f", value);
}

void ToString(char* buffer, double value)
{
	sprintf(buffer, "%f", value);
}

void ToString(char* buffer, char* value)
{
	strcpy(buffer, value);
}