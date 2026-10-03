from pathlib import Path

# Deliberate order: put the things you are most likely to search first.
FILES = [
    ("Template", "template.cpp"),
    ("C++ STL", "cpp_stl.cpp"),
    ("Graphs", "graph.cpp"),
    ("Dynamic Programming", "dp.cpp"),
    ("Range Queries", "range_queries.cpp"),
    ("Number Theory", "num_theory.cpp"),
    ("Combinatorics", "combi.cpp"),
    ("Trees", "tree.cpp"),
    ("Trie", "trie.cpp"),
    ("String Hashing", "string-hashing.cpp"),
    ("Bit Manipulation", "bit_man.cpp"),
    ("PBDS", "pbds.cpp"),
    ("Patterns", "patterns.cpp"),
    ("Matrix Exponentiation", "matrix_expo.cpp"),
    ("Custom Hash", "custom_hash.cpp"),
    ("Merge Intervals", "merge_intervals.cpp"),
    ("GCC Optimizations", "gcc_optimization.cpp"),
    ("Observations", "observations.cpp"),
]

def latex_escape(s):
    # Only used for section titles, not source code.
    return (s.replace("\\", r"\textbackslash{}")
             .replace("&", r"\&")
             .replace("%", r"\%")
             .replace("#", r"\#")
             .replace("_", r"\_")
             .replace("{", r"\{")
             .replace("}", r"\}"))

available = [(title, path) for title, path in FILES if Path(path).exists()]

missing = [path for _, path in FILES if not Path(path).exists()]
if missing:
    print("Warning: missing files:", ", ".join(missing))

parts = []
for title, path in available:
    parts.append(
        rf"""
\section*{{{latex_escape(title)}}}
\lstinputlisting[language=C++,breaklines=true]{'{' + path + '}'}
"""
    )

tex = rf"""
\documentclass[8pt,a4paper]{{article}}

\usepackage[
    landscape,
    margin=0.35cm,
    top=0.45cm,
    bottom=0.45cm
]{{geometry}}

\usepackage{{listings}}
\usepackage{{multicol}}
\usepackage{{xcolor}}
\usepackage{{titlesec}}
\usepackage{{fancyhdr}}

\pagestyle{{fancy}}
\fancyhf{{}}
\lhead{{ICPC Template}}
\rhead{{\thepage}}
\renewcommand{{\headrulewidth}}{{0.2pt}}

\setlength{{\columnsep}}{{0.35cm}}
\setlength{{\parindent}}{{0pt}}
\setlength{{\parskip}}{{0pt}}

\titleformat{{\section}}
  {{\bfseries\small}}
  {{}}
  {{0pt}}
  {{}}
  [\vspace{{-2pt}}\hrule\vspace{{2pt}}]

\lstset{{
    basicstyle=\ttfamily\fontsize{{4.8}}{{5.5}}\selectfont,
    columns=fullflexible,
    keepspaces=true,
    breaklines=true,
    breakatwhitespace=false,
    tabsize=2,
    showstringspaces=false,
    frame=single,
    framesep=1pt,
    xleftmargin=1pt,
    xrightmargin=1pt,
    aboveskip=2pt,
    belowskip=3pt
}}

\begin{{document}}
\begin{{center}}
    {{\Large\bfseries ICPC Template}}
\end{{center}}
\vspace{{-5pt}}

\begin{{multicols*}}{{3}}
{''.join(parts)}
\end{{multicols*}}

\end{{document}}
"""

Path("icpc_cheatsheet.tex").write_text(tex)
print(f"Generated icpc_cheatsheet.tex with {len(available)} files.")
