/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:25:45 by linyao            #+#    #+#             */
/*   Updated: 2024/07/01 16:37:11 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_length_hex(unsigned int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_puthex_suf(unsigned int n, char c)
{
	char	*base;
	int		len;

	len = 0;
	if (n == 0)
		return (ft_putchar_suf('0'));
	else
	{
		if (c == 'x')
			base = "0123456789abcdef";
		else
			base = "0123456789ABCDEF";
		if (n >= 16)
		{
			ft_puthex_suf(n / 16, c);
			ft_puthex_suf(n % 16, c);
		}
		else
			ft_putchar_suf(base[n]);
	}
	len = ft_length_hex(n);
	return (len);
}

void	ft_putptr_rec(unsigned long long addr, char *base)
{
	if (addr >= 16)
	{
		ft_putptr_rec(addr / 16, base);
		ft_putptr_rec(addr % 16, base);
	}
	else
		ft_putchar_suf(base[addr]);
}

int	ft_length_ptr(unsigned long long addr)
{
	int	len;

	len = 0;
	while (addr > 0)
	{
		addr /= 16;
		len++;
	}
	return (len);
}

int	ft_putptr_suf(void *ptr)
{
	int					len;
	char				*base;
	unsigned long long	addr;

	addr = (unsigned long long)ptr;
	len = 0;
	if (!addr)
		return (write(1, "(nil)", 5));
	base = "0123456789abcdef";
	len += ft_putstr_suf("0x");
	if (addr == 0)
		len += ft_putchar_suf('0');
	else
	{
		ft_putptr_rec(addr, base);
		len += ft_length_ptr(addr);
	}
	return (len);
}
