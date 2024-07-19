# Nom de l'exécutable
TARGET = builder
FAKE_VERSION=_FAKE_VERSION_=\"0.2.0\"
SDCC_VERSION=_SDCC_VERSION_=\"4.4.0\"

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
	gcc -o fake fake.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)

fake_cpp:
	gcc -o fake_cpp fake_cpp.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)

fake_ld:
	gcc -o fake_ld fake_ld.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)

fake_objcopy:
	gcc -o fake_objcopy fake_objcopy.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)
	
fake_size:
	gcc -o fake_size fake_size.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)

fake_sdar:
	gcc -o fake_sdar fake_sdar.c -D$(FAKE_VERSION) -D$(SDCC_VERSION)

try: clean all

.PHONY: all clean
