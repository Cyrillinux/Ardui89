# Fichier cible
TARGET=package_ardui89_index.json
VERSION=0.2.1
STCFLASHISP_VERSION=0.2.1
SDCC_VERSION=4.4.0
HOST = x86_64-apple-darwin12
# Liste des fichiers source
DSRCS = sdcc-$(SDCC_VERSION)-$(HOST) fake_cc-$(VERSION)-$(HOST) stcflashisp-$(STCFLASHISP_VERSION)-$(HOST)

# Liste des fichiers objets
TGZ = $(DSRCS:=.tar.gz)
MKTOOL = $(DSRCS:=.json)
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

mingw32:
	make -f makefile_i686-mingw32.sub
