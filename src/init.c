#include <philosophers.h>

void	print_philo_status(t_philo *philo)
{
	printf("starve: %ld\n", philo->time_to_starve);
	printf("eat: %ld\n", philo->time_to_eat);
	printf("sleep: %ld\n", philo->time_to_sleep);
	printf("die: %ld\n", philo->time_to_die);
	printf("id: %d\n", philo->philo_id);
	printf("fork1 id: %d\n", philo->fork1_id);
	printf("fork2 id: %d\n", philo->fork2_id);
}

pthread_t	*init_th_id(char *argv[])
{
	pthread_t *th;

	th =  malloc(sizeof(pthread_t) * strtol(argv[1], NULL, 10));
	if (th == NULL)
	{
		exit(1);
	}
	return (th);
}

t_philo	*init_philo(char *argv[], pthread_mutex_t	*mutex)
{
	size_t	i;
	size_t	philo_num = strtol(argv[1], NULL, 10);
	t_philo	*philo;
	philo = malloc(sizeof(t_philo) * (philo_num + 1));
	i = 0;
	while (i < philo_num)
	{
		philo[i].time_to_starve = strtol(argv[2], NULL, 10);
		philo[i].time_to_eat = strtol(argv[3], NULL, 10);
		philo[i].time_to_sleep = strtol(argv[4], NULL, 10);
		philo[i].time_to_die = -1;
		philo[i].is_death = false;
		philo[i].philo_id = i;
		philo[i].philo_num = philo_num;
		philo[i].forks = mutex;
		if (i % 2 == 0)
		{
			philo[i].fork1_id = i;
			philo[i].fork2_id = (i + 1) % philo_num;
			philo[i].fork_lh = &mutex[philo[i].fork1_id];
			philo[i].fork_rh = &mutex[philo[i].fork2_id];
		}
		else
		{
			philo[i].fork1_id = (i + 1) % philo_num;
			philo[i].fork2_id = i;
			philo[i].fork_lh = &mutex[philo[i].fork1_id];
			philo[i].fork_rh = &mutex[philo[i].fork2_id];
		}
		i++;
	}
	philo[i].is_death = true;
	return (philo);
}

pthread_mutex_t	*init_fork(char *philonum)
{
	pthread_mutex_t	*mutex;
	int	len = atoi(philonum);

	mutex = malloc(sizeof(pthread_mutex_t) * len);

	int	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&mutex[i], NULL) == -1)
		{
			printf("mutex init failure!\n");
			exit(1);
		}
		i++;
	}
	return (mutex);
}

