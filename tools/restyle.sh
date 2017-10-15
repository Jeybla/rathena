#!/bin/bash
git fetch origin
git checkout master
git reset --hard origin/master
find ../src/ -name "*.[ch]" -or -name "*.cpp" | xargs uncrustify -c uncrustify.cfg --no-backup
git commit -am "Apply uncrustify rules"
git checkout style_ra
git merge master
