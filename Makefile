# NAME		=	pipex

# SRCS_FILES	= 	${shell find ./srcs_man -name "*.c"}
# BONUS_FILES	= 	${shell find ./srcs_bonus -name "*.c"}

# SRCS_BONUS	= 	$(BONUS_FILES)
# OBJS_MAN	=	$(patsubst %.c,%.o,$(SRCS_BONUS))

# # SRCS_BONUS	= 	$(BONUS_FILES)
# # OBJS_BONUS	=	$(patsubst %.c,%.o,$(SRCS_BONUS))

# LIB_DIR		=	libft
# HEADER		=	-I./include/pipex_bonus.h
# HEADER_B	=	-I./include/pipex_bonus.h

# CC			=	gcc
# CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g
# RM			=	rm -f


# all:		 $(LIB) $(NAME)

# $(NAME):	$(OBJS_MAN) include/pipex_bonus.h
# 			make -C libft
# 			@$(CC) $(CFLAGS) $(HEADER) $(LIB_DIR)/libft.a $(OBJS_MAN) -o $(NAME)
# 			@#clear

# bonus:		all

# %.o:		%.c libft/*.c
# 			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# clean:
# 			@make clean -C $(LIB_DIR)
# 			$(RM) $(OBJS_MAN)
# 			$(RM) $(OBJS_BONUS)

# fclean:		clean
# 			@make fclean -C $(LIB_DIR)
# 			$(RM) $(NAME)

# re:			fclean all

# .PHONY:		all clean fclean re bonus


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichan <yichan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 16:27:06 by yichan            #+#    #+#              #
#    Updated: 2023/04/27 16:51:50 by yichan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex
CC	 		= gcc
RM	 		= rm -rf
CFLAGS		= -Wall -Werror -Wextra -g3 
LIBFT		= libft
# CFLAGS		+= -pthread
CFLAGS		+= 	-g #-fsanitize=address
INCLUDE 	= ./include
SRC_PATH 	= ./srcs_bonus
OBJ_PATH	= ./obj

SRCS	= $(wildcard $(SRC_PATH)/*.c )
# OBJS	= $(patsubst %.c,$(OBJ_PATH)/%.o,$(notdir $(SRCS)))
OBJS 	= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(MAKE) -C $(LIBFT)
			$(CC) $(CFLAGS) $^ -I$(INCLUDE) -L$(LIBFT) -lft -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* $(INCLUDE)/*.h ./Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) -c -I$(INCLUDE) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:	
					$(MAKE) -C $(LIBFT) clean
					$(RM) $(OBJ_PATH)


fclean			:	clean
					$(MAKE) -C $(LIBFT) fclean
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re