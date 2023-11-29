#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef	pthread_mutex_t	t_mtx;
typedef struct s_prog 	t_prog;

typedef struct s_pilo
{
	int			pilo_num;
	int			m_count;
	int			pilo_is_eating;
	pthread_t	pilo_thread;
	long int	pilo_last_e;
	t_prog		*pilo_info;
	t_mtx		*pilo_fork_r;
	t_mtx		pilo_myfork_l;
}		t_pilo;

typedef struct s_prog
{
	int			philo_eat;
	int			nop;
	int			ttd;
	int			tte;
	int			tts;
	int			nb_eat;
	int			prog_end;
	long int	start_time;
	t_pilo		*philous;
	t_mtx		mx_write;
	t_mtx		mx_stop;
	t_mtx		mx_eat;
	t_mtx		mx_dead;
}		t_prog;

int			ft_var_init(t_prog *data, char **av);
int			ft_philo_init(t_prog *data);
void		*ft_philo_life(void *phi);
void		ft_set_i_full(t_pilo *philo);
void		ft_print_state(t_pilo *myphilo, char *str);
int			ft_is_dead(t_pilo *philo, int nb);
int			ft_isdigit(int character);
int			ft_atoi(const char *str);
void		ft_usleep(int ms);
long long	ft_get_timestamp(void);

#endif
