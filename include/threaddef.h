/*
  threaddef.h  --- Absorb trivial differences amoung thread interfaces.
*/

#ifndef _THREADDEF_H_
#define _THREADDEF_H_

#include <config.h>

#ifdef HAVE_PTHREAD

#include <pthread.h>
#define THREAD_OBJECT pthread_t
#define THREAD_ID_OBJECT pthread_t
#define THREAD_SYNC_OBJECT pthread_mutex_t
#define THREAD_EVENT_OBJECT pthread_cond_t
#define LOCK_SYNC_OBJECT(so) (pthread_mutex_lock(&(so)))
#define UNLOCK_SYNC_OBJECT(so) (pthread_mutex_unlock(&(so)))
#define LOCK_SYNC_OBJECT_FOR_EVENT(so) (pthread_mutex_lock(&(so)))
#define UNLOCK_SYNC_OBJECT_FOR_EVENT(so) (pthread_mutex_unlock(&(so)))
#define INIT_SYNC_OBJECT(so) (pthread_mutex_init(&(so), NULL))
#define DESTROY_SYNC_OBJECT(so) (pthread_mutex_destroy(&(so)))
#define INIT_EVENT_OBJECT(eo) (pthread_cond_init(&(eo), NULL))
#define DESTROY_EVENT_OBJECT(eo) (pthread_cond_destroy(&(eo)))
#define THREAD_CREATE(so, handler, arg) \
  (pthread_create(&(so), NULL, (handler), (arg)))
#define THREAD_DETACH(so) (pthread_detach(so))
#define THREAD_WAIT_AND_FREE(so) (pthread_join((so), NULL))
#define THREAD_SET_CURRENT_ID(tid) ((tid) = pthread_self())
#define THREAD_ID(so) (so)
#define THREAD_ID_EQUAL(tid1, tid2) (pthread_equal((tid1), (tid2)))
#define THREAD_RESET_EVENT(eo) /* do nothing */
#define THREAD_WAIT_EVENT(eo, so) (pthread_cond_wait(&(eo), &(so)))
#define THREAD_SIGNAL_EVENT(eo, so) (pthread_cond_signal(&(eo)))

#elif defined(HAVE_UITHREAD)

// TODO

#elif defined(WIN32)

#include <windows.h>
#define THREAD_OBJECT HANDLE
#define THREAD_SYNC_OBJECT HANDLE
#define THREAD_ID_OBJECT DWORD
#define THREAD_SYNC_OBJECT CRITICAL_SECTION
#define THREAD_EVENT_OBJCET HANDLE
#define LOCK_SYNC_OBJECT(so) (EnterCriticalSection(&(so)))
#define UNLOCK_SYNC_OBJECT(so) (LeaveCriticalSection(&(so)))
#define LOCK_SYNC_OBJECT_FOR_EVENT(so) /* do nothing */
#define UNLOCK_SYNC_OBJECT_FOR_EVENT(so) /* do nothing */
#define INIT_SYNC_OBJECT(so) (InitializeCriticalSection(&(so))
#define DESTROY_SYNC_OBJECT(so) (DeleteCriticalSection(&(so)))
/* NOTE THAT manual, nonsignaled event!!! */
#define INIT_EVENT_OBJECT(eo) ((eo) = CreateEvent(NULL, TRUE, FALSE, NULL)) 
#define DESTROY_EVENT_OBJECT(eo) (CloseHandle(eo))
#define THREAD_CREATE(so, handler, arg) \
  ((so) = _beginthread((handler), 0, (arg)))
#define THREAD_DETACH(so) (CloseHandle(so))
#define THREAD_WAIT_AND_FREE(so) \
  ((WaitForSingleObject(so, INFINITE) == WAIT_OBJECT_0) && CloseHandle(so))
#define THREAD_SET_CURRENT_ID(tid) ((tid) = GetCurrentThreadId())
#define THREAD_ID_EQUAL(tid1, tid2) ((tid1) == (tid2))
#define THREAD_RESET_EVENT(eo) (ResetEvent(eo))
#define THREAD_WAIT_EVENT(eo, so) (WaitForSingleObject(eo, INFINITE))
#define THREAD_SIGNAL_EVENT(eo, so) (SetEvent(so))

#elif defined(HAVE_NO_THREAD)

#define THREAD_OBJECT
#define THREAD_SYNC_OBJECT
#define THREAD_ID_OBJECT
#define THREAD_SYNC_OBJECT
#define THREAD_EVENT_OBJCET
#define LOCK_SYNC_OBJECT(so) ((void) 0)
#define UNLOCK_SYNC_OBJECT(so) ((void) 0)
#define DEFINE_SYNC_OBJECT(so) ((void) 0)
#define DEFINE_SYNC_OBJECT_STATIC(so) ((void) 0)
#define LOCK_SYNC_OBJECT_FOR_EVENT(so) ((void) 0)
#define UNLOCK_SYNC_OBJECT_FOR_EVENT(so) ((void) 0)
#define INIT_SYNC_OBJECT(so) ((void) 0)
#define DESTROY_SYNC_OBJECT(so) ((void) 0)
#define INIT_EVENT_OBJECT(eo) ((void) 0)
#define DESTROY_EVENT_OBJECT(eo) ((void) 0)
#define THREAD_CREATE(so, handler, arg) ((void) 0)
#define THREAD_DETACH(so) ((void) 0)
#define THREAD_WAIT_AND_FREE(so) ((void) 0)
#define THREAD_SET_CURRENT_ID(tid) ((void) 0)
#define THREAD_ID_EQUAL(tid1, tid2) ((void) 0)
#define THREAD_RESET_EVENT(eo) ((void) 0)
#define THREAD_WAIT_EVENT(eo, so) ((void) 0)
#define THREAD_SIGNAL_EVENT(eo, so) ((void) 0)

#else
#error "This system dose not have thread feature!"
#endif

#endif /* not _THREADDEF_H_ */

