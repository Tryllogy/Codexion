NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
DEBUG_FLAGS := -g3 -O1 -fsanitize=thread -fno-omit-frame-pointer

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
MAIN_RETURN_DIR := main_return
THREAD_DIR := thread
ACTIONS_DIR := actions
FREE_DIR := free
INIT_DIR := init
EDF_DIR := edf

SRC := main.c \
$(MAIN_RETURN_DIR)/errors.c \
$(MAIN_RETURN_DIR)/success.c \
$(UTILS_DIR)/ft_strlen.c \
$(UTILS_DIR)/get_time.c \
$(UTILS_DIR)/check_args.c \
$(UTILS_DIR)/check_malloc.c \
$(THREAD_DIR)/create_thread.c \
$(THREAD_DIR)/join_thread.c \
$(ACTIONS_DIR)/compile.c \
$(ACTIONS_DIR)/debug.c \
$(ACTIONS_DIR)/refactor.c \
$(ACTIONS_DIR)/use_dongle.c \
$(FREE_DIR)/free.c \
$(INIT_DIR)/init_struct_utils.c \
$(INIT_DIR)/init_values.c \
$(INIT_DIR)/init_structs.c \
$(INIT_DIR)/init_time.c \
$(EDF_DIR)/edf.c \

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

run_d: 						#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	valgrind --tool=helgrind --log-file=helgrind-gen.log --read-var-info=yes --num-callers=20 --gen-suppressions=all ./codexion 20 1000 200 200 200 15 200 fifo

run: 	#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	./codexion 6 800 200 200 200 1 100 fifo

.PHONY: all clean fclean re