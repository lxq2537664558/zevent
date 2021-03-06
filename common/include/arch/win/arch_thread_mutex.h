#ifndef WIN_THREAD_MUTEX_H
#define WIN_THREAD_MUTEX_H

#include <windows.h>

typedef enum thread_mutex_type {
    thread_mutex_critical_section,
    thread_mutex_unnested_event,
    thread_mutex_nested_mutex
} thread_mutex_type;

/* handle applies only to unnested_event on all platforms 
 * and nested_mutex on Win9x only.  Otherwise critical_section 
 * is used for NT nexted mutexes providing optimal performance.
 */
struct thread_mutex_t {
    thread_mutex_type type;
    HANDLE            handle;
    CRITICAL_SECTION  section;
};

#endif  /* THREAD_MUTEX_H */

