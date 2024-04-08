import { readData } from "./utils";

const NAMED_DIGITS: [[string, string], string][] = [
    [["zero", "0"], "0"],
    [["one", "1"], "1"],
    [["two", "2"], "2"],
    [["three", "3"], "3"],
    [["four", "4"], "4"],
    [["five", "5"], "5"],
    [["six", "6"], "6"],
    [["seven", "7"], "7"],
    [["eight", "8"], "8"],
    [["nine", "9"], "9"],
];

function consumeCharacters (input: string, index: number): string | null {
    for (const [names, value] of NAMED_DIGITS) {
        for (const name of names) {
            if (input.length - index >= name.length && input.slice(index, index + name.length) === name) {
                return value;
            }
        }
    }
    return null;
}

export function determineCalibrationValue (input: string): number {
    let index = 0;
    let digits: string = "";
    while (index < input.length) {
        const value = consumeCharacters(input, index);
        if (value !== null) {
            digits = digits.concat(value);
        }
        index += 1;
    }
    const number = [digits.at(0), digits.at(-1)].join("");
    return parseInt(number);
}


export default function day01 () {
    const data = readData("src/data/day01.txt");
    const calibration_value = data.reduce((acc, line) => acc + determineCalibrationValue(line), 0);
    console.log(`[Part2] The calibration value is: ${calibration_value}`);
}