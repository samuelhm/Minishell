/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:18:34 by linyao            #+#    #+#             */
/*   Updated: 2024/06/27 15:30:16 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_parse_converse(va_list *ag, char c);
int		ft_putchar_suf(char c);
int		ft_putstr_suf(char *s);
int		ft_putnbr_suf(int n);
int		ft_putnbr_unsigned_suf(unsigned int n);
int		ft_puthex_suf(unsigned int n, char c);
int		ft_length_hex(unsigned int n);
int		ft_putptr_suf(void *ptr);
void	ft_putptr_rec(unsigned long long addr, char *base);
int		ft_length_ptr(unsigned long long addr);

#endif
