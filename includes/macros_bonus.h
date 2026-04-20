/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:58:03 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/19 16:45:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_BONUS_H
# define MACROS_BONUS_H

// Screen & Map

# define WIDTH 1920
# define HEIGHT 1080
# define N_KEYS 65536
# define FRAME_DELAY 0.0333333333333

// Player

# define PLYR_DIR "WNSE"
# define M_SENS 0.0015
# define P1_SPEED 1.5
# define P1_ROT_SPEED 1.0
# define P1_TURNSP 0.013
# define P1_R 0.2

// Keys

# ifdef LINUX
#  include <X11/keysym.h>
#  define KEY_W 0x0077
#  define KEY_A 0x0061
#  define KEY_S 0x0073
#  define KEY_D 0x0064
#  define KEY_E 0x0065
#  define KEY_ESC 0xff1b
#  define KEY_SHIFT 0xffe1
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

# define MASK_KEY_PRESS 1
# define MASK_KEY_RELEASE 2
# define MASK_POINTER_MOTION 64

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
# define WALLS "1234"

// Sprites

# define FIRE 1
# define DOOR 2
# define FIRE_T 100
# define WALK_T 150
# define IDLE_T 300
# define N_FIRES 4
# define F_RADIUS 0.1
# define D_RADIUS 0.4

// Minimap

# define MINI_FACTOR 10
# define PLYR_FACTOR 7

#endif
