CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./src/minilibx-linux -I./includes -I./src/libft
LDFLAGS = -L./src/minilibx-linux -lmlx_Linux -lX11 -lXext -L./src/libft -lft

TARGET = fractol

OBJ_PATH = obj/
LIBFT_DIR = src/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS =	src/main.c \
	src/events.c \
	src/init.c \
	src/math_utils.c \
	src/render.c \
	src/string_utils.c
		
OBJS = $(SRCS:src/%.c=$(OBJ_PATH)%.o)
HEADERS = includes/fractol.h

$(OBJ_PATH)%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_LIB) $(TARGET)

$(TARGET): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
