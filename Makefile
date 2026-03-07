NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
DEBUG_FLAGS := -g3

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
MAIN_RETURN_DIR := main_return
THREAD_DIR := thread
ACTIONS_DIR := actions
FREE_DIR := free
INIT_DIR := init
EDF_DIR := edf
SET_GET_DIR := set_get

SRC := main.c \
$(MAIN_RETURN_DIR)/errors.c \
$(MAIN_RETURN_DIR)/success.c \
$(UTILS_DIR)/ft_strlen.c \
$(UTILS_DIR)/get_time.c \
$(UTILS_DIR)/check_args.c \
$(THREAD_DIR)/create_thread.c \
$(THREAD_DIR)/join_thread.c \
$(ACTIONS_DIR)/compile.c \
$(ACTIONS_DIR)/debug.c \
$(ACTIONS_DIR)/refactor.c \
$(ACTIONS_DIR)/use_dongle.c \
$(ACTIONS_DIR)/routine.c \
$(ACTIONS_DIR)/monitor.c \
$(FREE_DIR)/free.c \
$(INIT_DIR)/init_struct_utils.c \
$(INIT_DIR)/init_values.c \
$(INIT_DIR)/init_structs.c \
$(INIT_DIR)/init_time.c \
$(EDF_DIR)/edf.c \
$(SET_GET_DIR)/set_get.c \

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

run_v: 						#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	timeout 300s valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=memcheck.log ./codexion 4 20 2 2 2 1 2 fifo

run_h: 						#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	valgrind --tool=helgrind --fair-sched=yes --log-file=helgrind-gen.log --read-var-info=yes --num-callers=20 --gen-suppressions=all ./codexion 4 20 2 2 2 1 2 fifo

run: 	#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	./codexion 6 800 2000 200 200 1 100 fifo

.PHONY: all clean fclean re