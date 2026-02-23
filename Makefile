NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils

SRC := main.c \
init_data.c \
errors.c \
success.c \
$(UTILS_DIR)/lst.c \
$(UTILS_DIR)/ft_strlen.c


all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)


clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re