# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 15:53:25 by inazaria          #+#    #+#              #
#    Updated: 2024/09/16 18:29:43 by inazaria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#<><><><><><><> Files <><><><><><><><><><><><><><><><><><><>

INCLUDES	= ./includes/

SRC_DIR_STD 	= ./src/

BUILD_DIR_STD	= ./build/

DEBUG_FILE_PATH_STD = ./src/error_management/debugging_function

DEBUG_BUILD_PATH_STD 	= ./build/error_management/debugging_function

SRC_STD_NAMES	= main.c
SRC_STD_NAMES	+= launch_childs.c
SRC_STD_NAMES	+= exec.c
SRC_STD_NAMES	+= heredoc.c
SRC_STD_NAMES	+= utils/make_t_pipex.c
SRC_STD_NAMES	+= utils/exec_utils.c
SRC_STD_NAMES	+= utils/manage_files.c
SRC_STD_NAMES	+= utils/manage_file_descriptors.c
SRC_STD_NAMES	+= error_management/error_management.c
SRC_STD_NAMES	+= error_management/free_utils.c

SRC_FILES_STD = $(addprefix $(SRC_DIR_STD), $(SRC_STD_NAMES))
OBJ_FILES_STD = $(patsubst $(SRC_DIR_STD)%.c, $(BUILD_DIR_STD)%.o, $(SRC_FILES_STD))
DEP_FILES_STD = $(patsubst $(SRC_DIR_STD)%.c, $(BUILD_DIR_STD)%.d, $(SRC_FILES_STD))

#<><><><><><><> Variables <><><><><><><><><><><><><><><><><>

NAME_STD	:= pipex
NAME_BONUS	:= pipex_bonus
CFLAGS		:= -g3 -Wall -Wextra -Werror -I $(INCLUDES) -MMD -MP
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

$(NAME_STD) : $(OBJ_FILES_STD)
	@echo -e "$(BROWN)[BLD] Building libft...$(NC)"
	@$(MAKE) --no-print-directory -s -C libft all 
	@echo -e "$(GREEN)[BLD] Libft built successfully.$(NC)"
	@echo -e "$(BROWN)[BLD] Building Pipex executable...$(NC)"
	@$(RM) $(DEBUG_BUILD_PATH).[od]
	@$(RM) $(NAME_STD)
	@echo -e "$(BROWN)[LNK] Linking object files ..."
	@$(CC) $(CFLAGS) -c $(DEBUG_FILE_PATH_STD).c -o $(DEBUG_BUILD_PATH_STD).o
	@$(CC) $(CFLAGS) $(OBJ_FILES_STD) $(DEBUG_BUILD_PATH_STD).o -o $(NAME_STD) ./libft/libft.a
	@echo -e "$(GREEN)[BLD] Executable built successfully.$(NC)"

all : $(NAME_STD)

debug : $(OBJ_FILES_STD)
	@echo -e "$(RED)[DBG] Building in Debug mode...$(NC) "
	@$(RM) $(DEBUG_BUILD_PATH_STD).[od]
	@echo -e "$(BLUE)[CMP] Compiling $(DEBUG_FILE_PATH_STD).c ..."
	@$(CC) $(CFLAGS) -D DEBUG -c $(DEBUG_FILE_PATH_STD).c -o $(DEBUG_BUILD_PATH_STD).o
	@echo -e "$(BROWN)[LNK] Linking object files ..."
	@$(CC) $(CFLAGS) $^ $(DEBUG_BUILD_PATH_STD).o -o $(NAME_STD) ./libft/libft.a 
	@echo -e "$(GREEN)[BLD] Executable built successfully.$(NC)"


clean : 
	@echo -e "$(BROWN)[CLN] Cleaning object and dependency files...$(NC)"	
	@$(RM) $(DEP_FILES_STD) $(OBJ_FILES_STD) $(DEBUG_BUILD_PATH).[od]
	@echo -e "$(GREEN)[CLN] Clean complete.$(NC)"

fclean : 
	@echo -e "$(BROWN)[CLN] Cleaning object, dependency files, and executable...$(NC)"
	@$(RM_RF) $(BUILD_DIR_STD) $(NAME_STD)
	@echo -e "$(GREEN)[CLN] Clean complete.$(NC)"


re : fclean all

.DEFAULT_GOAL := all
.PHONY : all clean fclean re debug
