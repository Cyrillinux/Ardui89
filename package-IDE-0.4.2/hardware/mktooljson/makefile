
# Nom de l'exécutable
TARGET = mktooljson

# Compilateur
CC = gcc

# Options du compilateur
CFLAGS = -Wall -Wextra -O2

# Options de l'éditeur de liens
LDFLAGS = 

# Liste des fichiers source
SRCS = main.c sha256.c

# Liste des fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut : construire l'exécutable
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Règle pour construire les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers de construction
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour nettoyer tout (y compris les fichiers de sauvegarde)
distclean: clean
	rm -f *~

.PHONY: all clean distclean
