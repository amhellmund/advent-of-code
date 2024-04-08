import { readData } from "./utils";

export type Engine = {
    readonly rows: number,
    readonly columns: number,
    readonly data: string[],
}

function isDigit(char: string): boolean {
    return char >= '0' && char <= '9';
}

export function isValidIndex (engine: Engine, row: number, column: number): boolean {
    return row >= 0 && row < engine.rows && column >= 0 && column < engine.columns;
}

export function isNumber(engine: Engine, row: number, column: number): boolean {
    return isValidIndex(engine, row, column) && isDigit(engine.data[row][column]);
}

export function isSymbol(engine: Engine, row: number, column: number): boolean {
    return isValidIndex(engine, row, column) && !isDigit(engine.data[row][column]) && engine.data[row][column] != '.';
}

function isGear(engine: Engine, row: number, column: number): boolean {
    return isValidIndex(engine, row, column) && engine.data[row][column] == '*';
}

function constructEngine(data: string[]): Engine {
    const rows: number = data.length;
    let columns: number = 0;
    if (rows > 0) {
        columns = data[0].length;
        if (!data.every((element) => element.length == columns)) {
            throw new Error("Cannot construct engine: input data must have equal number of columns in each row.");
        } 
    }
    return {
        rows: rows,
        columns: columns,
        data: data,
    }
}

function parseNumber (value: string, start_index: number): [number, number] {
    let i = start_index;
    for (; i < value.length; i++) {
        if (!isDigit(value[i])) {
            break;
        }
    }
    return [parseInt(value.slice(start_index, i)), i];
}

function isSymbolAdjacent(engine: Engine, row_start: number, row_end_inclusive: number, column_start: number, column_end_inclusive: number): boolean {
    for (let i = row_start; i <= row_end_inclusive; ++i) {
        for (let j = column_start; j <= column_end_inclusive; ++j) {
            if (isSymbol(engine, i, j)) {
                return true;
            }
        }
    }
    return false;
}

function getPartNumbers (engine: Engine): number[] {
    let part_numbers: number[] = [];
    for (let i = 0; i < engine.rows; i++) {
        for (let j = 0; j < engine.columns;) {
            if (isNumber(engine, i, j)) {
                const [part_number, new_index] = parseNumber(engine.data[i], j);
                if (isSymbolAdjacent(engine, i-1, i+1, j-1, new_index)) {
                    part_numbers.push(part_number);
                }
                j = new_index;
            }
            else {
                ++j;
            }
        }
    }
    return part_numbers;
}

function runMissingParts(engine: Engine) {
    const part_numbers = getPartNumbers(engine);
    const part1_sum_value = part_numbers.reduce((acc, part_number) => acc + part_number, 0);
    console.log(`[Part1] Sum of part numbers: ${part1_sum_value}`);
}

type NumberWithIndexRange = {
    value: number,
    start: number,
    end: number,
}

function getNumbersWithIndices(engine: Engine): Map<number, NumberWithIndexRange[]> {
    let numbers_with_indices = new Map<number, NumberWithIndexRange[]>();
    for (let i = 0; i < engine.rows; ++i) {
        for (let j = 0; j < engine.columns;) {
            if (isNumber(engine, i, j)) {
                const [part_number, new_index] = parseNumber(engine.data[i], j);
                if (!numbers_with_indices.has(i)) {
                    numbers_with_indices.set(i, []);
                }
                numbers_with_indices.get(i)?.push({
                    value: part_number,
                    start: j,
                    end: new_index-1,
                });
                j = new_index;
            }
            else {
                ++j;
            }
            
        }
    }
    return numbers_with_indices;
}

function getNumbersAroundGear(engine: Engine, row: number, column: number, numbers_with_indices: Map<number, NumberWithIndexRange[]>): number[] {
    let row_start = row - 1;
    let row_end = row + 1;
    let column_start = column - 1;
    let column_end = column + 1;

    let numbers_around_gear: number[] = [];
    for (let i = row_start; i <= row_end; ++i) {
        const numbers = numbers_with_indices.get(i);
        if (numbers !== undefined) {
            for (const number of numbers) {
                if (!(number.end < column_start || number.start > column_end)) {
                    numbers_around_gear.push(number.value);
                }
            }
        }
    }
    return numbers_around_gear;
}

function getGearNumbers (engine: Engine): number[] {
    let gear_numbers: number[] = [];
    const numbers_with_indices = getNumbersWithIndices(engine);
    for (let i = 0; i < engine.rows; ++i) {
        for (let j = 0; j < engine.columns; ++j) {
            if (isGear(engine, i, j)) {
                const numbers_in_ranges = getNumbersAroundGear(engine, i, j, numbers_with_indices);
                if (numbers_in_ranges.length == 2) {
                    gear_numbers.push(numbers_in_ranges[0] * numbers_in_ranges[1]);
                }
            }
        }
    }
    return gear_numbers;
}

function runMissingGears(engine: Engine) {
    const gear_numbers: number[] = getGearNumbers(engine);
    const part2_sum_value = gear_numbers.reduce((acc, part_number) => acc + part_number, 0);
    console.log(`[Part2] Sum of gears: ${part2_sum_value}`);
}

export default function day03 () {
    const data = readData("src/data/day03.txt");
    const engine = constructEngine(data);
    runMissingParts(engine);
    runMissingGears(engine);
}
