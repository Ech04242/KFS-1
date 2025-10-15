#nasm -felf32 ./Amorcage/boot.asm -o boot.o

#gcc -m32 -fno-builtin -fno-exception -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs






#########################
#      WRITE FUNCT      #
#########################

grey  = /bin/echo -e "\x1b[30m$1\x1b[0m"
red   = /bin/echo -e "\x1b[31m$1\x1b[0m"
green = /bin/echo -e "\x1b[32m$1\x1b[0m"
yelow = /bin/echo -e "\x1b[33m$1\x1b[0m"
blue  = /bin/echo -e "\x1b[34m$1\x1b[0m"
purple= /bin/echo -e "\x1b[35m$1\x1b[0m"
cyan  = /bin/echo -e "\x1b[36m$1\x1b[0m"
white = /bin/echo -e "\x1b[37m$1\x1b[0m"


#########################
#      DEFINE SRCS      #
#########################

NAME = kfs1

CC = gcc
FLAG = -MMD -Wall -g3 -Werror -Wextra -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

DIR_HEADER  = headers/
SRC_PATH = C/src/
SRC =	main.c	printk.c utils.c kernel.c 
OBJ_PATH	=	.obj/
OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))

DEP_PATH	=	.dep/
DEP		=	$(SRC:.c=.d)
DEPS	=	$(addprefix $(DEP_PATH), $(DEP))

RM		=	rm -f
RMDIR	=	rm -rf
MKDIR	=	mkdir -p

#########################
#        INCLUDES       #
#########################


$(NAME): $(OBJS)
	nasm -f elf32 ./Amorcage/boot.asm -o .obj/boot.o
	@$(call green,"debut de la compilation de kfs1")
	ld -m elf_i386 -T ./linker/linker.ld -o kfs1.bin .obj/boot.o .obj/kernel.o .obj/main.o .obj/utils.o .obj/printk.o
#	objcopy -O binary kfs1.elf kfs1.bin
	@$(call purple,"compilation du programme accomplie avec succès !")


#########################
#       BUILD RULES     #
#########################

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAG) -c $< -o $@ -I $(DIR_HEADER)
	@$(call green,"$< ✅")


build_iso:
	docker build -t iso_maker ./Docker
	docker run --mount type=bind,source=./,target=/app iso_maker


#########################
#       CLEAN RULES     #
#########################

clean:
	@rm -rf .obj
	@$(call yelow,"clean kfs1 ok ✅")

#########################
#      FCLEAN RULES     #
#########################

fclean:
	@rm -f $(NAME)
	@rm -rf .obj
	@$(call yelow,"fclean kfs1 ✅")

#######################
#       RE RULES      #
#######################

re: fclean
	@make

#######################
#      ALL RULES      #
#######################

run:
	qemu-system-i386 -kernel kfs1.bin

run_iso:
	qemu-system-i386 -cdrom kfs1.iso

run_debug:
	qemu-system-i386 -kernel kfs1.bin -s -S & gdb -x .gdbinit

all: $(NAME)

.PHONY: all clean fclean re all