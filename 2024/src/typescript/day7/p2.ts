import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day7.txt';

async function solution() {
  const file = await parseInput(filePath); 
  if (typeof file === 'string') {
    throw new Error('Expected an array of string');
  }
  
  let sum = 0;
  
  for (const line of file) {
    const [output, input] = line.split(': ');
    const nums = input.split(' ').map(Number);
    
    // Early exit if solution found
    const result = findExpression(nums, Number(output));
    if (result) {
      sum += Number(output);
    }
  }
  
  console.log(sum);
}

function findExpression(nums: number[], output: number){

  function backtrack(index: number, currentVal: number){
    if (index === nums.length) return currentVal === output

    const nextNum = nums[index]
    if (backtrack(index + 1, currentVal + nextNum)) return true
    if (backtrack(index + 1, currentVal * nextNum)) return true
    const concatenated = Number(`${currentVal}${nextNum}`);
    if (backtrack(index + 1, concatenated)) return true

    return false
  }
  return backtrack(1, nums[0])
}

solution()