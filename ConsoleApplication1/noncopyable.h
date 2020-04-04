#pragma once
#ifndef _C_NONCOPYABLE_INCLUDE_
#define _C_NONCOPYABLE_INCLUDE_


class noncopyable {
public:
	noncopyable(const noncopyable&) = delete;
	void operator=(const noncopyable&) = delete;
protected:
	noncopyable() = default;
	~noncopyable() = default;
};

#endif // !_C_NONCOPYABLE_INCLUDE_