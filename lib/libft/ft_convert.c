/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:29:42 by linyao            #+#    #+#             */
/*   Updated: 2024/06/28 11:14:49 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putchar_suf(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_suf(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
		len += write(1, s++, 1);
	return (len);
}

int	ft_putnbr_suf(int n)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(n);
	len = ft_putstr_suf(str);
	free(str);
	return (len);
}

int	ft_putnbr_unsigned_suf(unsigned int n)
{
	int		len;

	len = 0;
	if (n == 0)
		len += ft_putchar_suf('0');
	else
	{
		if (n / 10 != 0)
			ft_putnbr_unsigned_suf(n / 10);
		ft_putchar_suf((n % 10) + '0');
		while (n > 0)
		{
			n /= 10;
			len++;
		}
	}
	return (len);
}
