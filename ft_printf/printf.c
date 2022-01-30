#include <stdarg.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

void	ft_putnbr(int num, int *res)
{
	if (num == -2147483648)
	{
		*res += write(1, "-2147483648", 11);
		return ;
	}
	if (num < 0)
	{
		*res += write(1, "-", 1);
		num = -num;
	}
	if (num > 9)
		ft_putnbr(num / 10, res);
	num = (num % 10) + '0';
	*res += (int) write(1, &num, 1); 
}

void	ft_putnbr_hex(unsigned int num, int *res)
{
	char *hex = "0123456789abcdef";

	if (num > 15)
		ft_putnbr_hex(num / 16, res);
	num = hex[num % 16];
	*res += (int) write(1, &num, 1); 
}

//%s,%d,%x
int	ft_printf(const char *format, ...)
{
	va_list ap;
	int	i;
	int	res;
	char *s;
	int	d;
	unsigned int x;


	va_start(ap, format);

	res = 0;
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			++i;
			if (format[i] == 's')
			{
				s = va_arg(ap, char *);
				if (s == NULL)
					res += write(1, "(null)", 6);
				else
					res += write(1, s, ft_strlen(s));
			}
			if (format[i] == 'd')
			{
				d = va_arg(ap, int);
				ft_putnbr(d, &res);
			}
			if (format[i] == 'x')
			{
				x = va_arg(ap, unsigned int);
				ft_putnbr_hex(x, &res);
			}
		}
		else
			res += write(1, &format[i], 1);
		++i;
	}
	va_end(ap);
	return (res);
}
int main(int ac, char **av)
{
	char *hello = "hello";
	int	forty_two = 42;
	int	max_int = 2147483647;
	int	min_int = -2147483648;

	printf("\n\ns flag\n");
	printf("\t\t-real(%d)\n", printf("s:%s", hello));
	printf("\t\t-mine(%d)\n", ft_printf("s:%s", hello));
	printf("\t\t-real(%d)\n", printf("s:%s", NULL));
	printf("\t\t-mine(%d)\n", ft_printf("s:%s", NULL));

	printf("\n\nd flag\n");
	printf("\t\t-real(%d)\n", printf("d:%d", forty_two));
	printf("\t\t-mine(%d)\n", ft_printf("d:%d", forty_two));
	printf("\t\t-real(%d)\n", printf("d:%d", -forty_two));
	printf("\t\t-mine(%d)\n", ft_printf("d:%d", -forty_two));
	printf("\t\t-real(%d)\n", printf("d:%d", max_int));
	printf("\t\t-mine(%d)\n", ft_printf("d:%d", max_int));
	printf("\t\t-real(%d)\n", printf("d:%d", min_int));
	printf("\t\t-mine(%d)\n", ft_printf("d:%d", min_int));

	printf("\n\nx flag\n");
	printf("\t\t-real(%d)\n", printf("x:%x", forty_two));
	printf("\t\t-mine(%d)\n", ft_printf("x:%x", forty_two));
	printf("\t\t-real(%d)\n", printf("x:%x", -forty_two));
	printf("\t\t-mine(%d)\n", ft_printf("x:%x", -forty_two));

	//multi
	printf("\n\nmulti flag\n");
	printf("\t\t-real(%d)\n", printf("s:%s d:%d x:%x", hello, forty_two, -forty_two));
	printf("\t\t-mine(%d)\n", ft_printf("s:%s d:%d x:%x", hello, forty_two, -forty_two));
	return (0);
}
