# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 17:16:12 by eelroy            #+#    #+#              #
#    Updated: 2022/06/05 18:42:23 by eelroy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c init_data.c utils.c 

OBJ_DIR			= obj/

OBJS			= $(addprefix ${OBJ_DIR}, ${SRCS:.c=.o})

DEPS			= $(addprefix ${OBJ_DIR}, ${SRCS:.c=.d})

NAME			= philo

HEADERS			= includes.h

CC				= gcc

FLAGS			= -Wall -Werror -Wextra -O3 -MMD

${OBJ_DIR}%.o: 	%.c
				${CC} ${FLAGS} -c $< -o $@

all:			${OBJ_DIR} ${NAME}

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${NAME}:		${OBJS} ${HEADERS}
				${CC} ${OBJS} -o ${NAME}

clean:
				@rm -rf ${OBJ_DIR}
				@echo "Clean: Done."

fclean:			clean
				@rm -f ${NAME}
				@echo "Fclean: Done."

re:				fclean all

.PHONY:			all FORCE clean fclean re

-include 		${DEPS}
