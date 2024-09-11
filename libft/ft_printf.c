/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:19:52 by linyao            #+#    #+#             */
/*   Updated: 2024/06/27 15:29:50 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_convert(va_list *ag, char c)
{
	int	tot_len;

	tot_len = 0;
	if (c == 'c')
		tot_len += ft_putchar_suf(va_arg(*ag, int));
	else if (c == 's')
		tot_len += ft_putstr_suf(va_arg(*ag, char *));
	else if (c == 'p')
		tot_len += ft_putptr_suf(va_arg(*ag, void *));
	else if (c == 'd' || c == 'i')
		tot_len += ft_putnbr_suf(va_arg(*ag, int));
	else if (c == 'u')
		tot_len += ft_putnbr_unsigned_suf(va_arg(*ag, unsigned int));
	else if (c == 'x' || c == 'X')
		tot_len += ft_puthex_suf(va_arg(*ag, unsigned int), c);
	else
		tot_len += ft_putchar_suf(c);
	return (tot_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;
	int		i;

	total_len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			total_len += ft_parse_convert(&args, format[i]);
		}
		else
			total_len += ft_putchar_suf(format[i]);
		i++;
	}
	va_end(args);
	return (total_len);
}
