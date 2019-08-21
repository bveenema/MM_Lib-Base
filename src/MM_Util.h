#ifndef MM_UTIL_H
#define MM_UTIL_H

#include <cmath>

#define MM_OVERLOADS  	operator const T& () const { return this->val; } \
						const T& operator = (const T& _value) { this->val = _value; return this->val; } \
						const T& operator += (const T& _value) { this->val += _value; return this->val; } \
						const T& operator -= (const T& _value) { this->val -= _value; return this->val; } \
						const T& operator *= (const T& _value) { this->val *= _value; return this->val; } \
						const T& operator /= (const T& _value) { this->val /= _value; return this->val; } \

inline void ToString(char* buffer, int value){ sprintf(buffer, "%i", value); }
inline void ToString(char* buffer, unsigned value){ sprintf(buffer, "%u", value); }
inline void ToString(char* buffer, float value){ sprintf(buffer, "%f", value); }
inline void ToString(char* buffer, double value){ sprintf(buffer, "%f", value); }

inline int ToValue(char* buffer, int value){ return atoi(buffer); }
inline unsigned ToValue(char* buffer, unsigned value){ return atol(buffer); }
inline float ToValue(char* buffer, float value){ return atof(buffer); }
inline double ToValue(char* buffer, double value){ return atof(buffer); }

template<typename T>
struct MM_Object_Parameter
{
	T value;
	bool defined = false;

	const T& operator = (const T& _value) { value = _value; defined = true; return value; }
	operator const T& () const { return value; }
};

template<size_t precision>
struct spFloat_t
{
  public:
    float fValue()
    {
      return float(val)/divisor;
    }

    unsigned fPrecision()
    {
      return precision;
    }

    unsigned fDivisor()
    {
      return divisor;
    }

    operator const int () const { return this->val; }

    const int& operator =  (const int& _value)   { this->val = _value*divisor; return this->val; }
    const int& operator =  (const float& _value) { this->val = _value*divisor; return this->val; }
    const int& operator += (const int& _value)   { this->val += _value*divisor; return this->val; }
    const int& operator += (const float& _value) { this->val += _value*divisor; return this->val; }
    const int& operator -= (const int& _value)   { this->val -= _value*divisor; return this->val; }
    const int& operator -= (const float& _value) { this->val -= _value*divisor; return this->val; }
    const int& operator *= (const int& _value)   { this->val *= _value; return this->val; }
    const int& operator *= (const float& _value) { this->val *= _value; return this->val; }
    const int& operator /= (const int& _value)   { this->val /= _value; return this->val; }
    const int& operator /= (const float& _value) { this->val /= _value; return this->val; }
    const int& operator %= (const int& _value)   { this->val %= _value*divisor; return this->val; }
    const int& operator %= (const float& _value) { this->val %= _value*divisor; return this->val; }

  private:
    int val;
    unsigned divisor = pow(10,precision);
};

template<size_t precision>
struct upFloat_t
{
  public:
    float fValue()
    {
      return float(val)/divisor;
    }

    unsigned fPrecision()
    {
      return precision;
    }

    unsigned fDivisor()
    {
      return divisor;
    }

    operator const unsigned () const { return this->val; }

    const unsigned& operator =  (const unsigned& _value)   { this->val = _value*divisor; return this->val; }
    const unsigned& operator =  (const float& _value) { this->val = _value*divisor; return this->val; }
    const unsigned& operator += (const unsigned& _value)   { this->val += _value*divisor; return this->val; }
    const unsigned& operator += (const float& _value) { this->val += _value*divisor; return this->val; }
    const unsigned& operator -= (const unsigned& _value)   { this->val -= _value*divisor; return this->val; }
    const unsigned& operator -= (const float& _value) { this->val -= _value*divisor; return this->val; }
    const unsigned& operator *= (const unsigned& _value)   { this->val *= _value; return this->val; }
    const unsigned& operator *= (const float& _value) { this->val *= _value; return this->val; }
    const unsigned& operator /= (const unsigned& _value)   { this->val /= _value; return this->val; }
    const unsigned& operator /= (const float& _value) { this->val /= _value; return this->val; }
    const unsigned& operator %= (const unsigned& _value)   { this->val %= _value*divisor; return this->val; }
    const unsigned& operator %= (const float& _value) { this->val %= _value*divisor; return this->val; }

  private:
    unsigned val;
    unsigned divisor = pow(10,precision);
};

#endif