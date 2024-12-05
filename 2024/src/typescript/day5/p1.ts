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

  const pageOrderingRulesMap = new Map<number, number[]>();
  let sum = 0;

  pageOrderingRulesArray.forEach((pageOrderingRule) => {
    const [first, last] = pageOrderingRule.split('|').map(Number);
    if (!pageOrderingRulesMap.has(first)) {
      pageOrderingRulesMap.set(first, []);
    } 
    pageOrderingRulesMap.get(first)?.push(last);
  });

  pageNumbersOfUpdatesArray.forEach((pageNumbersOfUpdates) => {
    const pages = pageNumbersOfUpdates.split(',').map(Number);
    let isPossible = true;
    for (let i = 0; i < pages.length - 1; i++) {
      const valArray = pageOrderingRulesMap.get(pages[i]);
      if (valArray?.includes(pages[i + 1])) {
        continue;
      } else {
        isPossible = false
      }
    }
    if (isPossible) {
      const middle = Math.floor(pages.length / 2);
      sum += pages[middle];
    }
  });

  console.log(sum);
}

solution()