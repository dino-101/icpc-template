# ICPC PDF Generator

Run from the root of `dino-101/icpc-template`.

## Install

```bash
sudo apt update
sudo apt install texlive-latex-extra
```

## Generate

```bash
chmod +x make_pdf.sh
./make_pdf.sh
```

Output:

```text
icpc_cheatsheet.pdf
```

The generator uses a fixed topic order and a compact A4 landscape, 3-column layout.

If the text is too small for your print setup, change:

```latex
\fontsize{4.8}{5.5}
```

to e.g.

```latex
\fontsize{5.5}{6.2}
```

and/or change `multicols*` from `3` to `2`.
