#include "../includes/philo.h"

int	ft_get_is_dead(t_pilo *philo, int nb)
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

void	ft_print_state(t_pilo *myphilo, char *str)
{
	long int	time;
	t_prog		*myprog;
	
	myprog = myphilo->pilo_info;
	pthread_mutex_lock(&(myprog->mx_write));
	time = ft_get_timestamp() - myprog->start_time;
	if (!myprog->prog_end && time >= 0 \
			&& time <= INT_MAX && !ft_get_is_dead(myphilo, 0))
		printf("%lld %d %s", ft_get_timestamp() - myprog->start_time, myphilo->pilo_num, str);
	pthread_mutex_unlock(&(myprog->mx_write));
}
