/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macaruan <macaruan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:02:57 by macaruan          #+#    #+#             */
/*   Updated: 2025/05/21 18:19:52 by macaruan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/inc/libft.h"

static volatile __sig_atomic_t	g_recu = 0;

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_recu = 1;
	else if (sig == SIGUSR2)
		exit(0);
}

void	ft_print_bit(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
		{
			kill(pid, SIGUSR1);
		}
		if (((c >> i) & 1) == 1)
		{
			kill(pid, SIGUSR2);
		}
		g_recu = 0;
		while (!g_recu)
		{
			usleep(10);
		}
		i--;
	}
}

void	ft_print_str(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_print_bit(str[i], pid);
		i++;
	}
	ft_print_bit(0, pid);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf(RED "Wrong argument :p" RESET);
		exit(0);
	}
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_printf(RED "INVALID PID" RESET);
		exit(0);
	}
	ft_print_str(av[2], pid);

}

