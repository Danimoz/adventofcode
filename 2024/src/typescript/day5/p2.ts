import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day5.txt';

async function solution() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  const [pageOrderingRules, pageNumbersOfUpdates] = file.split('\n\n');
  const pageOrderingRulesArray = pageOrderingRules.split('\n');
  const pageNumbersOfUpdatesArray = pageNumbersOfUpdates.split('\n');

  const pageOrderingRulesMap = new Map<number, Set<number>>();
  let sum = 0;

  // Parse rules into a map
  pageOrderingRulesArray.forEach((pageOrderingRule) => {
    const [first, last] = pageOrderingRule.split('|').map(Number);
    if (!pageOrderingRulesMap.has(first)) {
      pageOrderingRulesMap.set(first, new Set());
    }
    pageOrderingRulesMap.get(first)?.add(last);
  });

  // Function to check if an update follows the rules
  function isValidUpdate(pages: number[]): boolean {
    const pageSet = new Set(pages);
    for (const [key, values] of pageOrderingRulesMap) {
      if (!pageSet.has(key)) continue;
      for (const value of values) {
        if (pageSet.has(value)) {
          // Validate order in the update
          if (pages.indexOf(key) >= pages.indexOf(value)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  // MergeSort with custom comparison based on ordering rules
  function mergeSort(arr: number[]): number[] {
    if (arr.length <= 1) return arr;

    const mid = Math.floor(arr.length / 2);
    const left = mergeSort(arr.slice(0, mid));
    const right = mergeSort(arr.slice(mid));

    return merge(left, right);
  }

  function merge(left: number[], right: number[]): number[] {
    const result: number[] = [];
    while (left.length && right.length) {
      const leftPage = left[0];
      const rightPage = right[0];

      // Custom comparison using ordering rules
      if (comesBefore(leftPage, rightPage)) {
        result.push(left.shift()!);
      } else {
        result.push(right.shift()!);
      }
    }
    return [...result, ...left, ...right];
  }

  function comesBefore(a: number, b: number): boolean {
    // If there's a direct rule a|b, a comes before b
    return pageOrderingRulesMap.get(a)?.has(b) ?? false;
  }

  // Process each update
  pageNumbersOfUpdatesArray.forEach((pageNumbersOfUpdates) => {
    let pages = pageNumbersOfUpdates.split(',').map(Number);

    if (!isValidUpdate(pages)) {
      // Reorder the pages
      pages = mergeSort(pages);

      // Find the middle page of the reordered array
      const mid = Math.floor(pages.length / 2);
      sum += pages[mid];
    }
  });

  console.log(sum);
}

solution();



// Using a Topological Sort approach with a Graph
async function solution2() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  const [pageOrderingRules, pageNumbersOfUpdates] = file.split('\n\n');
  const pageOrderingRulesArray = pageOrderingRules.split('\n');
  const pageNumbersOfUpdatesArray = pageNumbersOfUpdates.split('\n');

  // Create a map to store ordering rules
  const pageOrderingRulesMap = new Map<number, number[]>();
  pageOrderingRulesArray.forEach((pageOrderingRule) => {
    const [first, last] = pageOrderingRule.split('|').map(Number);
    if (!pageOrderingRulesMap.has(first)) {
      pageOrderingRulesMap.set(first, []);
    }
    pageOrderingRulesMap.get(first)?.push(last);
  });

  let sum = 0;

  // Function to reorder pages using topological sort
  function reorderPages(pages: number[]): number[] {
    // Build the graph for the current update
    const inDegree = new Map<number, number>();
    const graph = new Map<number, number[]>();

    // Initialize graph nodes
    pages.forEach((page) => {
      inDegree.set(page, 0);
      graph.set(page, []);
    });

    // Add edges based on relevant rules
    for (const [key, values] of pageOrderingRulesMap) {
      if (!pages.includes(key)) continue;
      values.forEach((value) => {
        if (pages.includes(value)) {
          graph.get(key)?.push(value);
          inDegree.set(value, (inDegree.get(value) || 0) + 1);
        }
      });
    }

    // Topological sort using Kahn's algorithm
    const sorted: number[] = [];
    const queue: number[] = [];

    // Find all nodes with in-degree 0
    inDegree.forEach((degree, node) => {
      if (degree === 0) queue.push(node);
    });

    while (queue.length > 0) {
      const current = queue.shift()!;
      sorted.push(current);

      graph.get(current)?.forEach((neighbor) => {
        inDegree.set(neighbor, inDegree.get(neighbor)! - 1);
        if (inDegree.get(neighbor) === 0) {
          queue.push(neighbor);
        }
      });
    }

    return sorted;
  }

  // Process each update
  pageNumbersOfUpdatesArray.forEach((pageNumbersOfUpdates) => {
    const pages = pageNumbersOfUpdates.split(',').map(Number);

    // Validate the update
    const isValid = (() => {
      const pageSet = new Set(pages);
      for (const [key, values] of pageOrderingRulesMap) {
        if (!pageSet.has(key)) continue;
        for (const value of values) {
          if (pageSet.has(value) && pages.indexOf(key) >= pages.indexOf(value)) {
            return false;
          }
        }
      }
      return true;
    })();

    if (!isValid) {
      // Reorder the pages
      const reordered = reorderPages(pages);
      const middleIndex = Math.floor(reordered.length / 2);
      sum += reordered[middleIndex];
    }
  });

  console.log(sum);
}

solution2();
