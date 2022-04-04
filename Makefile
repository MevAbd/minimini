SRC =	main.c \
		error.c \
		lexer.c \
		lexer_util.c \
		lexer_word.c \
		lib.c \
		parsing.c \
		cmd.c \
		redir.c \
		pars_util.c \
		fill_env.c \
		quote.c \
		quote_util.c \
		replace_dol.c \
		fork.c \
		fork_util.c \
		util.c \
		split.c \
		pwd.c \
		cd.c \
		echo.c \
		export.c \
		unset.c \
		exit.c \
		env.c \
		quote_word_splter.c

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,${SRC})
OBJ_DIR	= objs/
LEXER_DIR = lexer/
PARS_DIR = parsing/
LIB_DIR = lib/
FORK_DIR = fork/
BUILT_DIR = builtin/
INCLUDES_DIR = includes/

VPATH	= $(LEXER_DIR) $(LIB_DIR) $(PARS_DIR) $(FORK_DIR) $(BUILT_DIR)

FLAGS = -g

READ_FLAGS = -lreadline

$(OBJ_DIR)%.o	: %.c
				mkdir -p $(OBJ_DIR)
				cc $(FLAGS) -c $< -I$(INCLUDES_DIR) -o $@

NAME = mini

$(NAME): $(OBJ)
	cc $(FLAGS) -o $(NAME) $(OBJ) $(READ_FLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re

