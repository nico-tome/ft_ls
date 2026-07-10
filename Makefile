NAME		:=	ft_ls

SRC_DIR		:=	srcs/
BUILD_DIR	:=	build/

SRC			:=	main.c \
				free_utils/free_utils.c \
				parsing/parse_flags.c \
				print_utils/print_utils.c \
				print_utils/print_ls.c \
				read_utils/read_utils.c \
				sort_utils/sort_dir.c \
				sort_utils/sort_file.c

OBJ = $(patsubst %.c, $(BUILD_DIR)%.o, $(SRC))

HEADERS = includes/

LIBS	:=	lib/libft/libft.a

CC = cc

FLAGS = -Wall -Werror -Wextra -g

TPUT = tput -T xterm-256color
_RESET := $(shell $(TPUT) sgr0)
_BOLD := $(shell $(TPUT) bold)
_ITALIC := $(shell $(TPUT) sitm)
_UNDER := $(shell $(TPUT) smul)
_GREEN := $(shell $(TPUT) setaf 2)
_YELLOW := $(shell $(TPUT) setaf 3)
_RED := $(shell $(TPUT) setaf 1)
_GRAY := $(shell $(TPUT) setaf 8)
_PURPLE := $(shell $(TPUT) setaf 5)

OBJS_TOTAL = $(words $(OBJ))
CURR_OBJ = 0

# User installation
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin

# Shell completions
BASH_COMPLETION_DIR := $(PREFIX)/share/bash-completion/completions
ZSH_COMPLETION_DIR := $(PREFIX)/share/zsh/site-functions

ZSHRC := $(HOME)/.zshrc
BASHRC := $(HOME)/.bashrc

all: ${NAME} banner

no-banner:	${NAME}

banner: # replace this banner with yours
	@echo "███████╗████████╗     ██╗     ███████╗";
	@echo "██╔════╝╚══██╔══╝     ██║     ██╔════╝";
	@echo "█████╗     ██║        ██║     ███████╗";
	@echo "██╔══╝     ██║        ██║     ╚════██║";
	@echo "██║        ██║███████╗███████╗███████║";
	@echo "╚═╝        ╚═╝╚══════╝╚══════╝╚══════╝";
	@echo "                                      ";

$(NAME): ${LIBS} ${OBJ}
	@${CC} -o ${NAME} ${FLAGS} ${OBJ} ${LIBS}
	@printf "${_BOLD}$(NAME)${_RESET} compiled ${_GREEN}${_BOLD}successfully${_RESET}\n\n"

$(LIBS):
	@make --no-print-directory -C lib/libft

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	@${CC} -o $@ -I $(HEADERS) -c $< ${FLAGS}
	@$(eval CURR_OBJ=$(shell echo $$(( $(CURR_OBJ) + 1 ))))
	@$(eval PERCENT=$(shell echo $$(( $(CURR_OBJ) * 100 / $(OBJS_TOTAL) ))))
	@printf "${_GREEN}(${_BOLD}%3s%%${_RESET}${_GREEN}) ${_RESET}Compiling ${_BOLD}${_PURPLE}$<${_RESET}\n" "$(PERCENT)"

clean:
	@make --no-print-directory -C lib/libft clean
	@rm -rf $(BUILD_DIR)
	@printf "\n${_BOLD}All objects are ${_RED}cleaned${_RESET}! 🎉\n\n"

fclean: clean
	@rm -f ${LIBS}
	@rm -f ${NAME}
	@printf "Cleaned ${_BOLD}${NAME}${_RESET} !\n\n"

install: $(NAME)
	@printf "${_BOLD}Installing $(NAME)...${_RESET}\n"

	@install -Dm755 $(NAME) $(BINDIR)/$(NAME)
	@printf "${_GREEN}Installed${_RESET} $(NAME) in ${_BOLD}$(BINDIR)${_RESET}\n"

	@if [ -f completions/bash/$(NAME) ]; then \
		install -Dm644 \
			completions/bash/$(NAME) \
			$(BASH_COMPLETION_DIR)/$(NAME); \
		printf "${_GREEN}Installed${_RESET} bash completion\n"; \
		if ! grep -q "$(BASH_COMPLETION_DIR)" $(BASHRC) 2>/dev/null; then \
			printf "\n# ft_ls bash completion\nsource $(BASH_COMPLETION_DIR)/$(NAME)\n" >> $(BASHRC); \
			printf "${_GREEN}Updated${_RESET} ~/.bashrc\n"; \
		fi; \
	fi

	@if [ -f completions/zsh/_$(NAME) ]; then \
		install -Dm644 \
			completions/zsh/_$(NAME) \
			$(ZSH_COMPLETION_DIR)/_$(NAME); \
		printf "${_GREEN}Installed${_RESET} zsh completion\n"; \
		if ! grep -q "$(PREFIX)/share/zsh/site-functions" $(ZSHRC) 2>/dev/null; then \
			printf "\n# ft_ls zsh completion\nfpath=($(PREFIX)/share/zsh/site-functions \$$fpath)\nautoload -Uz compinit && compinit\n" >> $(ZSHRC); \
			printf "${_GREEN}Updated${_RESET} ~/.zshrc\n"; \
		fi; \
	fi
	
	@if ! grep -q "$(BINDIR)" $(BASHRC) 2>/dev/null; then \
		printf "\n# ft_ls path\nexport PATH=\"$(BINDIR):\$$PATH\"\n" >> $(BASHRC); \
	fi
	
	@if ! grep -q "$(BINDIR)" $(ZSHRC) 2>/dev/null; then \
		printf "\n# ft_ls path\nexport PATH=\"$(BINDIR):\$$PATH\"\n" >> $(ZSHRC); \
	fi

	@printf "\n${_GREEN}Installation complete.${_RESET}\n"
	@printf "${_YELLOW}Restart your terminal or run:${_RESET}\n"
	@printf "  source ~/.bashrc\n"
	@printf "  source ~/.zshrc\n"

uninstall:
	@printf "${_BOLD}Removing $(NAME)...${_RESET}\n"

	@rm -f $(BINDIR)/$(NAME)
	@rm -f $(BASH_COMPLETION_DIR)/$(NAME)
	@rm -f $(ZSH_COMPLETION_DIR)/_$(NAME)

	@printf "${_GREEN}Removed${_RESET} $(NAME)\n"

	@if [ -f $(BASHRC) ]; then \
		sed -i '/# ft_ls bash completion/d' $(BASHRC); \
		sed -i '\|$(BASH_COMPLETION_DIR)/$(NAME)|d' $(BASHRC); \
		sed -i '/# ft_ls path/d' $(BASHRC); \
		sed -i '\|export PATH="$(BINDIR):\$$PATH"|d' $(BASHRC); \
	fi

	@if [ -f $(ZSHRC) ]; then \
		sed -i '/# ft_ls zsh completion/d' $(ZSHRC); \
		sed -i '\|fpath=($(PREFIX)/share/zsh/site-functions \$$fpath)|d' $(ZSHRC); \
		sed -i '\|autoload -Uz compinit && compinit|d' $(ZSHRC); \
	fi

	@printf "${_GREEN}Uninstall complete.${_RESET}\n"

help:
	@printf "\n${_BOLD}${_PURPLE}Project Makefile Help${_RESET}\n"
	@printf "${_GRAY}----------------------------------------${_RESET}\n\n"

	@printf "${_BOLD}${_YELLOW}Usage:${_RESET}\n"
	@printf "  make ${_GREEN}[target]${_RESET}\n\n"

	@printf "${_BOLD}${_YELLOW}Available targets:${_RESET}\n\n"

	@printf "  ${_GREEN}all${_RESET}\n"
	@printf "      Build the project\n\n"

	@printf "  ${_GREEN}$(NAME)${_RESET}\n"
	@printf "      Compile the binary\n\n"

	@printf "  ${_GREEN}clean${_RESET}\n"
	@printf "      Remove object files (${_ITALIC}$(BUILD_DIR)${_RESET})\n\n"

	@printf "  ${_GREEN}fclean${_RESET}\n"
	@printf "      Remove object files and binary\n\n"

	@printf "  ${_GREEN}re${_RESET}\n"
	@printf "      Full rebuild (${_ITALIC}fclean + all${_RESET})\n\n"

	@printf "  ${_GREEN}install${_RESET}\n"
	@printf "      Install binary to ${_ITALIC}$(BINDIR)${_RESET}\n"
	@printf "      ${_GRAY}(may require sudo depending on destination)${_RESET}\n\n"

	@printf "  ${_GREEN}uninstall${_RESET}\n"
	@printf "      Remove binary from ${_ITALIC}$(BINDIR)${_RESET}\n\n"

	@printf "  ${_GREEN}help${_RESET}\n"
	@printf "      Display this help message\n\n"

	@printf "${_BOLD}${_YELLOW}Variables:${_RESET}\n\n"

	@printf "  ${_GREEN}PREFIX${_RESET}\n"
	@printf "      Installation prefix (default: ${_ITALIC}/usr/local${_RESET})\n\n"

	@printf "  ${_GREEN}BINDIR${_RESET}\n"
	@printf "      Binary installation directory (default: ${_ITALIC}\$$PREFIX/bin${_RESET})\n\n"

	@printf "${_BOLD}${_YELLOW}Examples:${_RESET}\n\n"

	@printf "  ${_ITALIC}make${_RESET}\n"
	@printf "  ${_ITALIC}make re${_RESET}\n"
	@printf "  ${_ITALIC}make install${_RESET}\n"
	@printf "  ${_ITALIC}make install PREFIX=\$$HOME/.local${_RESET}\n\n"

	@printf "${_BOLD}${_YELLOW}Credits:${_RESET}\n\n"

	@printf "  ${_GREEN}Project:${_RESET} ft_ls\n"
	@printf "  ${_GREEN}Author:${_RESET} ntome\n"
	@printf "  ${_GREEN}Language:${_RESET} C\n"
	@printf "  ${_GREEN}Build System:${_RESET} Makefile\n\n"

	@printf "${_GRAY}----------------------------------------${_RESET}\n\n"

re: fclean all

.PHONY: all clean fclean re banner no-banner help install uninstall
