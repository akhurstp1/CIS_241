
FILE = main
DEPS += sha1/sha1.c sha1/sha1.h
DEPS += fileTree/fileTree.c fileTree/fileTree.h

make:
	@gcc -o $(FILE).o $(FILE).c $(DEPS)

flash:
	@gcc -o $(FILE) $(FILE).c $(DEPS)
	@./$(FILE)