#include "thread_mutex.h"
#include "arch_thread_mutex.h"


int thread_mutex_create(thread_mutex_t **mutex,
                                                  unsigned int flags)
{
    (*mutex) = (thread_mutex_t *)malloc(sizeof(thread_mutex_t));

	memset(*mutex,0,sizeof(thread_mutex_t));

    if (flags & THREAD_MUTEX_UNNESTED) {
        (*mutex)->type = thread_mutex_unnested_event;
        (*mutex)->handle = CreateEvent(NULL, FALSE, TRUE, NULL);
    }
    else {
            InitializeCriticalSection(&(*mutex)->section);
            (*mutex)->type = thread_mutex_critical_section;
    }

    return 0;
}

int thread_mutex_lock(thread_mutex_t *mutex)
{
    if (mutex->type == thread_mutex_critical_section) {
        EnterCriticalSection(&mutex->section);
    }
    else {
        DWORD rv = WaitForSingleObject(mutex->handle, INFINITE);
	if ((rv != WAIT_OBJECT_0) && (rv != WAIT_ABANDONED)) {
            return -1;
	}
    }        
    return 0;
}

int thread_mutex_trylock(thread_mutex_t *mutex)
{
    if (mutex->type == thread_mutex_critical_section) {
            return -1;
    }
    else {
        DWORD rv = WaitForSingleObject(mutex->handle, 0);
	if ((rv != WAIT_OBJECT_0) && (rv != WAIT_ABANDONED)) {
            return -1;
	}
    }        
    return 0;
}

int thread_mutex_unlock(thread_mutex_t *mutex)
{
    if (mutex->type == thread_mutex_critical_section) {
        LeaveCriticalSection(&mutex->section);
    }
    else if (mutex->type == thread_mutex_unnested_event) {
        if (!SetEvent(mutex->handle)) {
            return -1;
        }
    }
    else if (mutex->type == thread_mutex_nested_mutex) {
        if (!ReleaseMutex(mutex->handle)) {
            return -1;
        }
    }
    return 0;
}

int thread_mutex_destroy(thread_mutex_t *mutex)
{
	if (mutex->type == thread_mutex_critical_section) {
		mutex->type = -1;
		DeleteCriticalSection(&mutex->section);
	}
	else {
		CloseHandle(mutex->handle);
	}
	free(mutex);
	return 0;

}

