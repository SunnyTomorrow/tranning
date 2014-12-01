#include "timevalue.h"

Timevalue::Timevalue(void)
{
	stamp.tv_sec = time_t(0);
	stamp.tv_usec= time_t(0);
	//::gettimeofday(&stamp, 0);
}//Timevalue


Timevalue::Timevalue(time_t sec, time_t usec)
{
	stamp.tv_sec = sec;
	stamp.tv_sec += usec / (1000 * 1000);
	stamp.tv_usec = usec % (1000 * 1000);
}//Timevalue


Timevalue::Timevalue(const Timevalue& tval)
{
	stamp = tval.stamp;
}//Timevalue


bool Timevalue::gettimeofday(void) const
{
	return !::gettimeofday((struct timeval*)&stamp, 0);
}//Update


bool Timevalue::operator>(const Timevalue& t) const
{
	U64 uscl = TMVU64(stamp);
	U64 usci = TMVU64(t.stamp);

	return (uscl > usci);
}//operator>(t)


bool Timevalue::operator<(const Timevalue& t) const
{
	U64 uscl = TMVU64(stamp);
	U64 usci = TMVU64(t.stamp);

	return (uscl < usci);
}//operator<(t)


bool Timevalue::operator==(const Timevalue& t) const
{
	U64 uscl = TMVU64(stamp);
	U64 usci = TMVU64(t.stamp);

	return (uscl == usci);
}//operator==(t)


bool Timevalue::operator>=(const Timevalue& t) const
{
	return !(*this < t);
}//operator>=(t)


bool Timevalue::operator<=(const Timevalue& t) const
{
	return !(*this > t);
}//operator<=(t)


bool Timevalue::operator!=(const Timevalue& t) const
{
	return !(*this == t);
}//operator!=(t)


Timevalue Timevalue::operator+(const Timevalue& tval) const
{
	Timevalue tmp(*this);

	return (tmp += tval);
}//operator+(t)


const Timevalue& Timevalue::operator=(const Timevalue& t)
{
	stamp = t.stamp;
	return *this;
}//operator=(t)


const Timevalue& Timevalue::operator+=(const Timevalue& t)
{
	U64 uscl = TMVU64(stamp) + TMVU64(t.stamp);

	stamp.tv_sec = ~time_t(0) & ( uscl / (1000 * 1000) );
	stamp.tv_usec= ~time_t(0) & ( uscl % (1000 * 1000) );

	return *this;
}//operator+=(t)


const Timevalue& Timevalue::operator-=(const Timevalue& t)
{
	U64 uscl = TMVU64(stamp) - TMVU64(t.stamp);

	stamp.tv_sec = ~time_t(0) & ( uscl / (1000 * 1000) );
	stamp.tv_usec= ~time_t(0) & ( uscl % (1000 * 1000) );

	return *this;
}

const Timevalue& Timevalue::operator*=(const Timevalue& t)
{
	U64 uscl = TMVU64(stamp) * TMVU64(t.stamp);

	stamp.tv_sec = ~time_t(0) & ( uscl / (1000 * 1000) );
	stamp.tv_usec= ~time_t(0) & ( uscl % (1000 * 1000) );

	return *this;
}//operator*=(t)


const Timevalue& Timevalue::operator/=(const Timevalue& t)
{
	if( TMVU64(t.stamp) == 0 )
		return *this;
	U64 uscl = TMVU64(stamp) / TMVU64(t.stamp);

	stamp.tv_sec = ~time_t(0) & ( uscl / (1000 * 1000) );
	stamp.tv_usec= ~time_t(0) & ( uscl % (1000 * 1000) );

	return *this;
}//operator/=(t)


const Timevalue& Timevalue::operator%=(const Timevalue& t)
{
	U64 uscl = TMVU64(stamp) % TMVU64(t.stamp);

	stamp.tv_sec = ~time_t(0) & ( uscl / (1000 * 1000) );
	stamp.tv_usec= ~time_t(0) & ( uscl % (1000 * 1000) );

	return *this;
}//operator%=(t)


time_t Timevalue::operator/(const Timevalue& t)
{
	if( TMVU64(t.stamp) == U64(0) )
		return TIMEMAX;
	U64 r = TMVU64(stamp) / TMVU64(t.stamp);

	return (r & TIMEMAX);
}//operator/(t)


const struct timeval& Timevalue::operator()(void) const
{
	return stamp;
}//operator()


void Timevalue::operator()(time_t sec, time_t usec)
{
	stamp.tv_sec = sec;
	stamp.tv_sec += usec / (1000 * 1000);
	stamp.tv_usec = usec % (1000 * 1000);
}//operator()


const time_t Timevalue::operator[](int i) const
{
	if( 1 & i )
		return stamp.tv_usec;
	return stamp.tv_sec;
}//operator[]


