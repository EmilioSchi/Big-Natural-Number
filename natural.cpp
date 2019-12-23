/*
A simple library to rappresent large natural
numbers with fixed number of bits.

Written by Emilio Schinina' (emilioschi@gmail.com), DEC 2019
File:	natural.cc
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "natural.h"

natural::natural(uint sz)
{
	#if _DEBUG_
		std::cout << "[DEBUG] Allocation of new Number of " <<  uint(sz) << " bits @ "<< this << std::endl;
	#endif

	size = sz;

	value = (bool*) malloc(sizeof(bool) * size);
	if (!value)
		exit(1);

	bool* ptr = value;
	for (uint i = 0; i < size; ++i)
		*(ptr + i) = 0;
}

natural::natural()
{
	#if _DEBUG_
		std::cout << "[DEBUG] Allocation of new " << _DEFAULT_SIZE_ << "bits natural @ "<< this << std::endl;
	#endif

	size = _DEFAULT_SIZE_;

	value = (bool*) malloc(sizeof(bool) * _DEFAULT_SIZE_);
	if (!value)
		exit(1);

	bool* ptr = value;
	for (uint i = 0; i < _DEFAULT_SIZE_; ++i)
		*(ptr++) = 0;

}

natural::natural(const natural& other)
{
	#if _DEBUG_
		std::cout << "[DEBUG] Copy Constructor called. THIS @ " << this << std::endl;
	#endif

	size = other.size;

	value = (bool*) malloc(sizeof(bool) * size);
	if (!value)
		exit(1);

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;

	for (uint i = 0; i < size; ++i)
		*(ptr_1++) = *(ptr_2++);

}

natural::~natural()
{
	SAFE_FREE(value);
}

uint natural::getsize()
{
	return size;
}

// Big Endian
void natural::print_bin()
{
	std::cout << ">> 0b";
	bool* ptr = value;
	for (uint i = 0; i < size; ++i) {
		if (*ptr++)		std::cout << "1";
		else			std::cout << "0";
	}
	std::cout << std::endl;
}

// TODO CHAR DEC
void natural::print_dec()
{
	ASSERT(size <= 128);
	bool* ptr = value;
	uint dec = 0;
	std::cout << ">> 0d";
	for (uint i = 0; i < size; ++i)
		if (*ptr++)	dec += pow(2, i);
	std::cout << uint(dec) << std::endl;
}

bool& natural::proxy::operator=(const bool v)
{
	a->value[idx] = v;
	return a->value[idx];
}

natural::proxy::operator bool() const {
	return a->value[idx];
}


natural::proxy natural::operator[](const uint index)
{
	ASSERT(index >= (uint)0 && index < size);
	return proxy(this, index);
}

natural& natural::operator=(const natural& other)
{
	#if _DEBUG_
		std::cout << "[DEBUG] Overoaded Assignent called. Number of" << uint(size) << " bits @ "<< this << std::endl;
	#endif

	// self assignment check
	if (this == &other) {
		#if _DEBUG_
			std::cout << "[DEBUG] Same object: "<< this << std::endl;
		#endif
		return *this;
	}

	size = other.size;

	value = (bool*) realloc(value, sizeof(bool) * size);
	if (!value) {
		exit(1);
	}

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;

	for (uint i = 0; i < size; ++i) {
		*(ptr_1++) = *(ptr_2++);
	}

	return *this;
}

natural natural::operator<<(const uint shift)
{
	natural leftshifted(size);

	bool* ptr_result = leftshifted.value;
	bool* ptr = value;

	for (uint i = 0; i < shift; ++i)
		*(ptr_result++) = 0;
	for (uint i = 0; i < size - shift; ++i)
		*(ptr_result++) = *(ptr++);

	return leftshifted;
}

natural natural::operator>>(const uint shift)
{
	natural rightshifted(size);

	bool* ptr_result = rightshifted.value;
	bool* ptr = value;

	for (uint i = 0; i < shift; ++i)
		ptr++;
	for (uint i = 0; i < size - shift; ++i)
		*(ptr_result++) = *(ptr++);
	for (uint i = 0; i < shift; ++i)
		*(ptr_result++) = 0;

	return rightshifted;
}

natural natural::operator~()
{
	natural negate(size);
	bool* ptr_result = negate.value;
	bool* ptr = value;
	for (uint i = 0; i < size; ++i)
		*(ptr_result++) = !(*(ptr++));
	return negate;
}

bool natural::operator>(const natural& other)
{
	natural ltb(size), gtb(size), tmp(size), isGt(size);

	natural a = *this;
	natural b = other;

	ltb = ~a;
	ltb = ltb & b;

	gtb = ~b;
	gtb = gtb & a;

	for (uint i = 1; i < size; i*=2) {
		tmp = ltb >> i;
		ltb = ltb | tmp;
	}

	tmp = ~ltb;
	isGt = gtb & tmp;

	for (uint i = 1; i < size; i*=2) {
		tmp = isGt >> i;
		isGt = isGt | tmp;
	}

	return isGt[0];
}

bool natural::operator==(const natural& other)
{
	ASSERT(size == other.size);

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;

	for (uint i = 0; i < size; ++i) {
		if ((*(ptr_1++)) != (*(ptr_2++)))
			return false;
	}

	return true;
}

bool natural::operator!=(const natural& other)
{
	ASSERT(size == other.size);

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;

	for (uint i = 0; i < size; ++i) {
		if ((*(ptr_1++)) != (*(ptr_2++)))
			return true;
	}

	return false;
}

bool natural::operator<(const natural& other)
{
	ASSERT(size == other.size);
	return !(*this > other) && (*this != other);
}

bool natural::operator>=(const natural& other)
{
	ASSERT(size == other.size);
	return (*this > other) || (*this == other);
}

bool natural::operator<=(const natural& other)
{
	ASSERT(size == other.size);
	return !(*this > other);
}

natural natural::operator|(const natural& other)
{
	ASSERT(size == other.size);

	natural logicor;

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;
	bool* ptr_result = logicor.value;

	for (uint i = 0; i < size; ++i)
		*(ptr_result++) = *(ptr_1++) | *(ptr_2++);

	return logicor;
}

natural natural::operator&(const natural& other)
{
	ASSERT(size == other.size);

	natural logicand;

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;
	bool* ptr_result = logicand.value;

	for (uint i = 0; i < size; ++i)
		*(ptr_result++) = *(ptr_1++) & *(ptr_2++);

	return logicand;
}

natural natural::operator+(const natural& other)
{
	ASSERT(size == other.size);

	natural sum(size);

	bool a, b, d;
	bool carry = 0;

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;
	bool* ptr_result = sum.value;

	for(uint i = 0; i < size; ++i) {
		a = *(ptr_1++);
		b = *(ptr_2++);
		d = a ^ b;
		*(ptr_result++) = d ^ carry;
		carry = (d & carry) | (a & b);
	}

	// OVERFLOW
	ASSERT(carry != 1);

	return sum;
}

natural natural::operator-(const natural& other)
{
	ASSERT(size == other.size);
	ASSERT(*this >= other);

	natural sub(size);

	bool a, b, d;
	bool borrow = 0;

	bool* ptr_1 = value;
	bool* ptr_2 = other.value;
	bool* ptr_result = sub.value;

	for(uint i = 0; i < size; ++i) {
		a = *(ptr_1++);
		b = *(ptr_2++);
		d = a ^ b;
		*(ptr_result++) = d ^ borrow;
		borrow = (!d & borrow) | (!a & b);
	}

	// OVERFLOW
	ASSERT(borrow != 1);

	return sub;
}

natural natural::operator*(const natural& other)
{
	ASSERT(size == other.size);

	natural multiplier(size);

	natural a = *this;

	bool* ptr = other.value;

	for (uint i = 0; i < size; ++i) {
		if (*(ptr++))
			multiplier += (a << i);
	}

	return multiplier;
}

natural natural::operator/(const natural& other)
{
	ASSERT(size == other.size);

	natural quotient(size), remaind(size);
	natural zero(size);

	natural dividend = *this;
	natural divisor = other;

	if (dividend == zero)
		return zero;

	if (divisor == zero)
		return zero;

	bool tmp_bit;
	uint e = 0;
	for (uint i = size - 1; e < size; --i, e++) {
		tmp_bit = dividend[i];
		remaind[0] = tmp_bit;

		quotient = quotient << 1;

		if ((divisor == remaind) || (remaind > divisor)) {
			remaind = remaind - divisor;
			quotient[0] = 1;
		}

		remaind = remaind << 1;
	}
	//remaind = remaind >> 1;
	return quotient;
}

natural natural::operator%(const natural& other)
{
	ASSERT(size == other.size);

	natural quotient(size), remaind(size);
	natural zero(size);

	natural dividend = *this;
	natural divisor = other;

	if (dividend == zero)
		return zero;

	if (divisor == zero)
		return zero;

	bool tmp_bit;
	uint e = 0;
	for (uint i = size - 1; e < size; --i, e++) {
		tmp_bit = dividend[i];
		remaind[0] = tmp_bit;

		quotient = quotient << 1;

		if ((divisor == remaind) || (remaind > divisor)) {
			remaind = remaind - divisor;
			quotient[0] = 1;
		}

		remaind = remaind << 1;
	}
	remaind = remaind >> 1;

	return remaind;
}

natural natural::operator+=(const natural& other)
{
	return *this = *this + other;
}

natural natural::operator-=(const natural& other)
{
	return *this = *this - other;
}

natural natural::operator*=(const natural& other)
{
	return *this = *this * other;
}

natural natural::operator/=(const natural& other)
{
	return *this = *this * other;
}

natural natural::operator%=(const natural& other)
{
	return *this = *this % other;
}
