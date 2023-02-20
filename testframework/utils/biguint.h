#ifndef BIGINT_H
#define BIGINT_H

#include <sys/types.h>
#include <vector>

class BigUInt {
  private:
	std::vector<u_int64_t> vec;

	u_int32_t get_overflow(u_int64_t &i, bool clear = true);
	void add_at(u_int64_t v, size_t pos);

  public:
	BigUInt();
	BigUInt(u_int64_t v);

	friend BigUInt operator*(const BigUInt &a, const BigUInt &b);
	friend BigUInt operator+(const BigUInt &a, const BigUInt &b);
};

#endif