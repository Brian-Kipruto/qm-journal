# QM Journal

A working notebook for learning quantum mechanics by building it. Each entry pairs careful prose explanation with interactive widgets where the math is computed in C++ compiled to WebAssembly.

## Live site

[Deployment link will come here]

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

MIT License

Copyright (c) 2026 Kipruto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
