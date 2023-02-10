#include "bigint.h"

bigint::bigint() {
	this->digits = "0";

	this->issigned = true;
	this->sign_val = 0;
}

bigint::bigint(std::string number, bool issigned) {
	this->issigned = issigned;
	this->parse(number);
}

bigint::bigint(long long num) {
	issigned = true;
	if (num == 0) {
		this->digits = "0";

		this->sign_val = 0;
	}
	else {
		if (num < 0) {
			this->sign_val = -1;
		}
		else {
			this->sign_val = 1;
		}

		this->digits = std::to_string(std::abs(num));
	}
}

const std::string bigint::to_str() {
	return (this->issigned && (this->sign_val == -1)) ? ("-" + digits) : digits;
}

void bigint::parse(std::string num) {
	std::string number = num;
	if (num[0] == '-') {
		if (!this->issigned) {
			throw("unsigned numbers can not be negative.");
		}

		this->sign_val = -1;
		number = num.substr(1, num.length() - 1);
	}
	else {
		this->sign_val = 1;
	}

	int ind = 0;
	while (number[ind] == '0') {
		if (ind == number.length()) {
			this->sign_val = 0;
			this->digits = "0";
			return;
		}
		else {
			ind++;
		}
	}

	this->digits = number.substr(ind, number.length() - ind);
}

int bigint::get_sign() {
	return this->sign_val;
}

bool bigint::is_signed() {
	return this->issigned;
}

void bigint::make_signed(bool is) {
	this->issigned = is;
	if (this->digits == "0") {
		sign_val = 0;
	}
	else {
		sign_val = 1;
	}
}

void bigint::change_sign(int s) {
	if (this->digits == "0") {
		this->sign_val = 0;
	}
	else {
		if (s == 0) {
			throw("the number is nonzero, sign can not be 0.");
		}

		this->sign_val = s;
	}
}

bigint& bigint::operator=(bigint n) {
	this->digits = n.digits;
	this->issigned = n.issigned;
	this->sign_val = n.sign_val;

	return *this;
}

bool bigint::operator==(bigint n) {
	return this->to_str() == n.to_str();
}

bool bigint::operator!=(bigint n) {
	return this->to_str() != n.to_str();
}

bool bigint::smaller(bigint x, bigint rhs) {
	if (x.get_sign() < rhs.get_sign()) {
		return true;
	}
	else if (x == rhs) {
		return false;
	}
	else {
		if (x.get_sign() == rhs.get_sign()) {
			int tl = x.digits.length();
			int rl = rhs.digits.length();
			int sgn = x.get_sign();

			if (tl < rl) {
				return sgn != -1;
			}
			else if (tl == rl) {
				for (int k = 0; k < tl; k++) {
					int ad = x.digits[k], bd = rhs.digits[k];
					if (ad != bd) {
						if (sgn == -1) {
							return ad > bd;
						}
						else {
							return ad < bd;
						}
					}
				}

				return false;
			}
			else {
				return sgn == -1;
			}
		}
		else {
			return false;
		}
	}
}

bigint bigint::gcd(bigint x, bigint y) {
	while (x != y) {
		if (x > y) {
			x = x - y;
		}
		else {
			y = y - x;
		}
	}

	return x;
}

bool bigint::operator< (const bigint rhs) {
	return smaller(*this, rhs);
}

bool bigint::operator> (const bigint rhs) {
	return smaller(rhs, *this);
}

bool bigint::operator<= (const bigint rhs) {
	return (*this < rhs) || (*this == rhs);
}

bool bigint::operator>= (const bigint rhs) {
	return (*this > rhs) || (*this == rhs);
}

// friend op.
bool operator< (long long lhs, const bigint rhs) {
	return bigint(lhs) < rhs;
}

bool operator> (long long lhs, const bigint rhs) {
	return bigint(lhs) > rhs;
}

bool operator<= (long long lhs, const bigint rhs) {
	return bigint(lhs) <= rhs;
}

bool operator>= (long long lhs, const bigint rhs) {
	return bigint(lhs) >= rhs;
}

std::ostream& operator<< (std::ostream& os, bigint rhs) {
	os << rhs.to_str();
	return os;
}

bigint bigint::min(bigint x, bigint y) {
	if (x <= y) {
		return x;
	}
	return y;
}

bigint bigint::max(bigint x, bigint y) {
	if (x >= y) {
		return x;
	}
	return y;
}

bigint bigint::abs(bigint num) {
	bigint tmp = num;
	tmp.change_sign(1);

	return tmp;
}

bigint bigint::abs() {
	bigint tmp = *this;
	tmp.change_sign(1);

	return tmp;
}

bigint bigint::sum(bigint x, bigint y) {
	if (x == bigint(0)) {
		return y;
	}
	if (y == bigint(0)) {
		return x;
	}

	if (x.get_sign() == -1 || y.get_sign() == -1) {
		if (x.get_sign() == -1 && y.get_sign() == -1) {
			return -sum(x.abs(), y.abs());
		}
		else if (x.get_sign() == -1 && y.get_sign() != -1) {
			return sub(y, x.abs());
		}
		else {
			return sub(x, y.abs());
		}
	}
	else {
		std::string xd = x.digits;
		std::string yd = y.digits;
		
		int lensub = xd.length() - yd.length();
		std::string zeros = std::string();
		for (int s = 0; s < (int)std::abs(lensub); s++) {
			zeros.push_back('0');
		}

		if (lensub > 0) {
			yd = zeros + yd;
		}
		else {
			xd = zeros + xd;
		}

		std::string result = std::string();

		int c = 0; // carry
		for (int i = xd.length() - 1; i >= 0; i--) {
			int a = xd[i] - '0';
			int b = yd[i] - '0';

			int dsum = a + b + c;

			c = (int)(dsum >= 10);
			dsum %= 10;

			result.insert(0, 1, (char)(dsum + '0'));
		}

		if (c != 0) {
			result.insert(0, 1, (char)(c + '0'));
		}

		return result;
	}
}

bigint bigint::sub(bigint x, bigint y) {
	if (x == y) {
		return bigint(0);
	}
	if (x == bigint(0)) { // 0 - y
		bigint yp = y;
		yp.change_sign(-1 * yp.get_sign());
		return yp;
	}
	else if (y == bigint(0)) {
		return x;
	}

	// 3 - 5 = -(5 - 3)
	if (x < y) {
		bigint nsub = sub(y, x);
		nsub.change_sign(-1);

		return nsub;
	}

	if (x.sign_val == -1 && y.sign_val != -1) {
		bigint sm = sum(x.abs(), y);
		sm.change_sign(-1);
		return sm;
	}
	else if (x.sign_val != -1 && y.sign_val == -1) {
		return sum(y.abs(), x);
	}
	else if (x.sign_val == -1 && y.sign_val == -1) {
		return sub(y.abs(), x.abs());
	}

	// subtract
	std::string xd = x.digits;
	std::string yd = y.digits;

	int lensub = xd.length() - yd.length();
	std::string zeros = std::string();
	for (int s = 0; s < (int)std::abs(lensub); s++) {
		zeros.push_back('0');
	}

	if (lensub > 0) {
		yd = zeros + yd;
	}
	else {
		xd = zeros + xd;
	}

	std::string result = std::string();

	int c = 0; // carry
	for (int i = xd.length() - 1; i >= 0; i--) {
		int a = xd[i] - '0';
		int b = yd[i] - '0';
		int dsub = 0;

		if (a == 0 && c == -1) {
			a = 9;
			dsub = a - b;
			
			result.insert(0, 1, (char)(dsub + '0'));
			continue;
		}
		else {
			a += c;
		}

		c = 0;

		if (a == b) {
			dsub = 0;
		}
		else if (a > b) {
			dsub = a - b;
		}
		else { // a < b
			c = -1;
			dsub = 10 + a - b;
		}

		if (i != 0 || dsub != 0) {
			result.insert(0, 1, (char)(dsub + '0'));
		}
	}

	return result;
}

bigint bigint::mul(bigint x, bigint y) {
	if (x == bigint(0) || y == bigint(0)) {
		return bigint(0);
	}
	
	if (x.get_sign() == -1 || y.get_sign() == -1) {
		int fsign = x.get_sign() * y.get_sign();
		bigint fn = mul(x.abs(), y.abs());
		fn.change_sign(fsign);
		return fn;
	}

	if (y > x) {
		return mul(y, x);
	}

	// multiply
	std::string xd = x.digits;
	std::string yd = y.digits;

	bigint result = bigint(0);

	int pad = 0;
	for (int i = yd.length() - 1; i >= 0; i--) {
		int d = yd[i] - '0';

		// x * d:
		std::string res = std::string();
		if (d == 0) {
			res = "0";
		}
		else if(d == 1) {
			res = xd;
		}
		else {
			int c = 0;
			for (int j = xd.length() - 1; j >= 0; j--) {
				int n = xd[j] - '0';
				int ml = (d * n) + c;
				int rem = ml % 10;
				c = (ml - rem) / 10;
				res.insert(0, 1, rem + '0');
			}
			if (c != 0) {
				res.insert(0, 1, c + '0');
			}
		}

		for (int k = 0; k < pad; k++) {
			res.push_back('0');
		}
		pad++;

		result = sum(result, bigint(res));
	}

	return result;
}

bigint bigint::div(bigint x, bigint y) {
	if (y == bigint(0)) {
		throw("division by zero.");
	}
	else if (x == bigint(0)) {
		return bigint(0);
	}
	else if (x == y) {
		return bigint(1);
	}

	if (x.get_sign() == -1 || y.get_sign() == -1) {
		int fsign = x.get_sign() * y.get_sign();
		bigint fn = div(x.abs(), y.abs());
		fn.change_sign(fsign);
		return fn;
	}

	if (y > x) {
		return div(y, x);
	}
	
	// long division
	std::string xd = x.digits;
	std::string yd = y.digits;

	std::string result = std::string();

	for (int i = yd.length(); i <= xd.length(); i++) {
		bigint d = bigint(xd.substr(0, i));

		bigint md = bigint(0);
		while (d >= y) {
			d = d - y;
			md = md + bigint(1);
		}

		if (md > bigint(0)) {
			std::string dstr = d.to_str();
			int len = dstr.length();
			for (int k = 0; k < i - len; k++) {
				dstr.insert(0, 1, '0');
			}
			xd.replace(xd.begin(), xd.begin() + i, dstr);
		}

		result += md.to_str();
	}

	return bigint(result);
}

bigint bigint::mod(bigint x, bigint y) {
	if (y == bigint(0)) {
		throw("modulus is zero.");
	}
	else if (x == bigint(0) || x == y) {
		return bigint(0);
	}

	if (x.get_sign() == -1) {
		if (x.abs() > y) {
			return y - mod(x.abs(), y);
		}
		else {
			return y + x;
		}
	}
	else if (x < y) {
		return x;
	}

	// long division
	std::string xd = x.digits;
	std::string yd = y.digits;

	for (int i = yd.length(); i <= xd.length(); i++) {
		bigint d = bigint(xd.substr(0, i));

		bigint md = bigint(0);
		while (d >= y) {
			d = d - y;
			md = md + bigint(1);
		}

		if (md > bigint(0)) {
			std::string dstr = d.to_str();
			int len = dstr.length();
			for (int k = 0; k < i - len; k++) {
				dstr.insert(0, 1, '0');
			}
			xd.replace(xd.begin(), xd.begin() + i, dstr);
		}
	}

	return bigint(xd); // residue
}

// Recursive exponentiation
bigint bigint::pow(bigint exp) {
	if (exp.get_sign() == -1) {
		throw("negative exponent.");
	}

	if (exp == 1) 
	{
		return *this;
	}
	if (exp % 2 == 1) {
		return *this * this->pow(exp - 1);
	}

	bigint tmp_exp = this->pow(exp / 2);
	return tmp_exp * tmp_exp;
}

// very slow
bigint shiftright(bigint num, bigint shift) {
	return num / bigint(2).pow(shift);
}

bigint shiftleft(bigint num, bigint shift) {
	return num * bigint(2).pow(shift);
}

bigint bigint::operator+ (bigint n) {
	return sum(*this, n);
}

bigint bigint::operator- (bigint n) {
	return sub(*this, n);
}

bigint bigint::operator* (bigint n) {
	return mul(*this, n);
}

bigint bigint::operator/ (bigint n) {
	return div(*this, n);
}

bigint bigint::operator% (bigint n) {
	return mod(*this, n);
}

bigint bigint::operator>> (bigint n) {
	return shiftright(*this, n);
}

bigint& bigint::operator+= (bigint rhs) {
	*this = *this + rhs;
	return *this;
}

bigint& bigint::operator-= (bigint rhs) {
	*this = *this - rhs;
	return *this;
}

bigint& bigint::operator*= (bigint rhs) {
	*this = *this * rhs;
	return *this;
}

bigint& bigint::operator/= (bigint rhs) {
	*this = *this / rhs;
	return *this;
}

bigint& bigint::operator%= (bigint rhs) {
	*this = *this % rhs;
	return *this;
}

bigint& bigint::operator>>= (bigint rhs) {
	*this = *this >> rhs;
	return *this;
}

bigint& bigint::operator++ () {
	*this += 1;
	return *this;
}

bigint& bigint::operator-- () {
	*this -= 1;
	return *this;
}

bigint bigint::operator- () {
	bigint chs = *this;
	chs.change_sign(-1 * chs.get_sign());
	
	return chs;
}
