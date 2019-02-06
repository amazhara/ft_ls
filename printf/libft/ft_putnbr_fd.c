/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:51:15 by amazhara          #+#    #+#             */
/*   Updated: 2018/11/02 14:56:50 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		if ((nb / -10) > 0)
			ft_putnbr_fd(nb / -10, fd);
		ft_putchar_fd((-(nb % 10) + '0'), fd);
	}
	else if ((nb / 10) > 0)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((nb + 48), fd);
}
