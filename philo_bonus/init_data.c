/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:52:27 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 14:23:52 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res < 0)
			return (-1);
	}
	if (str[i] != 0)
		return (-1);
	return (res);
}

void	init_data_2(t_philo *p, pid_t **p_id)
{
	while (++p->i < p->n_philo)
		(*p_id)[p->i] = 0;
	p->i = -1;
}

void	init_data(int argc, char **argv, t_philo *p, pid_t **p_id)
{
	p->n_philo = ft_atoi(argv[1]);
	p->t_2die = ft_atoi(argv[2]);
	p->t_2eat = ft_atoi(argv[3]);
	p->t_2sleep = ft_atoi(argv[4]);
	p->n_m_eat = 0;
	p->eating = 0;
	p->stop = 0;
	p->died = 0;
	p->meal_cnt = 0;
	p->i = -1;
	if (argc != 4)
		p->n_m_eat = ft_atoi(argv[5]);
	if (p->n_philo <= 0 || p->t_2die <= 0 || p->t_2eat <= 0 \
	|| p->t_2sleep <= 0 || p->n_m_eat < 0)
		ft_exit("Error: wrong arguments", -1);
	sem_unlink("/printf_sem");
	sem_unlink("/forks_sem");
	p->printf_sem = sem_open("/printf_sem", O_CREAT, 0644, 1);
	p->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, p->n_philo);
	if (p->printf_sem <= 0 || p->forks_sem <= 0)
		ft_exit("Error: create semaphores", -1);
	*p_id = (pid_t *)malloc(sizeof(pid_t) * p->n_philo);
	if (!(*p_id))
		ft_exit("Error: malloc pid_t", -1);
	init_data_2(p, p_id);
}
