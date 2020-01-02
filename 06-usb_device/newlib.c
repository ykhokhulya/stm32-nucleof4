/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2017 Yuriy Khokhulya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include <stm32f3xx.h>

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar() __attribute__((weak));

void _exit(int status)
{
    (void)status;

    while (1)
    {
    }
}

int _close(int file)
{
    (void)file;

    return -1;
}

int _execve(char* name, char** argv, char** env)
{
    (void)name;
    (void)argv;
    (void)env;

    errno = ENOMEM;
    return -1;
}

int _fork()
{
    errno = EAGAIN;
    return -1;
}

int _fstat(int file, struct stat* st)
{
    if (STDOUT_FILENO == file || STDIN_FILENO == file || STDERR_FILENO == file)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return -1;
}

int _getpid()
{
    return 1;
}

int _isatty(int file)
{
    if (file == STDOUT_FILENO || file == STDIN_FILENO || file == STDERR_FILENO)
    {
        return 1;
    }

    errno = EBADF;
    return -1;
}

int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;

    errno = EINVAL;
    return (-1);
}

int _link(char* old, char* new)
{
    (void)old;
    (void)new;

    errno = EMLINK;
    return -1;
}

int _lseek(int file, int offset, int whence)
{
    (void)offset;
    (void)whence;

    if (STDOUT_FILENO == file || STDERR_FILENO == file)
    {
        return 0;
    }

    errno = EBADF;
    return -1;
}

caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char* heap_end = &_ebss;

    char* prev_heap_end = heap_end;
    char* stack = (char*)__get_MSP();

    if (heap_end + incr > stack)
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

int _read(int file, char* buf, int len)
{
    (void)len;

    if (STDIN_FILENO != file)
    {
        errno = EBADF;
        return -1;
    }

    int ch = __io_getchar();
    *buf = ch;
    return (ch == -1) ? -1 : 1;
}

int _stat(const char* filepath, struct stat* st)
{
    (void)filepath;
    (void)st;

    errno = EACCES;
    return -1;
}

clock_t _times(struct tms* buf)
{
    (void)buf;

    errno = EACCES;
    return -1;
}

int _unlink(char* name)
{
    (void)name;

    errno = ENOENT;
    return -1;
}

int _wait(int* status)
{
    (void)status;

    errno = ECHILD;
    return -1;
}

int _write(int file, char* buf, int len)
{
    int i;

    if (file != STDOUT_FILENO && file != STDERR_FILENO)
    {
        errno = EBADF;
        return -1;
    }

    for (i = 0; i < len; i++)
    {
        __io_putchar(buf[i]);
    }
    return len;
}
