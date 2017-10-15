#!/bin/bash
git fetch origin
git reset --hard origin/master
git reset --soft jeyra/style_ra
git reset tools/
git checkout tools/
find src/ -name "*.[ch]" -or -name "*.cpp" | xargs uncrustify -c tools/uncrustify.cfg --no-backup
git commit -am "Automatic rathena Update"
git push jeyra style_ra
