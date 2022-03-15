/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:00:45 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/15 10:23:12 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	first_to_last(t_config *config)
{
	t_phil *temp_phil;

	temp_phil = config->last;
	while (temp_phil->next)
		temp_phil = temp_phil->next;
	temp_phil->next = config->last;
}

char	*get_action(t_action action)
{
	if (action == FORK)
		return ("has taken a fork");
	if (action == EAT)
		return ("is eating");
	if (action == SLEEP)
		return ("is sleeping");
	if (action == THINK)
		return ("is thinking");
	if (action == DEAD)
		return ("died");
	return (NULL);
}

void	print_activity(t_phil *phil, t_action action)
{
	pthread_mutex_lock(&phil->config->write_status);
	if (!phil->config->game_over)
		printf("%08ld: %ld %s\n", get_time() - phil->config->start_game,
			phil->id, get_action(action));
	if (action == DEAD)
	{
		phil->config->game_over = true;
		//is this neceserry ?!
		pthread_mutex_unlock(&phil->p_fork);
	}
	pthread_mutex_unlock(&phil->config->write_status);
}

void	check_ho_dies(t_config *config)
{
	t_phil	*phil;
	t_bool	done_eating;

	phil = config->last;
	done_eating = false;
	while (!config->game_over)
	{
		//why is this needed ?!
		if (phil == config->last && config->times_to_eat)
			done_eating = true;
		if (get_time() > phil->die)
		{
			print_activity(phil, DEAD);
			return ;
		}
		if (phil->t_eaten < config->times_to_eat)
			done_eating = false;
		//why is this needed ?!
		phil = phil->next;
		if (phil == config->last && done_eating)
		{
			config->game_over = true;
			return ;
		}
	}
}