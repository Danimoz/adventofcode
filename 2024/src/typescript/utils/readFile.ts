import { promises as fs } from "fs";

export async function parseInput(filePath: string, dontSplit?: boolean) {
  const fileContent = (await fs.readFile(filePath, 'utf-8')).trim();
  return dontSplit ? fileContent : fileContent.split('\n');
}