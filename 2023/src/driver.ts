import day01 from "./day01";
import day02 from "./day02";
import day03 from "./day03";

import { match } from 'ts-pattern';

if (process.argv.length <= 2) {
    console.error(`Usage: ${process.argv[1]} <day-number>`);
    process.exit(1);
}

const day = process.argv[2];
match(day)
    .with("01", () => day01())
    .with("02", () => day02())
    .with("03", () => day03())
    .otherwise(() => console.error(`Invalid day selection: ${day}`));