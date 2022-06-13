/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:49:57 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 15:06:06 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	ft_philo(t_philo *p)
{
	while (1)
	{
		logger(p, "is thinking");
		sem_wait(p->forks_sem);
		logger(p, "has taken a fork");
		sem_wait(p->forks_sem);
		logger(p, "has taken a fork");
		p->t_last_meal = find_time();
		logger(p, "is eating");
		ft_usleep(p->t_2eat, p);
		sem_post(p->forks_sem);
		sem_post(p->forks_sem);
		p->meal_cnt += 1;
		logger(p, "is sleeping");
		ft_usleep(p->t_2sleep, p);
	}
}

void	*check_if_alive(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->stop)
	{
		if (!p->eating && find_time() - p->t_last_meal >= p->t_2die)
		{
			logger(p, "died");
			sem_wait(p->printf_sem);
			p->stop = 1;
			p->died = 1;
		}
		else if (p->n_m_eat != 0 && p->meal_cnt >= p->n_m_eat)
		{
			p->stop = 1;
		}
	}
	if (p->died)
		exit(1);
	else
		exit(0);
}

void	end_simulation(t_philo *p, pid_t *p_id)
{
	int		i;
	int		ok;

	i = -1;
	while (++i < p->n_philo)
	{
		waitpid(-1, &ok, 0);
		if (ok != 0)
		{
			i = -1;
			while (++i < p->n_philo)
			{
				if (p_id[i])
					kill(p_id[i], SIGKILL);
			}
			break ;
		}
	}
	sem_close(p->printf_sem);
	sem_close(p->forks_sem);
	sem_unlink("/printf_sem");
	sem_unlink("/fork_sem");
	free(p_id);
}

void	simulation(t_philo *p, pid_t *p_id)
{
	p->t_start = find_time();
	while (++p->i < p->n_philo)
	{
		p_id[p->i] = fork();
		if (p_id[p->i] == -1)
		{
			sem_wait(p->printf_sem);
			free(p_id);
			ft_exit("Error: create fork\n", -1);
		}
		else if (p_id[p->i] == 0)
		{
			p->t_last_meal = find_time();
			if (pthread_create(&p->check, NULL, check_if_alive, (void *)(p)) \
			|| pthread_detach(p->check))
			{
				sem_wait(p->printf_sem);
				ft_exit("Error: create thread\n", -1);
			}
			ft_philo(p);
		}
	}
	end_simulation(p, p_id);
}

int	main(int argc, char **argv)
{
	t_philo	p;
	pid_t	*p_id;

	if (argc < 5 || argc > 6)
		ft_exit("Error: wrong number of arguments", -1);
	init_data(argc - 1, argv, &p, &p_id);
	simulation(&p, p_id);
	return (0);
}
