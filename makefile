all:
	echo make create
	
preproc:
	git config --global --add safe.directory "/Users/cyrilbarbato/Desktop/A. TRAVAUX/B. PRJ/_µC/ardui89"
	rm -rf .git
	rm -rf examples
	mkdir examples
	cp -r package-IDE-0.4.2/hardware/ardui89-0.4.2/libraries/* examples
	git init

	echo "## macOS\n\
.DS_Store\n\
\n\
## Archives\n\
*.zip\n\
*.7z\n\
*.gz\n\
\n\
## Temp\n\
*.tmp\n\
*.bak\n\
\n\
## Répertoires exclus\n\
CH34x_CP210x_Drivers/\n\
package-IDE-0.4.2/tools/_OLD/\n\
package-IDE-0.4.2/tools/python3-3.8-stcgal-0.3-i686-mingw32/\n\
package-IDE-0.4.2/tools/python3-3.8-stcgal-0.3-i686-pc-linux-gnu/\n\
package-IDE-0.4.2/tools/python3-3.8-stcgal-0.3-x86_64-apple-darwin/\n\
package-IDE-0.4.2/tools/sdcc-4.4.0-i686-mingw32/\n\
package-IDE-0.4.2/tools/sdcc-4.4.0-i686-pc-linux-gnu/\n\
package-IDE-0.4.2/tools/sdcc-4.4.0-x86_64-apple-darwin/\n" > .gitignore

	git add .
	

create: preproc
	git commit -m "Initial commit of Ardui89"

	git status

	git remote add origin https://github.com/Cyrillinux/Ardui89.git
	git branch -M main
	git push -u origin main --force
