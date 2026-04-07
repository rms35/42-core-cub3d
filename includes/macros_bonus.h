/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:58:03 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/21 11:01:34 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_BONUS_H
# define MACROS_BONUS_H

// Screen & Map

# define WIDTH 1920
# define HEIGHT 1080
# define N_KEYS 65536
# define N_SPRITES 100
# define FRAME_DELAY 16.6667

// Player

# define PLYR_DIR "WNSE"
# define M_SENS 0.0015
# define P1_SPEED 2.0
# define P1_ROT_SPEED 1.0

// Textures

# define TEX_WIDTH 512
# define TEX_HEIGHT 512
# define N_TEX 6
# define W1N 0
# define W1S 1
# define W1W 2
# define W1E 3
# define S1 4
# define F1 5

// Sprites

# define FIRE 1
# define FIRE_T 100
# define WALK_T 150
# define IDLE_T 300
# define N_FIRES 4
# define F_RADIUS 0.1

#endif
