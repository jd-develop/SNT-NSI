#!/usr/bin/sh

chmod +x clean_tex.py
lilypond-book --output=out --pdf rapport.lytex
./clean_tex.py
cd out
pdflatex rapport.tex
cp rapport.pdf ..
cd ..
rm tmp*.pdf
rm tmp*.out
xdg-open rapport.pdf

