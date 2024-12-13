import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day11.txt';


async function solution() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  let input = file.split(' '); // Start with an array of numbers as strings
  for (let i = 0; i < 25; i++) {
    const temp: string[] = [];
    input.forEach((numStr) => {
      const num = Number(numStr);
      if (num === 0) {
        temp.push('1');
      } else if (num.toString().length % 2 === 0) {
        const mid = Math.floor(num.toString().length / 2);
        const left = num.toString().slice(0, mid);
        const right = num.toString().slice(mid);
        temp.push(left, right);
      } else {
        temp.push((num * 2024).toString());
      }
    });
    input = temp; // Update input for the next iteration
  }

  console.log(input.length);
}


solution()

