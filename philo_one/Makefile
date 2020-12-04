# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 12:09:13 by abourbou          #+#    #+#              #
#    Updated: 2020/12/04 15:50:05 by abourbou         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME				=	philo_one

#PATH
PATH_SRC			=	srcs

PATH_INC			=	include

#NAME OF FILES
SRC_NAME			=	tools.c init.c

INC_NAME			=	philo.h

#PATH + NAMES

SRC					=	$(addprefix $(PATH_SRC)/, $(SRC_NAME)) main.c

INC					=	$(addprefix $(PATH_INC)/, $(INC_NAME))

OBJ					= 	$(SRC:.c=.o)

#COMPILATION PARAMETERS

CC					=	gcc

CFLAGS				= -Wall -Werror -Wextra

#RULES

all					:	$(NAME)

$(NAME)				:	$(OBJ) $(INCLUDE)
						$(CC) -o $@ $(CFLAGS) $<

%.o					:	%.c . $(INCLUDE)
						$(CC) -c $< -I$(PATH_INC) -o $@ $(CFLAGS)
