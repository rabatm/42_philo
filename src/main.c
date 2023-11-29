/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:56:06 by mrabat            #+#    #+#             */
/*   Updated: 2023/11/29 18:45:04 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy(t_prog *myprog)
{
	int	i;

	i = -1;
	while (++i < myprog->nop)
		pthread_mutex_destroy(&(myprog->philous[i].pilo_myfork_l));
	free(myprog->philous);
	pthread_mutex_destroy(&myprog->mx_write);
	pthread_mutex_destroy(&myprog->mx_stop);
	pthread_mutex_destroy(&myprog->mx_eat);
	pthread_mutex_destroy(&myprog->mx_dead);
}

int	main(int ac, char **av)
{
	t_prog	myprog;

	if (ac != 5 && ac != 6)
		return (0);
	if (ft_var_init(&myprog, av) == 1)
		return (0);
	ft_philo_init(&myprog);
	ft_destroy(&myprog);
}
