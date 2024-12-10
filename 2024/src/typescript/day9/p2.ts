import { parseInput } from "../utils/readFile";

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day9.txt';

async function solution() {
  // Assuming `parseInput` is a function that reads the input file and returns its content as a string
  const file = await parseInput(filePath, true);
  if (typeof file !== 'string') {
    throw new Error('Expected a string');
  }

  // Parse the input into numbers
  const data: number[] = file.trim().replace(/\r/g, '').split('').map(Number);

  const unpackedDisk: (number | string)[][] = [];

  // Unpack the disk
  for (let i = 0; i < data.length; i++) {
    const file: (number | string)[] = [];
    for (let j = data[i]; j > 0; j--) {
      if (i % 2 === 0) {
        file.push(i / 2); // Use number for even indices
      } else {
        file.push('.'); // Use string '.' for odd indices
      }
    }
    if (file.length) {
      unpackedDisk.push(file);
    }
  }

  // Defrag the disk
  const movedIds: number[] = [];
  outer: for (let i = unpackedDisk.length - 1; i >= 0; i--) {
    if (typeof unpackedDisk[i][0] === 'number' && !movedIds.includes(unpackedDisk[i][0] as number)) {
      for (let j = 0; j <= i; j++) {
        if (
          unpackedDisk[j][0] === '.' &&
          unpackedDisk[j].length >= unpackedDisk[i].length
        ) {
          if (unpackedDisk[j].length === unpackedDisk[i].length) {
            movedIds.push(unpackedDisk[i][0] as number);
            const temp = [...unpackedDisk[j]];
            unpackedDisk[j] = unpackedDisk[i];
            unpackedDisk[i] = temp;
            continue outer;
          } else {
            movedIds.push(unpackedDisk[i][0] as number);
            const temp = [...unpackedDisk[i]];
            unpackedDisk[i].fill('.');
            unpackedDisk.splice(
              j,
              1,
              temp,
              unpackedDisk[j].slice(unpackedDisk[i].length)
            );
            i++;
            continue outer;
          }
        }
      }
    }
  }

  // Flatten the defragged disk
  const defraggedDisk: (number | string)[] = unpackedDisk.flat();

  let checksum = 0;

  // Calculate the checksum
  defraggedDisk.forEach((block, id) => {
    if (typeof block === 'number') {
      checksum += block * id;
    }
  });

  console.log(checksum); // Output the result
}

solution();