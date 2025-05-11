# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Fichiers source
SRC = src/main.c \
	  src/animaux.c \
	  src/affichage.c \
	  src/utils.c \
	  src/menu.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Nom de l'exécutable
TARGET = Projet

# Cible par défaut
all: $(TARGET)

# Règle de construction pour l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Règle pour générer les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)
