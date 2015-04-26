all: tree

tree:
	gcc main.c rb_tree.c -o tree

balance:
	gcc main.c rb_tree.c -o tree -D__BALANCE

clean:
	-rm tree core *.dat *.png
