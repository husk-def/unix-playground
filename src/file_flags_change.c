#include <fcntl.h>
#include <assert.h>

void
set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
	int    val;
	assert((val = fcntl(fd, F_GETFL, 0)) >= 0);

	val |= flags;

	assert(fcntl(fd, F_SETFL, val) >= 0);
}

/*
when we modify either the fd flags or the file status flags,
we must be careful to fetch the existing flag value, modify
as desired, and the set the new flag value. we can't simply
issue an F_SETFD or an F_SETFL command, as this could turn off 
flag bits that were previously set.
*/
