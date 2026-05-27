// Scans all MDX files in src/pages/ for <WikiLink slug="..." /> references.
// Returns a map: targetSlug → array of sourceSlugs that reference it.

import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const pagesDir = path.resolve(__dirname, '../pages');

// Match: <WikiLink slug="some-slug" ... />  or  <WikiLink slug='some-slug' />
const WIKILINK_RE = /<WikiLink\s+[^>]*slug\s*=\s*["']([^"']+)["'][^>]*\/?>/g;

let cached = null;

function scan() {
  const result = {};   // targetSlug → Set of sourceSlugs

  const files = fs.readdirSync(pagesDir).filter((f) => f.endsWith('.mdx'));
  for (const file of files) {
    const sourceSlug = file.replace(/\.mdx$/, '');
    const content = fs.readFileSync(path.join(pagesDir, file), 'utf8');

    let match;
    WIKILINK_RE.lastIndex = 0;
    while ((match = WIKILINK_RE.exec(content)) !== null) {
      const targetSlug = match[1];
      if (targetSlug === sourceSlug) continue;  // skip self-references
      if (!result[targetSlug]) result[targetSlug] = new Set();
      result[targetSlug].add(sourceSlug);
    }
  }

  // Convert Sets to sorted arrays for stable output
  const final = {};
  for (const target in result) {
    final[target] = Array.from(result[target]).sort();
  }
  return final;
}

// Public API: get backlinks for a given slug.
export function getBacklinks(slug) {
  // In dev we re-scan every call (cheap); in production cache it.
  if (process.env.NODE_ENV === 'production') {
    if (!cached) cached = scan();
    return cached[slug] || [];
  }
  return scan()[slug] || [];
}