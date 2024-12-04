import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day3.txt';

async function solution() {
  const file = await parseInput(filePath);
  if (typeof file === 'string') {
    throw new Error('Expected an array of strings');
  }
  
  const multRegex = /mul\(\d+,\d+\)/g;
  const numRegex = /\d+,\d+/g;

  let sum = 0
  file.forEach(input => {
    const match = input.match(multRegex)
    match?.forEach(item => {
      const nums = item.match(numRegex)
      if (nums){
        const itemsToMult = nums[0]
        const [first, second] = itemsToMult.split(',')
        const action = Number(first) * Number(second)
        sum += action
      }
    })
  })

  console.log(sum)
}

solution()