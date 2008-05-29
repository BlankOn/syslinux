#ifndef _GPXE_RETRY_H
#define _GPXE_RETRY_H

/** @file
 *
 * Retry timers
 *
 */

#include <gpxe/list.h>

/** A retry timer */
struct retry_timer {
	/** List of active timers */
	struct list_head list;
	/** Timeout value (in ticks) */
	unsigned long timeout;
	/** Start time (in ticks)
	 *
	 * A start time of zero indicates a stopped timer.
	 */
	unsigned long start;
	/** Retry count */
	unsigned int count;
	/** Timer expired callback
	 *
	 * @v timer	Retry timer
	 * @v fail	Failure indicator
	 *
	 * The timer will already be stopped when this method is
	 * called.  The failure indicator will be True if the retry
	 * timeout has already exceeded @c MAX_TIMEOUT.
	 */
	void ( * expired ) ( struct retry_timer *timer, int over );
};

extern void start_timer ( struct retry_timer *timer );
extern void start_timer_nodelay ( struct retry_timer *timer );
extern void stop_timer ( struct retry_timer *timer );

/**
 * Test to see if timer is currently running
 *
 * @v timer		Retry timer
 * @ret running		Non-zero if timer is running
 */
static inline __attribute__ (( always_inline )) unsigned long
timer_running ( struct retry_timer *timer ) {
	return ( timer->start );
}

#endif /* _GPXE_RETRY_H */