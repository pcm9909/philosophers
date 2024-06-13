#include "philosopher.h"

void ft_take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->resource->forks[philo->l_fork]);
    print_status(philo, FORK);
    pthread_mutex_lock(&philo->resource->forks[philo->r_fork]);
    print_status(philo, FORK);
}

void ft_drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->resource->forks[philo->l_fork]);
    pthread_mutex_unlock(&philo->resource->forks[philo->r_fork]);
}

void ft_eat(t_philo *philo)
{
    print_status(philo, EAT);
    usleep(philo->resource->time_eat * 1000);
    pthread_mutex_lock(&philo->resource->mutex_eat);
    philo->cnt_eat++;
    philo->time_last_eat = get_time();
    pthread_mutex_unlock(&philo->resource->mutex_eat);
}

void ft_sleep(t_philo *philo)
{
    print_status(philo, SLEEP);
    usleep(philo->resource->time_sleep * 1000);
}

void ft_think(t_philo *philo)
{
    print_status(philo, THINK);
}