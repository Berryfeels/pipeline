#Program name
NAME	= pipex

# Compilel
CC		= cc
CFLAGS	= -g -Werror -Wextra -Wall

# Libft
LIBFT_PATH	= include/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# printf
PRINTF_PATH	= include/printf/
PRINTF_NAME	= libprintf.a
PRINTF		= $(PRINTF_PATH)$(PRINTF_NAME)

# Includes
INC			=	-I ./include/\
				-I $(LIBFT_PATH)\
				-I $(PRINTF_PATH)\

# Sources
SRC_PATH	=	src/
SRC		=		pipex.c \
				utils.c

			
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= src/obj/
OBJS		= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

# Rules
all: $(LIBFT) $(PRINTF) $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making libft..."
	@make -C $(LIBFT_PATH)

$(PRINTF):
	@echo "Making printf..."
	@make -C $(PRINTF_PATH)

$(NAME): $(OBJS)
	@echo "Compiling ..."
	@echo "Now smoke that pipe"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(PRINTF_PATH) -lprintf


RM	= rm -f
clean:
	@echo "Removing .o object files..."
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_PATH) 
	@make clean -C $(PRINTF_PATH)

fclean: clean
	@echo "Removing..."
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(PRINTF)
	rm -r $(OBJ_PATH)

re: fclean all

.PHONY: all re clean fclean
