/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:55:59 by mrabat            #+#    #+#             */
/*   Updated: 2023/11/30 13:23:33 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_fork(t_prog *myprog, int i)
{
	if (myprog->nop - 1 == i)
		myprog->philous[i].pilo_fork_r = &myprog->philous[0].pilo_myfork_l;
	else
		myprog->philous[i].pilo_fork_r = &myprog->philous[i + 1].pilo_myfork_l;
}

int	ft_philo_init(t_prog *myprog)
{
	int	i;

	myprog->start_time = ft_get_timestamp();
	i = 0;
	while (myprog->nop > i)
		pthread_mutex_init(&(myprog->philous[i++].pilo_myfork_l), NULL);
	i = -1;
	while (myprog->nop > ++i)
	{
		myprog->philous[i].pilo_num = i + 1;
		myprog->philous[i].pilo_last_e = 0;
		myprog->philous[i].pilo_fork_r = NULL;
		myprog->philous[i].pilo_info = myprog;
		myprog->philous[i].m_count = 0;
		ft_init_fork(myprog, i);
		if (pthread_create(&myprog->philous[i].pilo_thread, NULL, \
				&ft_philo_life, &(myprog->philous[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < myprog->nop)
		if (pthread_join(myprog->philous[i].pilo_thread, NULL) != 0)
			return (-1);
	return (0);
}

int	ft_is_number(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_var_init(t_prog *myprog, char **av)
{
	if (av[5] && av[5] == 0)
		return (1);
	if (ft_is_number(av))
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	pthread_mutex_init(&myprog->mx_write, NULL);
	pthread_mutex_init(&myprog->mx_stop, NULL);
	pthread_mutex_init(&myprog->mx_eat, NULL);
	pthread_mutex_init(&myprog->mx_dead, NULL);
	myprog->prog_end = 0;
	myprog->philo_eat = 0;
	myprog->nop = ft_atoi(av[1]);
	myprog->ttd = ft_atoi(av[2]);
	myprog->tte = ft_atoi(av[3]);
	myprog->tts = ft_atoi(av[4]);
	myprog->nb_eat = -1;
	myprog->philous = malloc(sizeof(t_pilo) * myprog->nop);
	if (myprog->philous == NULL)
		return (2);
	if (av[5])
		myprog->nb_eat = ft_atoi(av[5]);
	return (0);
}
