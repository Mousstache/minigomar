# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 00:22:02 by maheraul          #+#    #+#              #
#    Updated: 2023/08/29 22:09:16 by maheraul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFT			=	libft.a

PRINTF			=	libftprintf.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c \
					heredoc/heredoc.c \
					heredoc/here_doc2.c \
					builtin/builtin.c \
					builtin/export.c \
					builtin/unset.c \
					builtin/cd.c \
					builtin/env.c \
					builtin/echo.c \
					builtin/pwd.c \
					builtin/exit.c \
					builtin/exit_fork.c\
					exec/fill_cmd_struct.c \
					exec/minishell.c \
					exec/exec.c \
					exec/redirection.c \
					exec/redir_nofork.c \
					exec/signaux.c \
					free/free.c \
					utils/lst.c \
					utils/utils.c \
					parsing/env.c \
					parsing/syntax.c\
					parsing/parse.c \
					parsing/parse_input.c \
					parsing/strjoin.c \
					parsing/utils_env_2.c \
					parsing/utils_env.c \
					parsing/valid.c \
					parsing/count_expand.c \
					parsing/expand.c



OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

INC				=	-Iincludes -Ilibs/libft -Ilibs/ft_printf

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD			=	-Iincludes -lreadline

CC				=	cc

CFLAGS			=	-Iincludes -Ilibs/ft_printf -Ilibs/libft -g3 -Wall -Werror -Wextra

all				:	${NAME}

bonus			: ${NAME_BONUS}

$(NAME): $(DIR_OBJS) $(OBJS)
	@make -C libs/libft
	@make -C libs/ft_printf
	@mv libs/libft/libft.a .
	@mv libs/ft_printf/libftprintf.a .
	cc $(HEAD) $(OBJS) ${LIBFT} ${PRINTF} -o $(NAME)

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CFLAGS) $(INC) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/builtin
	mkdir -p objs/parsing
	mkdir -p objs/exec
	mkdir -p objs/free
	mkdir -p objs/utils
	mkdir -p objs/heredoc

clean			:
					make clean -C libs/libft
					make clean -C libs/ft_printf
					rm -rf ${OBJS} ${OBJS_BONUS} $(DIR_OBJS)

fclean			:	clean
					make fclean -C libs/libft
					make fclean -C libs/ft_printf
					rm -rf ${LIBFT}
					rm -rf ${PRINTF}
					rm -rf ${NAME}

re				:	fclean all

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.txt  --track-fds=yes    ./minishell

.PHONY			:	all clean fclean re bonus
