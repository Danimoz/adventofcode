import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day11.txt';

async function solution() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  const initialNumbers = file.split(' ').map(Number);
  const memo: Map<string, number> = new Map();

  /**
   * Recursively computes the size of the resulting list after applying the 
   * transformation t times starting from a single number x.
   * 
   * @param x - The initial number
   * @param t - The number of transformation steps remaining
   * @returns The length of the resulting list after t steps
   */
  function computeLength(x: number, t: number): number {
    if (t === 0) {
      return 1;
    }

    const key = `${x},${t}`;
    if (memo.has(key)) {
      return memo.get(key)!;
    }

    let result: number;
    if (x === 0) {
      result = computeLength(1, t - 1);
    } else if (x.toString().length % 2 === 0) {
      const mid = Math.floor(x.toString().length / 2);
      const left = Number(x.toString().slice(0, mid));
      const right = Number(x.toString().slice(mid));
      result = computeLength(left, t - 1) + computeLength(right, t - 1);
    } else {
      result = computeLength(x * 2024, t - 1);
    }

    memo.set(key, result);
    return result;
  }

  function computeFinalLengths(t: number): number {
    let total: number = 0;
    
    for (const num of initialNumbers) {
      total += computeLength(num, t);
    }
    
    return total;
  }

  console.log(`Total length after 25 steps: ${computeFinalLengths(25)}`);
  console.log(`Total length after 75 steps: ${computeFinalLengths(75)}`);
}

solution()