import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day1.txt';

async function solution() {
  const file = await parseInput(filePath);
  if (typeof file === 'string') {
    throw new Error('Expected an array of strings');
  }
  
  const counter = new Map<number, number>()

  // Loop through and put each item in the respective arrays
  file.forEach((item) => {
    const [_left, ...rest] = item.split(' ').map(Number)
    const rightValue = rest[rest.length - 1]

    counter.set(rightValue, (counter.get(rightValue) || 0) + 1)
  })

  const similarities = file.map((item) => {
    const [left] = item.split(' ').map(Number);
    return left * (counter.get(left) || 0);
  })

  const sum = similarities.reduce((acc, curr) => acc + curr, 0)
  console.log(sum)
}

solution()