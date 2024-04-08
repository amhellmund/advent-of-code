import {isValidIndex, isNumber, isSymbol, Engine} from './day03';

describe("setting up engine", () => {
    const engine: Engine = {
        rows: 3,
        columns: 5,
        data: [
            "..#12",
            "1.234",
            "...#5",
        ],
    }

    test("isValidIndex", () => {
        expect(isValidIndex(engine, 0, 0)).toBe(true);
        expect(isValidIndex(engine, 1, 2)).toBe(true);
        expect(isValidIndex(engine, 3, 5)).toBe(false);
        expect(isValidIndex(engine, -1, -1)).toBe(false);
    })

    test("isNumber", () => {
        expect(isNumber(engine, -1, -1)).toBe(false);
        expect(isNumber(engine, 0, 0)).toBe(false);
        expect(isNumber(engine, 0, 3)).toBe(true);
        expect(isNumber(engine, 2, 3)).toBe(false);
    });

    test("isSymbol", () => {
        expect(isSymbol(engine, 3, 5)).toBe(false);
        expect(isSymbol(engine, 0, 0)).toBe(false);
        expect(isSymbol(engine, 1, 0)).toBe(false);
        expect(isSymbol(engine, 0, 2)).toBe(true);
    })
});