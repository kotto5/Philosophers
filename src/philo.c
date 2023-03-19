/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 15:33:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i], NULL, &routine, &philos[i]) != 0)
		{
			printf("[FOOOOOOOOOOOO!!!]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	threads_join(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
		{
			printf("[NOOOOOOOOOOON!!!!!!!!]\n");
			return (2);
		}
		i++;
	}
	return (0);
}

int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_shere		shere;

	if (parse_argment(argc, argv) == 1)
		return (1);
	shere.philo_num = atoi(argv[1]);
	shere.dead_info = init_t_dead(shere.philo_num);
	shere.wishs = init_wishs(shere.philo_num);
	philos = init_philo(argv, init_fork(shere.philo_num), &shere);
	th_id = init_th_id(argv);

	if (threads_create(philos, th_id, shere.philo_num) == 1)
		return (1);
	monitor_philos_death(&shere);
	if (threads_join(philos, th_id, shere.philo_num) == 2)
		return (2);
	return (0);
	printf("%p\n", (philos[0].wish));
	printf("%p\n", (&shere.wishs[0]));
}

	// int i = 0;
	// while (i < shere.philo_num)
	// {
	// 	printf("%ld\n", (philos[i].time_to_die));
	// 	printf("%ld\n", (*philos[i].dead_info->time_to_die));
	// 	printf("%ld\n", (*shere.dead_info[i].time_to_die));
	// 	philos[i].time_to_die = 500;
	// 	printf("%ld\n", (philos[i].time_to_die));
	// 	printf("%ld\n", (*philos[i].dead_info->time_to_die));
	// 	printf("%ld\n", (*shere.dead_info[i].time_to_die));
	// 	printf("--  --\n");

	// 	i++;
	// }
