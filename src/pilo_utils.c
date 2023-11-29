/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pilo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:56:13 by mrabat            #+#    #+#             */
/*   Updated: 2023/11/29 18:53:01 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_dead(t_pilo *philo, int nb)
{
	t_prog		*myprog;

	myprog = philo->pilo_info;
	pthread_mutex_lock(&myprog->mx_dead);
	if (nb)
		myprog->prog_end = 1;
	if (myprog->prog_end)
	{
		pthread_mutex_unlock(&myprog->mx_dead);
		return (1);
	}
	pthread_mutex_unlock(&myprog->mx_dead);
	return (0);
}

long long	ft_get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_get_timestamp();
	while (ft_get_timestamp() - time < ms)
		usleep(ms / 10);
}

void	ft_set_i_full(t_pilo *philo)
{
	t_prog		*myprog;

	myprog = philo->pilo_info;
	pthread_mutex_lock(&myprog->mx_stop);
	if (++myprog->philo_eat == myprog->nop)
	{
		pthread_mutex_unlock(&myprog->mx_stop);
		ft_is_dead(philo, 2);
	}
	pthread_mutex_unlock(&myprog->mx_stop);
}

void	ft_print_state(t_pilo *philo, char *str)
{
	int			end_check;
	long int	time;
	t_prog		*myprog;

	myprog = philo->pilo_info;
	pthread_mutex_lock(&(myprog->mx_write));
	time = ft_get_timestamp() - myprog->start_time;
	pthread_mutex_lock(&(myprog->mx_dead));
	end_check = myprog->prog_end;
	pthread_mutex_unlock(&(myprog->mx_dead));
	if (!end_check && time >= 0 \
			&& time <= INT_MAX && !ft_is_dead(philo, 0))
		printf("%lld %d %s", ft_get_timestamp()
			- myprog->start_time, philo->pilo_num, str);
	pthread_mutex_unlock(&(myprog->mx_write));
}
