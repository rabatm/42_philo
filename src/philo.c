#include "../includes/philo.h"

void	*ft_check_death(void *phi)
{
	t_pilo	*philo;
	t_prog		*myprog;

	philo = (t_pilo *)phi;
	myprog = philo->pilo_info;
	ft_usleep(myprog->ttd + 1);
	pthread_mutex_lock(&myprog->mx_eat);
	pthread_mutex_lock(&myprog->mx_stop);
	if (!ft_get_is_dead(philo, 0) && ft_get_timestamp() - \
			philo->pilo_last_e >= (long)(myprog->ttd))
	{
		pthread_mutex_unlock(&myprog->mx_eat);
		pthread_mutex_unlock(&myprog->mx_stop);
		ft_print_state(philo, " died\n");
		ft_get_is_dead(philo, 1);
	}
	pthread_mutex_unlock(&myprog->mx_eat);
	pthread_mutex_unlock(&myprog->mx_stop);
	return (NULL);
}

void	ft_take_fork(t_pilo *philo)
{
	pthread_mutex_lock(&(philo->pilo_myfork_l));
	ft_print_state(philo, " has taken a fork\n");
	if (philo->pilo_info->nop == 1)
	{
		ft_usleep(philo->pilo_info->ttd * 2);
		return ;
	}
	pthread_mutex_lock((philo->pilo_fork_r));
	ft_print_state(philo, " has taken a fork\n");
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
	ft_print_state(philo, " is sleeping\n");
	ft_usleep(myprog->tts);
	ft_print_state(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_pilo		*philo;
	t_prog		*myprog;
	pthread_t	my_t;

	philo = (t_pilo *)phi;
	myprog = philo->pilo_info;
	if (philo->pilo_num % 2 == 0)
		ft_usleep(myprog->tte / 10);
	while (!ft_get_is_dead(philo, 0))
	{
		if (philo->m_count == myprog->nb_eat)
		{
			pthread_mutex_lock(&myprog->mx_stop);
			if (++myprog->philo_eat == myprog->nop)
			{
				pthread_mutex_unlock(&myprog->mx_stop);
				ft_get_is_dead(philo, 2);
			}
			pthread_mutex_unlock(&myprog->mx_stop);
			return (NULL);
		}
		pthread_create(&my_t, NULL, ft_check_death, phi);
		ft_take_fork(philo);
		ft_philo_eat(philo);
		pthread_detach(my_t);
	}
	return (NULL);
}
