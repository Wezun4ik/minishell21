/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:02:29 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/24 18:07:05 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static void	ft_recput(int n, int fd)
{
	if ((n > -10) && (n < 10))
		ft_putchar_fd((char)(ft_abs(n)) + '0', fd);
	else
	{
		ft_recput(n / 10, fd);
		ft_recput(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	ft_recput(n, fd);
}
