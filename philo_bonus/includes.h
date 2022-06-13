/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:53:03 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 15:06:13 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				i;
	int				meal_cnt;

	int				t_2die;
	int				t_2eat;
	int				t_2sleep;

	int				n_philo;
	int				n_m_eat;

	int				eating;
	int				stop;
	int				died;

	pthread_t		check;

	sem_t			*printf_sem;
	sem_t			*forks_sem;

	long long int	t_last_meal;
	long long int	t_start;
}	t_philo;

void			logger(t_philo *p, char *s);
int				ft_exit(char *s, int code);

long long int	find_time(void);
void			ft_usleep(long long int wait, t_philo *p);

void			init_data(int argc, char **argv, t_philo *p, pid_t **p_id);

#endif
