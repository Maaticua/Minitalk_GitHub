/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macaruan <macaruan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:02:57 by macaruan          #+#    #+#             */
/*   Updated: 2025/04/25 13:45:31 by macaruan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

void	ft_mailbox(int sig)
{
	if (sig == SIGUSR1)
		g_ack_received = 1;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack_received)
			usleep(10);
		i--;
	}
}

int	main(int ac, char **av)
{
	int	PID;
	int	i;

	if (ac != 3)
	{
		ft_printf("Error wrong format\n");
		return (1);
	}
	signal(SIGUSR1, ft_mailbox);
	PID = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
		send_char(PID, av[2][i]);
		i++;
	}
	send_char(PID, '\0');
	return (0);
}
