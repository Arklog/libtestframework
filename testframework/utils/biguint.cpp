//
// Created by pierre on 20/02/23.
//
#include "utils/biguint.h"

BigUInt::BigUInt() { vec.push_back(0); }
BigUInt::BigUInt(u_int64_t v) {
	vec.push_back(v & 0xffff);
	vec.push_back((v & 0xffff0000) >> 32);
}

u_int32_t BigUInt::get_overflow(u_int64_t &i, bool clear) {
	u_int32_t overflow;

	overflow = i & 0xffff0000;
	if (clear)
		i &= 0x0000ffff;
	return (overflow);
}

void BigUInt::add_at(u_int64_t v, size_t pos) {
	size_t len(vec.size());
	u_int64_t overflow;

	while (pos >= len) {
		vec.push_back(0);
		++len;
	}
	overflow = get_overflow(v);
	vec.at(pos) += v;
	overflow += get_overflow(vec.at(pos));
	if (overflow)
		add_at(overflow, pos + 1);
}

BigUInt operator+(const BigUInt &a, const BigUInt &b) {
	BigUInt n(a);

	for (size_t i = 0; i < b.vec.size(); ++i)
		n.add_at(b.vec.at(i), i);
	return (n);
}