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

function findExpression(nums: number[], target: number): boolean {
  // Recursively try all possible expressions
  function backtrack(index: number, currentVal: number): boolean {
    // Base case: we've used all numbers
    if (index === nums.length) {
      return currentVal === target;
    }
    
    // Try adding current number
    if (backtrack(index + 1, currentVal + nums[index])) {
      return true;
    }
    
    // Try multiplying current number
    if (backtrack(index + 1, currentVal * nums[index])) {
      return true;
    }
    
    // If this is the first number, just use it
    if (index === 0) {
      return backtrack(index + 1, nums[index]);
    }
    
    return false;
  }
  
  return backtrack(0, 0);
}


solution()
