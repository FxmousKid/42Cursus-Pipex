# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 15:53:25 by inazaria          #+#    #+#              #
#    Updated: 2024/08/20 21:43:45 by inazaria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#<><><><><><><> Files <><><><><><><><><><><><><><><><><><><>

INCLUDES	= ./includes/

SRC_DIR_STD 	= ./src/
SRC_DIR_BONUS	= ./src_bonus/

BUILD_DIR_STD	= ./build/
BUILD_DIR_BONUS	= ./build_bonus/

DEBUG_FILE_PATH_STD = ./src/debugging_function
DEBUG_FILE_PATH_BONUS = ./src_bonus/debugging_function

DEBUG_BUILD_PATH_STD 	= ./build/debugging_function
DEBUG_BUILD_PATH_BONUS	= ./build_bonus/debugging_function

SRC_STD_NAMES	= pipex.c
SRC_STD_NAMES	+= pipex_utils.c
SRC_STD_NAMES	+= error_management.c

SRC_FILES_STD = $(addprefix $(SRC_DIR_STD), $(SRC_STD_NAMES))
OBJ_FILES_STD = $(patsubst $(SRC_DIR_STD)%.c, $(BUILD_DIR_STD)%.o, $(SRC_FILES_STD))
DEP_FILES_STD = $(patsubst $(SRC_DIR_STD)%.c, $(BUILD_DIR_STD)%.d, $(SRC_FILES_STD))

#<><><><><><><> Variables <><><><><><><><><><><><><><><><><>

NAME_STD	:= pipex
NAME_BONUS	:= pipex_bonus
CFLAGS		:= -g3 -Wall -Wextra -Werror -I $(INCLUDES) -MMD -MP libft/libft.a
MKDIR		:= mkdir -p
RM_RF		:= rm -rf

BLUE	:= $(shell echo -e "\033[34m") 
BROWN	:= $(shell echo -e "\033[33m")
GREEN	:= $(shell echo -e "\033[32m")
RED		:= $(shell echo -e "\033[31m")
NC		:= $(shell echo -e "\033[0m")


#<><><><><><><> Recipes <><><><><><><><><><><><><><><><><><>

$(BUILD_DIR_STD)%.o : $(SRC_DIR_STD)%.c
	@$(MKDIR) $(dir $@)
	@$(CC) -c $(CFLAGS) $< -o $@
	@echo "$(BLUE)[CMP] Compiling $< ... $(NC)"

-include $(DEP_FILES_STD)

$(NAME_STD) : libft $(OBJ_FILES_STD)
	@echo -e "$(BROWN)[BLD] Building Pipex executable...$(NC)"
	@$(RM) $(DEBUG_BUILD_PATH).[od]
	@$(RM) $(NAME_STD)
	@echo -e "$(BROWN)[LNK] Linking object files ..."
	@$(CC) $(CFLAGS) -c $(DEBUG_FILE_PATH_STD).c -o $(DEBUG_BUILD_PATH_STD).o
	@$(CC) $(CFLAGS) $^ $(DEBUG_BUILD_PATH_STD).o -o $(NAME_STD) ./libft/libft.a 

	@echo -e "$(GREEN)[BLD] Executable built successfully.$(NC)"

libft : 
	@echo -e "$(BROWN)[BLD] Building libft...$(NC)"
	@make -C --no-print-directory -s ./libft all
	@echo -e "$(GREEN)[BLD] Libft built successfully.$(NC)"

all : $(NAME_STD)

debug : $(OBJ_FILES)
	@echo -e "$(RED)[DBG] Building in Debug mode...$(NC) "
	@$(RM) $(DEBUG_BUILD_PATH_STD).[od]
	@echo -e "$(BLUE)[CMP] Compiling $(DEBUG_FILE_PATH_STD).c ..."
	@$(CC) $(CFLAGS) -D DEBUG -c $(DEBUG_FILE_PATH_STD).c -o $(DEBUG_BUILD_PATH_STD).o
	@echo -e "$(BROWN)[LNK] Linking object files ..."
	@$(CC) $(CFLAGS)  $^ $(DEBUG_BUILD_PATH_STD).o -o $(NAME_STD) ./libft/libft.a 


clean : 
	@echo -e "$(BROWN)[CLN] Cleaning object and dependency files...$(NC)"	
	@$(RM) $(DEP_FILES) $(OBJ_FILES) $(DEBUG_BUILD_PATH).[od]
	@echo -e "$(GREEN)[CLN] Clean complete.$(NC)"

fclean : 
	@echo -e "$(BROWN)[CLN] Cleaning object, dependency files, and executable...$(NC)"
	@$(RM_RF) $(BUILD_DIR_STD) $(NAME_STD)
	@echo -e "$(GREEN)[CLN] Clean complete.$(NC)"


re : fclean all

.DEFAULT_GOAL := all
.PHONY : all clean fclean re debug
