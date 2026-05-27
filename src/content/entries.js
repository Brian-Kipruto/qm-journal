// Single source of truth for all journal entries.
// When you add a new entry, add it here too.
// The order in this array determines display order in lists.

export const entries = [
  {
    slug: 'lecture-00',
    number: 'Lecture 00',
    title: 'Wave functions, Normalization, Expected values',
    description: "What ψ is, why we square it, and how to get real numbers out of complex math.",
    date: '2026-05-23',
    tags: ['Foundations', 'Wave function', 'Probability'],
  },
  {
    slug: 'exp-01',
    number: 'Exp. 01',
    title: 'The particle in a box',
    description: 'The simplest bound state: a particle confined to an infinite square well.',
    date: '2026-05-23',
    tags: ['Bound state', '1D', 'Time-independent'],
  },
];

// Helper: look up an entry by slug. Returns undefined if not found.
export function getEntry(slug) {
  return entries.find((e) => e.slug === slug);
}