all :
	make re -C ./utils/libft
	cc main.c utils.c -pthread -g
