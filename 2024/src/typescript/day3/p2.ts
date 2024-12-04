import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day3.txt';

async function solution() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  let state = 'enabled';
  const validMulInstructions: string[] = [];

  const regex = /don't\(\)|\b\w*do\b|mul\(\d+,\d+\)*\)/g;
  const matches = file.matchAll(regex);
  const numRegex = /\d+,\d+/g;

  for (const match of matches) {
    const instr = match[0];

    if (instr === "don't()") {
      state = 'disabled'
    } else if (/^\w*do$/.test(instr)) {
      state = 'enabled';
    } else if (instr.startsWith('mul(')) {
      if (state == 'enabled') {
        validMulInstructions.push(instr)
      }
    }
  }

  let sum = 0

  for (const instr of validMulInstructions){
    const nums = instr.match(numRegex)
    if (nums) {
      const itemsToMult = nums[0]
        const [first, second] = itemsToMult.split(',')
        const action = Number(first) * Number(second)
        sum += action
    }
  }

  console.log(sum)
}

solution()