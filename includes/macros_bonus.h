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
// # define N_SPRITES 100
# define FRAME_DELAY 16.6667

// Player

# define PLYR_DIR "WNSE"
# define M_SENS 0.0015
# define P1_SPEED 2.0
# define P1_ROT_SPEED 1.0

// Keys

# ifdef LINUX
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_SHIFT 65505
# elif defined(MACOS)
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_SHIFT 257
# endif

// MiniLibX Event Codes

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOTION_NOTIFY 6
# define EVENT_DESTROY_NOTIFY 17

// MiniLibX Event Masks

# define MASK_KEY_PRESS 1L<<0
# define MASK_KEY_RELEASE 1L<<1
# define MASK_POINTER_MOTION 1L<<6

// Textures

# define TEX_WIDTH 512
# define TEX_HEIGHT 512
# define W1N 0
# define W1S 1
# define W1W 2
# define W1E 3
# define S1 4
# define F1 5
# define N_TEX 6

// Sprites

# define FIRE 1
# define DOOR 2
# define FIRE_T 100
# define WALK_T 150
# define IDLE_T 300
# define N_FIRES 4
# define F_RADIUS 0.1

#endif
