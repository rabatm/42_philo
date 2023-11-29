#include "../includes/philo.h"

void	ft_destroy(t_prog *myprog)
{
	int	i;

	i = -1;
	while (++i < myprog->nop)
	{
		pthread_mutex_destroy(&myprog->philous[i].pilo_myfork_l);
		pthread_mutex_destroy(myprog->philous[i].pilo_fork_r);
	}
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
