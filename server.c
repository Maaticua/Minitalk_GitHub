/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macaruan <macaruan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:17:28 by macaruan          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:24 by macaruan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit = 0;
	static pid_t			current_pid = 0;

	(void)context;

	if (current_pid != 0 && info->si_pid != current_pid)
		return ;

	if (current_pid == 0)
		current_pid = info->si_pid;

	if (sig == SIGUSR2)
		c |= (1 << (7 - bit));
	bit++;

	kill(info->si_pid, SIGUSR1);

	if (bit == 8)
	{
		if (c == '\0')
		{
			ft_printf("\n--fin de transmission--\n");
			current_pid = 0;
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("PID : %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
