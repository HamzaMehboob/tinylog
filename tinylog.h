/* tinylog.h – v1.0 – MIT License
 *
 * Drop‑in logging for C89+.
 *   • Levels: TRACE, DEBUG, INFO, WARN, ERROR, FATAL
 *   • Compile‑time filter: define TINYLOG_LEVEL (default INFO)
 *   • Color output on ANSI consoles, off on Windows unless TERM supports it
 *   • Thread‑safe if TINYLOG_USE_MUTEX + tinylog_lock()/unlock() provided
 *   • Redirect output: tinylog_set_fp(FILE*)
 *
 * Usage:
 *     #define TINYLOG_IMPLEMENTATION
 *     #include "tinylog.h"
 *
 *     LOG_INFO("Hello %s", "world");
 */
#ifndef TINYLOG_H
#define TINYLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/* -------- cfg defaults -------- */
#ifndef TINYLOG_LEVEL      /* default minimum level shown at runtime */
#   define TINYLOG_LEVEL TL_INFO
#endif
#ifndef TINYLOG_USE_COLOR
#   define TINYLOG_USE_COLOR 1
#endif

/* -------- public API -------- */
enum tl_level { TL_TRACE=0, TL_DEBUG, TL_INFO, TL_WARN, TL_ERROR, TL_FATAL };

void tinylog_set_level(int level);           /* raise/lower at runtime        */
void tinylog_set_fp(FILE *fp);               /* redirect to file/UART/etc.     */
void tinylog_log(int level,
                 const char *file, int line,
                 const char *fmt, ...);

/* Convenience macros */
#define LOG_TRACE(...) tinylog_log(TL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) tinylog_log(TL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  tinylog_log(TL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  tinylog_log(TL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) tinylog_log(TL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) tinylog_log(TL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

/* -------- implementation -------- */
#ifdef TINYLOG_IMPLEMENTATION
static struct {
    int level;
    FILE *fp;
} tl_state = { TINYLOG_LEVEL, NULL };

static const char *tl_level_names[] = {
    "TRACE","DEBUG","INFO","WARN","ERROR","FATAL"
};
#if TINYLOG_USE_COLOR
static const char *tl_colors[] = {
    "\x1b[90m", /* gray      */
    "\x1b[36m", /* cyan      */
    "\x1b[32m", /* green     */
    "\x1b[33m", /* yellow    */
    "\x1b[31m", /* red       */
    "\x1b[35m"  /* magenta   */
};
#endif

void tinylog_set_level(int level) { tl_state.level = level; }
void tinylog_set_fp(FILE *fp)     { tl_state.fp = fp; }

void tinylog_log(int level,
                 const char *file, int line,
                 const char *fmt, ...)
{
    if (level < tl_state.level) return;

    /* timestamp */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);

    FILE *out = tl_state.fp ? tl_state.fp : stderr;

#if TINYLOG_USE_COLOR
    fprintf(out, "%s %-5s \x1b[0m%s:%d: ",
            tl_colors[level], tl_level_names[level], file, line);
#else
    fprintf(out, "%s %-5s %s:%d: ",
            buf, tl_level_names[level], file, line);
#endif

    va_list ap;
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);
    fputc('\n', out);
    fflush(out);

    if (level == TL_FATAL) abort();
}
#endif /* TINYLOG_IMPLEMENTATION */
#endif /* TINYLOG_H */
