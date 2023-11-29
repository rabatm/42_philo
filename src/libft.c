#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	atoi;
	int	signe;

	i = 0;
	atoi = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		signe *= -1; 
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] < '9')
	{
		atoi = atoi * 10 + str[i] - '0';
		i++;
	}
	return (atoi * signe);
}

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}
