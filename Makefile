NAME		=	pipex

SRCS_FILES	= 	${shell find ./srcs_man -name "*.c"}
BONUS_FILES	= 	${shell find ./srcs_bonus -name "*.c"}

SRCS_BONUS	= 	$(BONUS_FILES)
OBJS_MAN	=	$(patsubst %.c,%.o,$(SRCS_BONUS))

# SRCS_BONUS	= 	$(BONUS_FILES)
# OBJS_BONUS	=	$(patsubst %.c,%.o,$(SRCS_BONUS))

LIB_DIR		=	libft
HEADER		=	-I./include/pipex_bonus.h
HEADER_B	=	-I./include/pipex_bonus.h

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g
RM			=	rm -f


all:		 $(LIB) $(NAME)

$(NAME):	$(OBJS_MAN) include/pipex_bonus.h
			make -C libft
			@$(CC) $(CFLAGS) $(HEADER) $(LIB_DIR)/libft.a $(OBJS_MAN) -o $(NAME)
			@#clear

bonus:		all

%.o:		%.c libft/*.c
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
			@make clean -C $(LIB_DIR)
			$(RM) $(OBJS_MAN)
			$(RM) $(OBJS_BONUS)

fclean:		clean
			@make fclean -C $(LIB_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus