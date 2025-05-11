# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Fichiers source
SRC = main.c animaux.c affichage.c utils.c menu.c

# Fichiers objets
OBJ = main.o animaux.o affichage.o utils.o menu.o

# Nom de l'exécutable
TARGET = Projet

# Cible par défaut
all: $(TARGET)

# Construction de l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compilation des fichiers .c en .o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

animaux.o: animaux.c
	$(CC) $(CFLAGS) -c animaux.c

affichage.o: affichage.c
	$(CC) $(CFLAGS) -c affichage.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c

# Nettoyage
clean:
	rm -f *.o $(TARGET)
