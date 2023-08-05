/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthread.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:06:50 by mdekker       #+#    #+#                 */
/*   Updated: 2023/08/04 01:07:21 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTHREAD_H
# define PTHREAD_H

# include <pthread.h>

// create shorthands for pthread functions so they are not as long
# define PCREATE pthread_create
# define PDETATCH pthread_detach
# define PJOIN pthread_join
# define PEXIT pthread_exit
# define MINIT pthread_mutex_init
# define MDESTROY pthread_mutex_destroy
# define MLOCK pthread_mutex_lock
# define MUNLOCK pthread_mutex_unlock

#endif
