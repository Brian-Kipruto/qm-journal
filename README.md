# QM Journal

A working notebook for learning quantum mechanics by building it. Each entry pairs careful prose explanation with interactive widgets where the math is computed in C++ compiled to WebAssembly.

## Live site

[link to your deployment, once you deploy]

## Stack

- **Astro 5** with MDX for content
- **C++ → WebAssembly** via Emscripten for physics computation
- **D3.js** for plotting
- **KaTeX** for math rendering
- **Vanilla CSS** — no Tailwind, no framework

## Run locally

Requires Node 18+, [Emscripten](https://emscripten.org/), and Python 3.

\`\`\`bash
git clone https://github.com/YOUR_USERNAME/qm-journal
cd qm-journal
npm install
./build.sh        # compile C++ to WebAssembly
npm run dev       # serve at localhost:4321
\`\`\`

## Entries

- **Lecture 00** — Wave functions, Normalization, Expected values
- **Exp. 01** — The particle in a box

## Architecture

[Brief paragraph about the design — the split between C++ physics and JS visualization, the MDX-as-content authoring, etc.]

## License

MIT (see LICENSE)
