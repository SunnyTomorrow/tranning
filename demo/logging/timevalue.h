#ifndef __ZX_TIMEVALUE__
#define __ZX_TIMEVALUE__
#include <sys/time.h>

typedef unsigned int U32;
typedef unsigned long long U64;
#define U32U64(x)		( (U64(0x00000000ffffffff) & (U64)(x)) )
#define TMVU64(t)		( ((U64(t.tv_sec) * 1000 * 1000) + t.tv_usec) )
#define MKU64(h,l)		( ((U32U64(h) << 32) | U32U64(l) )
#define TIMEMAX 		( (~time_t(0) > time_t(1)) ? (~time_t(0)) : (~time_t(0) & ~(time_t(1) << (sizeof(time_t)*8-1))) )

class Timevalue
{
	protected:
		struct timeval stamp;

	public:
		Timevalue(void);
		Timevalue(time_t, time_t);
		Timevalue(const Timevalue&);

	public:
		bool gettimeofday(void) const;
		void operator()(time_t, time_t);
		time_t operator/(const Timevalue&);
		bool operator>(const Timevalue&) const;
		bool operator<(const Timevalue&) const;
		bool operator>=(const Timevalue&) const;
		bool operator<=(const Timevalue&) const;
		bool operator==(const Timevalue&) const;
		bool operator!=(const Timevalue&) const;
		Timevalue operator+(const Timevalue&) const;
		const Timevalue& operator=(const Timevalue&);
		const Timevalue& operator+=(const Timevalue&);
		const Timevalue& operator-=(const Timevalue&);
		const Timevalue& operator*=(const Timevalue&);
		const Timevalue& operator/=(const Timevalue&);
		const Timevalue& operator%=(const Timevalue&);
		const struct timeval& operator()(void) const;
		const time_t operator[](int) const;
};

#endif
