/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:37:20 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/15 18:32:16 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

void	activity_time(t_config *config, int m_sec)
{
	long int	current_time;

	// (void)(config);
	current_time = get_time();
	// while (1)
	while (!config->game_over)
	{
		if (get_time() > current_time + m_sec)
			return ;
		//Is this needed ?!
		usleep(600);
	}
}

void	phil_eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->p_fork);
	print_activity(phil, FORK);
	//print_activity grab fork
	pthread_mutex_lock(&phil->next->p_fork);
	//print_activity grab fork
	print_activity(phil, FORK);
	//print_activity eat
	print_activity(phil, EAT);
	phil->t_eaten++;
	phil->die = get_time() + phil->config->time_to_die;
	activity_time(phil->config, phil->config->time_to_eat);
	pthread_mutex_unlock(&phil->next->p_fork);
	pthread_mutex_unlock(&phil->p_fork);
}

void	phil_sleep(t_phil *phil)
{
	//print_activity sleep
	print_activity(phil, SLEEP);
	activity_time(phil->config, phil->config->time_to_sleep);
}

void	phil_think(t_phil *phil)
{
	//print_activity think
	print_activity(phil, THINK);
}

void	game_over(t_config *config)
{
	t_phil	*phil_pointer;
	t_phil	*kill_this_one;

	phil_pointer = config->last->next;
	pthread_mutex_destroy(&config->last->p_fork);
	pthread_join(config->last->thread, NULL);
	//detech them some there are not zobie
	while (phil_pointer != config->last)
	{
		pthread_join(phil_pointer->thread, NULL);
		phil_pointer = phil_pointer->next;
	}
	//go to the "first" one
	phil_pointer = phil_pointer->next;
	//check this one out as well;
	free(config->last);
	//kill them all;
	while (phil_pointer != config->last)
	{
		kill_this_one = phil_pointer;
		phil_pointer = phil_pointer->next;
		pthread_mutex_destroy(&kill_this_one->p_fork);
		free(kill_this_one);
	}
	pthread_mutex_destroy(&config->write_status);
}