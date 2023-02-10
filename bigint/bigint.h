#pragma once

#include <string>
#include <ostream>

class bigint
{
private:
	std::string digits;

	bool issigned;
	int sign_val;

	bool smaller(bigint x, bigint rhs); // x < rhs
	bigint sum(bigint x, bigint y);
	bigint sub(bigint x, bigint y);
	bigint mul(bigint x, bigint y);
	bigint div(bigint x, bigint y);
	bigint mod(bigint x, bigint y);

public:
	bigint();

	bigint(std::string number, bool issigned = true);
	bigint(long long num);

	const std::string to_str();

	void parse(std::string num);
	int get_sign();
	bool is_signed();
	void make_signed(bool is);
	void change_sign(int s);

	bigint abs();
	bigint pow(bigint exp);

	// static
	static bigint abs(bigint num);
	static bigint min(bigint x, bigint y);
	static bigint max(bigint x, bigint y);
	static bigint gcd(bigint x, bigint y);

	bigint& operator = (bigint n);

	bool operator == (const bigint n);
	bool operator != (const bigint n);

	bool operator < (const bigint rhs);
	bool operator > (const bigint rhs);
	bool operator <= (const bigint rhs);
	bool operator >= (const bigint rhs);
	friend bool operator < (long long lhs, const bigint rhs);
	friend bool operator > (long long lhs, const bigint rhs);
	friend bool operator <= (long long lhs, const bigint rhs);
	friend bool operator >= (long long lhs, const bigint rhs);
	friend std::ostream& operator << (std::ostream& os, bigint rhs);

	bigint operator + (bigint n);
	bigint operator - (bigint n);
	bigint operator / (bigint n);
	bigint operator * (bigint n);
	bigint operator % (bigint n);
	bigint operator >> (bigint n);

	bigint& operator += (bigint rhs);
	bigint& operator -= (bigint rhs);
	bigint& operator *= (bigint rhs);
	bigint& operator /= (bigint rhs);
	bigint& operator %= (bigint rhs);
	bigint& operator >>= (bigint rhs);

	bigint& operator ++ ();
	bigint& operator -- ();
	bigint operator - (); // -bigint
};

