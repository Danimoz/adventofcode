import { open } from 'fs/promises';

const filePath = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day4.txt';

async function solution(filePath: string) {
  const file = await open(filePath, 'r');
  let total = 0
  
  for await (const line of file.readLines()) {
    const cards = line.split('| ');
    // split input and remove empty strings
    const winningCards = cards[0].split(': ')[1].split(' ').filter(card => card !== '');
    const userCards = cards[1].split(' ').filter(card => card !== '');
    
    // check if user has winning cards
    const score = userCards.reduce((acc, card) => {
      return winningCards.includes(card) ? (acc === 0 ? 1 : acc * 2) : acc;
    }, 0);

    total += score;

  }
  console.log(total);
}

solution(filePath);