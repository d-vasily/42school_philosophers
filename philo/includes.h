/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:53:03 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 12:04:35 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;

	int				t_2die;
	int				t_2eat;
	int				t_2sleep;

	int				n_philo;
	int				n_m_eat;
	int				stop;

	long long int	t_start;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	t_data			*d;

	int				meal_cnt;
	int				i;
	int				eating;

	pthread_t		thread;
	long long int	t_last_meal;
}	t_philo;

void			logger(t_philo *p, char *s);
void			destroy_mutex(t_philo *p);
int				ft_atoi(const char *str);
int				ft_exit(t_philo *p, char *s, int code);
long long int	find_time(void);

int				init_data(int argc, char **argv, t_data *d, t_philo **tmp);

#endif
