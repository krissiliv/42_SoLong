RM := rm -rf

NAME := so_long
FT_PRINTFNAME := ./ft_printf/libftprintf.a

LDFLAGS = -Lminilibx-linux -L ./libft -lmlx -lXext -lX11 -lm

.PHONY: all clean fclean re ft_printf minilibx-linux

all: $(NAME)

clean:
	cd ft_printf && $(MAKE) clean
	$(RM) $(OBJS)

fclean: clean
	cd ft_printf && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all 

CC = cc
COMPILER_FLAGS = -Wall -Wextra -Werror -g 
HEADERS = -I .
COMPILE = $(CC) $(COMPILER_FLAGS) $(HEADERS) 

SRCS = solong.c input_processing.c input_processing2.c map.c map_check.c map_valid_path.c map_getdim.c finish.c math.c getnextline/get_next_line.c getnextline/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(FT_PRINTFNAME):
	cd ft_printf && $(MAKE) all

${NAME}: ${OBJS}
	@${MAKE} -C ./ft_printf --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} $(FT_PRINTFNAME) -o ${NAME} $(LDFLAGS)