import { readFileSync } from 'node:fs';

export function readData (data_path: string): string[] {
    return readFileSync(data_path).toString().split("\n");
}