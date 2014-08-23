res: res.c
	clang res.c -Wall -framework ApplicationServices -o res

clean:
	rm res
