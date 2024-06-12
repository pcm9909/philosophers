all :
	make re -C ./utils/libft
	cc main.c ./utils/libft/libft.a -lpthread -g