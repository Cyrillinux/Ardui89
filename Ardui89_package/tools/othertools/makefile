# Nom de l'exécutable
TARGET = builder

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -g

# Fichiers sources
SRCS = builder.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: fake fake_cpp fake_ld fake_objcopy fake_size fake_sdar

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET) fake fake_cpp fake_ld fake_objcopy fake_size fake_sdar
	
fake:
	gcc -o fake fake.c

fake_cpp:
	gcc -o fake_cpp fake_cpp.c

fake_ld:
	gcc -o fake_ld fake_ld.c

fake_objcopy:
	gcc -o fake_objcopy fake_objcopy.c
	
fake_size:
	gcc -o fake_size fake_size.c

fake_sdar:
	gcc -o fake_sdar fake_sdar.c

try: clean all

.PHONY: all clean
