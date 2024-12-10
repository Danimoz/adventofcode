import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day9.txt';

async function solution() {
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  let disk: (number | null)[] = [];
  for (let i = 0; i < file.length; i++) {
    const char = Number(file[i]);
    for (let j = 0; j < char; j++) {
      if (i % 2 === 0) {
        disk.push(Math.floor(i / 2)); // Use numbers for file IDs
      } else {
        disk.push(null); // Use null for free spaces
      }
    }
  }

  let leftptr = 0;
  let rightptr = disk.length - 1;

  while (leftptr < rightptr) {
    while (disk[leftptr] !== null) leftptr++;
    while (disk[rightptr] === null) rightptr--;
    if (leftptr >= rightptr) break;

    // Swap blocks
    [disk[leftptr], disk[rightptr]] = [disk[rightptr], disk[leftptr]];
  }

  let sum = 0
  for (let k=0; k < disk.length; k++){
    if (disk[k] === null) break;
    sum += k * Number(disk[k])
  }
  
  console.log(sum);
}

solution()

