/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:56:09 by mrabat            #+#    #+#             */
/*   Updated: 2023/11/29 19:26:40 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_check_death(void *phi)
{
	t_pilo	*philo;
	t_prog	*myprog;
	int		i;

	philo = (t_pilo *)phi;
	myprog = philo->pilo_info;
	while(!myprog->prog_end)
	{
		i = 0;
		while (myprog->nop > i)
		{
			ft_usleep(myprog->ttd);
			pthread_mutex_lock(&myprog->mx_eat);
			pthread_mutex_lock(&myprog->mx_stop);
			if (!ft_is_dead(philo[i], 0) && ft_get_timestamp() - \
				philo[i]->pilo_last_e >= (long)(myprog->ttd))
			{
				ft_print_state(philo[i], " died\n");
				ft_is_dead(philo[i], 1);
			}
			pthread_mutex_unlock(&myprog->mx_eat);
			pthread_mutex_unlock(&myprog->mx_stop);
		}
	}
	return (NULL);
}

int	ft_take_fork(t_pilo *philo)
{
	if (philo->pilo_num % 2)
		pthread_mutex_lock(&(philo->pilo_myfork_l));
	else
		pthread_mutex_lock((philo->pilo_fork_r));
	ft_print_state(philo, " has taken a fork\n");
	if (philo->pilo_info->nop == 1)
	{
		ft_usleep(philo->pilo_info->ttd * 2);
		pthread_mutex_unlock(&(philo->pilo_myfork_l));
		return (1);
	}
	if (philo->pilo_num % 2)
		pthread_mutex_lock((philo->pilo_fork_r));
	else
		pthread_mutex_lock(&(philo->pilo_myfork_l));
	ft_print_state(philo, " has taken a fork\n");
	return (0);
}

void	ft_philo_eat(t_pilo *philo)
{
	t_prog		*myprog;

	myprog = philo->pilo_info;
	ft_print_state(philo, " is eating\n");
	pthread_mutex_lock(&(myprog->mx_eat));
	philo->pilo_last_e = ft_get_timestamp();
	philo->m_count++;
	pthread_mutex_unlock(&(myprog->mx_eat));
	ft_usleep(myprog->tte);
	pthread_mutex_unlock((philo->pilo_fork_r));
	pthread_mutex_unlock(&(philo->pilo_myfork_l));
	if (philo->m_count != myprog->nb_eat)
	{
		ft_print_state(philo, " is sleeping\n");
		ft_usleep(myprog->tts);
		ft_print_state(philo, " is thinking\n");
	}
}

void	*ft_philo_life(void *phi)
{
	t_pilo		*philo;
	t_prog		*myprog;
	pthread_t	my_t;

	philo = (t_pilo *)phi;
	myprog = philo->pilo_info;
	while (!ft_is_dead(philo, 0))
	{
		pthread_create(&my_t, NULL, ft_check_death, phi);
		if (!ft_take_fork(philo))
			ft_philo_eat(philo);
		pthread_join(my_t, NULL);
		if (philo->m_count == myprog->nb_eat)
		{
			ft_set_i_full(philo);
			return (NULL);
		}
	}
	return (NULL);
}
