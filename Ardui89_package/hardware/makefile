# Fichier cible
TARGET=package_ardui89_index.json
VERSION=0.1.0
# Liste des fichiers source
DSRCS = ardui89-$(VERSION)
# Liste des fichiers objets
TGZ = $(DSRCS:=.tar.gz)
MKTOOL = $(DSRCS:=.json)
HOST = x86_64-apple-darwin12
URL = http://bacciel.com/tools/
# Règle par défaut : construire l'exécutable
all: $(TARGET)
# Règle pour construire l'exécutable
$(TARGET): $(TGZ) $(MKTOOL)
	echo "Done. Ready for : $(TARGET)"
# Règle pour construire les fichiers objets
%.tar.gz: %
	tar -cvzf $@ $<
%.json: %
	./mktooljson/mktooljson $<.tar.gz $(HOST) $(URL)$<.tar.gz
# Règle pour nettoyer les fichiers de construction
clean:
	rm -f $(TGZ)
.PHONY: all clean
