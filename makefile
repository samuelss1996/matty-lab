MaTTY_Lab: SHELL:=/bin/bash 

MaTTY_Lab:
	gcc *.c */*.c -I. -Ierrors -Ikeywords -Ilexical -Isymbols -Isyntactic -Iutil -o MaTTY_Lab -lfl -lm

clean:
	rm -f MaTTY_Lab