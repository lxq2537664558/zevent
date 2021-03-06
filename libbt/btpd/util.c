#include "btpd.h"

#include <stdarg.h>
#include <time.h>
#include <io.h>

int
btpd_id_eq(const void *k1, const void *k2)
{
    return memcmp(k1, k2, 20) == 0;
}

uint32_t
btpd_id_hash(const void *k)
{
    return dec_be32((char *)k + 16);
}

void *
btpd_malloc(size_t size)
{
    void *a;
    if ((a = malloc(size)) == NULL)
        btpd_err("Failed to allocate %d bytes.\r\n", (int)size);
    return a;
}

void *
btpd_calloc(size_t nmemb, size_t size)
{
    void *a;
    if ((a = calloc(nmemb, size)) == NULL)
        btpd_err("Failed to allocate %d bytes.\r\n", (int)(nmemb * size));
    return a;
}

void
btpd_ev_new(struct fdev *ev, SOCKET fd, uint16_t flags, evloop_cb_t cb, void *arg)
{
    if (fdev_new(ev, fd, flags, cb, arg) != 0)
        btpd_err("Failed to add event (%s).\r\n", strerror(errno));
}

void
btpd_ev_del(struct fdev *ev)
{
    if (fdev_del(ev) != 0)
        btpd_err("Failed to remove event (%s).\r\n", strerror(errno));
}

void
btpd_ev_enable(struct fdev *ev, uint16_t flags)
{
    if (fdev_enable(ev, flags) != 0)
        btpd_err("Failed to enable event (%s).\r\n", strerror(errno));
}

void
btpd_ev_disable(struct fdev *ev, uint16_t flags)
{
    if (fdev_disable(ev, flags) != 0)
        btpd_err("Failed to disable event (%s).\r\n", strerror(errno));
}

void
btpd_timer_add(struct timeout *to, struct timespec *ts)
{
    if (evtimer_add(to, ts) != 0)
        btpd_err("Failed to add timeout (%s).\r\n", strerror(errno));
}

void
btpd_timer_del(struct timeout *to)
{
    evtimer_del(to);
}

static int logfd;

void log_init()
{
    vopen(&logfd, O_CREAT|O_RDWR|O_APPEND,"%s","log.txt");
}

void log_fini()
{
    _close(logfd);
}

static const char *
logtype_str(uint32_t type)
{
    switch (type) {
    case BTPD_L_BTPD:  return "btpd";
    case BTPD_L_ERROR: return "error";
    case BTPD_L_CONN:  return "conn";
    case BTPD_L_TR:    return "tracker";
    case BTPD_L_MSG:   return "msg";
    case BTPD_L_POL:   return "policy";
    case BTPD_L_BAD:   return "bad";
    }
    return "";
}

static void
log_common(uint32_t type, const char *fmt, va_list ap)
{
    if (type & btpd_logmask) {
	char log[4096];
	fpos_t off = 0;
	time_t tp = time(NULL);
	strftime(log,sizeof(log), "%b %d %H:%M:%S",localtime(&tp));
	off = strlen(log);
	sprintf(log + off," %s ",logtype_str(type));
	off = strlen(log);
	vsprintf(log+off,fmt,ap);
	_lseek(logfd,0,SEEK_END);
	f_write_fully(logfd,log,strlen(log));
    }
}


void
btpd_err(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
/*    if (btpd_daemon_phase > 0) {
        vprintf(fmt, ap);
        if (btpd_daemon_phase == 1)
            first_btpd_exit(1);
        exit(1);
    } else*/ {
        log_common(BTPD_L_ERROR, fmt, ap);
        //abort();
    }
}

void
btpd_log(uint32_t type, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    log_common(type, fmt, ap);
    va_end(ap);
}
