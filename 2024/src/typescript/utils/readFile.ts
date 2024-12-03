import { promises as fs } from "fs";

export async function parseInput(filePath: string) {
  const file = await fs.readFile(filePath, 'utf-8');
  return file.trim().split("\n");
}