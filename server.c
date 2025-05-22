/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macaruan <macaruan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:17:28 by macaruan          #+#    #+#             */
/*   Updated: 2025/05/22 17:58:45 by macaruan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_clear_msg(void)
{
	static char	*msg = NULL;

	if (msg)
	{
		free(msg);
		msg = NULL;
	}
}

void	ft_mess(char c)
{
	static char	*msg = NULL;
	char		*temp;
	char		c_2[2];

	c_2[0] = c;
	c_2[1] = '\0';
	if (msg == NULL)
		msg = ft_strdup(c_2);
	else
	{
		temp = ft_strjoin(msg, c_2);
		free(msg);
		msg = temp;
	}
	if (c == '\0')
	{
		ft_printf(YELLOW "message :");
		ft_printf(MAGENTA "%s\n" RESET, msg);
		free(msg);
		msg = NULL;
	}
}

void	handle_sig(int signal, siginfo_t *info, void *context)
{
	static pid_t	last_pid = 0;
	static int		bit = 0;
	static char		c = 0;

	(void)context;
	if (last_pid != info->si_pid)
	{
		c = 0;
		bit = 0;
		ft_clear_msg();
	}
	last_pid = info->si_pid;
	if (signal == SIGUSR2)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_mess(c);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sig;
	pid_t				pid;

	pid = getpid();
	ft_printf(GREEN "PID du serv: %d\n" RESET, pid);
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_sigaction = &handle_sig;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
