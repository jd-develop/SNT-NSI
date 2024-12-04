#!/usr/bin/sh

lilypond-book --output=out --pdf rapport.lytex
cd out
pdflatex rapport.tex
cp rapport.pdf ..
cd ..

