/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:27:31 by risattou          #+#    #+#             */
/*   Updated: 2024/11/25 00:47:24 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_len(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static int	ft_printr(unsigned int num, char *base, unsigned int len)
{
	int	count;

	count = 0;
	if (num >= len)
	{
		count += ft_printr(num / len, base, len);
		count += ft_printr(num % len, base, len);
	}
	else
		count += ft_putchar(base[num], 0);
	return (count);
}
static int ft_hash(char *base)
{
	int count ;
	count = 0;
	if(base[10] == 'a')
		count += ft_printstring("0x",0);
	else if(base[10] == 'A')
		count += ft_printstring("0X",0);
	return count;
}
static int	ft_zero(t_flag *flag)
{
	int	count;

	count = 0;
	while(flag &&flag->number > 0)
	{
		count += write(1,"0",1);
		flag->number--;
	}
	return count;
}

int	ft_printnumber(unsigned int nbr, char *base, t_flag *flag)
{
	int	count;

	count = 0;
	if(flag && flag->hash == 1 && nbr > 0)
			count += ft_hash(base);
	if(flag && flag->dash == 0 && flag->number > count + (ft_countnbr_base(nbr,ft_len(base))))
		{
			flag->number -= (ft_countnbr_base(nbr,ft_len(base))+count);
			if(flag->zero ==1)
				count += ft_zero(flag);
			else 
				count += ft_putchar(' ',flag);
		}
	count += ft_printr(nbr, base, ft_len(base));
	if(flag && flag->dash == 1  && flag->number > count)
		{
			flag->number -= count;
			count += ft_putchar(' ',flag);
		}
	
	return (count);
}
