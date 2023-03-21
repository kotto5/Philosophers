/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 23:28:13 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	put_fork(t_philo *philo, t_fork *fork);
static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had);

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;
	int		ans;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	update_wish_status(philo->wish, LET_TRY_TO_TAKE_FORKS, NONE, NONE, philo->philo_id);
	// 手付けていいですか と じっさいfork とる時二回。
	while (1)
	{
		ans = is_wish_come(philo->wish, philo->philo_id);
		if (ans == LET_OK)
			break;
		else if (ans == LET_YOU_ARE_ALREADY_DEAD)
			return (ERROR);
	}
	if (take_fork(philo, first, NULL) == ERROR)
		return (ERROR);
	if (take_fork(philo, second, first) == ERROR)
	{
		put_fork(philo, first);
		return (ERROR);
	}
	return (0);
}

static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
{
	struct timeval t1;
	long sec_milli;
	int				ret;
	int				answer;

	while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
	{
		;
	}
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, fork->fork_id, philo->philo_id);
	while (1)
	{
		answer = is_wish_come(philo->wish, philo->philo_id);
		if (answer == LET_YOU_ARE_ALREADY_DEAD)
		{
			put_fork(philo, fork);
			return (ERROR);
		}
		if (answer == LET_OK)
			return (SUCCESS);
	}
}

// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long sec_milli;
// 	int				ret;

// 	while (1)
// 	{
// 		if (ft_pthread_mutex_trylock(&fork->fork) == SUCCESS)
// 			break;
// 		if (had)
// 		{
// 			if (put_fork(philo, had) == ERROR)
// 				return (ERROR);
// 			// usleep(100);
// 			return (take_forks(philo));
// 		}
// 	}
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, NONE);
// 	int	answer;
// 	while (1)
// 	{
// 		answer = is_wish_come(philo->wish);
// 		if (answer == LET_OK)
// 			break;
// 		else if (answer == LET_YOU_ARE_ALREADY_DEAD)
// 			return (ERROR);
// 		// ulseep(10);
// 	}
// 	ret = print_time(philo->philo_id, sec_milli, LET_TAKE_A_FORK, fork->fork_id);
// 	return (ret);
// }

int	put_forks(t_philo *philo)
{
	// t_fork	*first;
	// t_fork	*second;

	// first = philo->forks[FIRST];
	// second = philo->forks[SECOND];
	// if (put_fork(philo, first) == ERROR)
	// 	return (ERROR);
	// if (put_fork(philo, second) == ERROR)
	// 	return (ERROR);
	if (put_fork(philo, philo->forks[FIRST]) == ERROR)
		return (ERROR);
	if (put_fork(philo, philo->forks[SECOND]) == ERROR)
		return (ERROR);	
	return (SUCCESS);
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	// struct timeval t1;//
	// long sec_milli;//
	// int	ret;

	// gettimeofday(&t1, NULL);//
	// sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;//

	// if (check_am_i_dead(philo) == true)
	// {
	// 	pthread_mutex_unlock(&fork->fork.stuff);
	// 	fork->fork.is_available = false;
	// 	return (ERROR);
	// }

	// ret = print_time(philo->philo_id, sec_milli, LET_PUT_OFF_A_FORK, fork->fork_id);//
	return (ft_pthread_mutex_unlock(&fork->fork));
}

// static int	put_fork(t_philo *philo, t_fork *fork)
// {
// 	int	ret;

// 	// if (check_am_i_dead(philo) == true)
// 	// {
// 	// 	pthread_mutex_unlock(&fork->fork.stuff);
// 	// 	fork->fork.is_available = false;
// 	// 	return (ERROR);
// 	// }
// 	fork->fork.is_available = true;
// 	if (pthread_mutex_unlock(&fork->fork.stuff))
// 		return (ERROR);
// 	return (SUCCESS);
// }
