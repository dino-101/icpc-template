#!/usr/bin/env bash
set -euo pipefail

# Run this from the root of the icpc-template repository.
command -v pdflatex >/dev/null 2>&1 || {
    echo "pdflatex not found. Install it with:"
    echo "  sudo apt install texlive-latex-extra"
    exit 1
}

python3 generate_tex.py
pdflatex -interaction=nonstopmode -halt-on-error icpc_cheatsheet.tex >/dev/null
pdflatex -interaction=nonstopmode -halt-on-error icpc_cheatsheet.tex >/dev/null

rm -f icpc_cheatsheet.aux icpc_cheatsheet.log icpc_cheatsheet.out icpc_cheatsheet.toc
echo "Created: icpc_cheatsheet.pdf"
