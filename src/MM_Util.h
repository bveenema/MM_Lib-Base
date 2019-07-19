#ifndef MM_UTIL_H
#define MM_UTIL_H

#define MM_OVERLOADS  	operator const T& () const { return this->val; } \
						const T& operator = (const T& _value) { this->val = _value; return this->val; } \
						const T& operator += (const T& _value) { this->val += _value; return this->val; } \
						const T& operator -= (const T& _value) { this->val -= _value; return this->val; } \
						const T& operator *= (const T& _value) { this->val *= _value; return this->val; } \
						const T& operator /= (const T& _value) { this->val /= _value; return this->val; } \

#endif