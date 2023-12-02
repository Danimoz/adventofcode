import { open } from 'fs/promises';

const filePath = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day2.txt';

async function solution(filePath: string) {
  const file = await open(filePath, 'r');
  let total = 0
  for await (const line of file.readLines()) {
    const lineArray = line.split(': ');
    const gameId = lineArray[0].split(' ')[1];
    const sets = lineArray[1].split('; ');

    let validGame = true;

    sets.forEach(set => {
      const cubes = set.split(', ').map(cube => cube.split(' '));
      cubes.forEach(([number, color]) => {
        if ((color === 'red' && Number(number) > 12) || (color === 'green' && Number(number) > 13) || (color === 'blue' && Number(number) > 14)) {
          validGame = false;
        }
      }); 
    });

    if (validGame) {
      total += Number(gameId);
    }
    
  }
  console.log(total); 

}

solution(filePath);