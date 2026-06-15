// Astro's import.meta.glob is statically analyzed at build time.
// This returns an object mapping file paths to their raw source content.
// All work happens at build time — no runtime file I/O.

const mdxModules = import.meta.glob('/src/pages/*.mdx', {
  query: '?raw',
  import: 'default',
  eager: true,
});

const WIKILINK_RE = /<WikiLink\s+[^>]*slug\s*=\s*["']([^"']+)["'][^>]*\/?>/g;

// Build the backlink map once, when this module is first imported.
const backlinkMap = (() => {
  const result = {};

  for (const [filepath, content] of Object.entries(mdxModules)) {
    // Extract slug from filepath: '/src/pages/lecture-00.mdx' → 'lecture-00'
    const filename = filepath.split('/').pop();
    const sourceSlug = filename.replace(/\.mdx$/, '');

    let match;
    WIKILINK_RE.lastIndex = 0;
    while ((match = WIKILINK_RE.exec(content)) !== null) {
      const targetSlug = match[1];
      if (targetSlug === sourceSlug) continue;
      if (!result[targetSlug]) result[targetSlug] = new Set();
      result[targetSlug].add(sourceSlug);
    }
  }

  // Convert Sets to sorted arrays
  const final = {};
  for (const target in result) {
    final[target] = Array.from(result[target]).sort();
  }
  return final;
})();

export function getBacklinks(slug) {
  return backlinkMap[slug] || [];
}