#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/* Skip whitespace in the input stream.
 * Returns 1 on success, -1 on EOF/error.
 */
int match_space(FILE *f)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1;
    while (isspace(ch))
        ch = fgetc(f);
    if (ch != EOF)
        ungetc(ch, f);
    return 1;
}

/* Match a literal character from format with input.
 * Returns 1 on success, -1 on mismatch/EOF.
 */
int match_char(FILE *f, char c)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1;
    if (ch == c)
        return 1;
    if(ch != EOF)
        ungetc(ch, f);
    return -1;
}

/* %c : read exactly one character (including whitespace).
 * ap is pointer to va_list so we advance the caller's va_list.
 */
int scan_char(FILE *f, va_list *ap)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1;
    char *dst = va_arg(*ap, char *);
    *dst = (char)ch;
    return 1;
}

/* %d : read signed decimal integer (skip leading whitespace).
 * ap is pointer to va_list.
 */
int scan_int(FILE *f, va_list *ap)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1;

    /* skip initial whitespace */
    while (isspace(ch))
    {
        ch = fgetc(f);
        if (ch == EOF)
            return -1;
    }

    int sign = 1;
    if (ch == '+' || ch == '-')
    {
        if (ch == '-')
            sign = -1;
        ch = fgetc(f);
        if (ch == EOF)
            return -1;
    }

    if (!isdigit(ch))
    {
        if (ch != EOF)
            ungetc(ch, f);
        return -1;
    }

    long val = 0;
    while (isdigit(ch))
    {
        val = val * 10 + (ch - '0');
        ch = fgetc(f);
    }

    if (ch != EOF)
        ungetc(ch, f);

    int *dst = va_arg(*ap, int *);
    *dst = (int)(val * sign);
    return 1;
}

/* %s : read non-whitespace sequence into buffer (no width checking,
 * caller must provide sufficiently large buffer).
 * ap is pointer to va_list.
 */
int scan_string(FILE *f, va_list *ap)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1;

    /* skip leading whitespace */
    while (isspace(ch))
    {
        ch = fgetc(f);
        if (ch == EOF)
            return -1;
    }

    char *dst = va_arg(*ap, char *);
    int i = 0;
    while (ch != EOF && !isspace(ch))
    {
        dst[i++] = (char)ch;
        ch = fgetc(f);
    }
    dst[i] = '\0';

    if (ch != EOF)
        ungetc(ch, f);

    return (i > 0) ? 1 : -1;
}

/* Dispatcher: look at conversion char and call appropriate scanner.
 * Note: format is a pointer-to-pointer so caller controls advancing.
 * ap is pointer to va_list so scans consume shared va_list.
 */
int match_conv(FILE *f, const char **format, va_list *ap)
{
    char conv = **format;
    if (conv == 'c')
        return scan_char(f, ap);
    if (conv == 'd')
        return scan_int(f, ap);
    if (conv == 's')
        return scan_string(f, ap);
    return -1;
}

/* Core vfscanf-like implementation using stdin/file f. */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;
    /* We'll pass pointer to ap into match_conv/scan_* so that
       va_arg advances are shared among calls. */
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0')
                break;
            /* For %d and %s we do not additionally call match_space here,
               because scan_int/scan_string handle leading whitespace themselves.
               (This keeps behavior consistent and avoids double-skipping.) */
            if (match_conv(f, &format, &ap) != 1)
                break;
            nconv++;
        }
        else if (isspace((unsigned char)*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else
        {
            if (match_char(f, *format) != 1)
                break;
        }
        format++;
    }

    if (ferror(f))
        return EOF;
    return nconv;
}

/* Public API */
int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}