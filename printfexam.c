/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfexam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:56:50 by oel-ouar          #+#    #+#             */
/*   Updated: 2020/12/01 10:21:43 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct s_flags
{
    int width;
    int prec;
    int p;
}               t_flags;

int g_count;
int check;
va_list ap;
t_flags flags;

void	init_flags(void)
{
	flags.width = 0;
	flags.prec = 0;
	flags.p = 0;
	check = 0;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_count++;
}

int 	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int 	num(int n)
{
	int i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int 	ft_atoi(const char *s)
{
	long num;

	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - 48);
		s++;
	}
	return (num);
}

int		is_num(char c)
{
	if (c >= 48 && c < 58)
		return (1);
	return (0);
}

void    print_str()
{
    char *str;
    int spaces;
    int preci;
    int i;

    str = va_arg(ap, char*);
    if (!str)
        str = "(null)";
    preci = (flags.p && flags.prec <ft_strlen(str)) ? flags.prec : ft_strlen(str);
    spaces = flags.width - preci;
    i = 0;
    while (spaces > 0)
    {
        ft_putchar(' ');
        spaces--;
    }
    while (i < preci)
    {
        ft_putchar(str[i]);
        i++;
    }
}

void    ft_puthex(unsigned int n)
{   
    char *num ="0123456789abcdef";
    if (n < 16)
        ft_putchar(num[n]);
    else
    {
        ft_puthex(n / 16);
        ft_puthex(n % 16);
    }
}

void    print_hex()
{
    unsigned int x;
    int spaces;
    int preci;
    int i;
    x = va_arg(ap, unsigned int);
    preci = (flags.p > num(x) ? flags.width - num(x) : 0);
    spaces = (preci > 0) ? flags.width - preci : flags.width - num(x);
    i = -1;
    while (++i < spaces)
        ft_putchar(' ');
    i = -1;
    while (++i < preci)
        ft_putchar('0');
    ft_puthex(x);
}

void	ft_check(const char *s, int *i)
{
	if (is_num(s[*i]))
	{
		flags.width = ft_atoi(s + (*i));
		*i += num(flags.width);
	}
	if (s[*i] == '.')
	{
		flags.p = 1;
		(*i)++;
	}
	if (is_num(s[*i]))
	{
		flags.prec = ft_atoi(s + (*i));
		*i += num(flags.prec);
	}
	if (s[*i] == 'd')
		print_int();
	if (s[*i] == 's')
		print_str();
	else if (s[*i] == 'x')
		print_hex();
}

int     ft_printf(const char *s, ...)
{
    int i = 0;
    va_start(ap, s);
    g_count = 0;
    while (s[i])
    {
        init_flags();
        if (s[i] == '%')
        {
            i++;
            ft_check(s, &i);
        }
        else
            ft_putchar(s[i]);
        i++;
    }
    va_end(ap);
    return (g_count);
}

int main()
{
    ft_printf("%12.d|\n", 123);
    printf("%12.d", 123);
}