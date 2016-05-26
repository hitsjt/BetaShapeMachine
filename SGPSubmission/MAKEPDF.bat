taskkill /im Acrobat.exe


del *.aux
del *.out
del *.sav
del *.ps
del *.npg
del *.blg
del *.log
del *.bbl
del *.brf
del *.lbl


pdflatex bbbm
bibtex bbbm
pdflatex bbbm
pdflatex bbbm

del *.aux
del *.out
del *.sav
del *.ps
del *.npg
del *.bbl
del *.blg
del *.log
del *.bbl
del *.brf
del *.lbl

