import {extractGameRound, extractSingleCube, extractDraw, readGame, isValidGame} from './day02';

test("valid game rounds", () => {
    expect(extractGameRound("Game 1")).toBe(1);
    expect(extractGameRound("Game 10")).toBe(10);
    expect(extractGameRound("Game 999")).toBe(999);
});

test("invalid game input", () => {
    expect(() => extractGameRound("ABC 10")).toThrow("invalid input");
});

test("all three colors - single color input", () => {
    expect(extractSingleCube("red", "12 red")).toBe(12);
    expect(extractSingleCube("green", "15 green")).toBe(15);
    expect(extractSingleCube("blue", "30 blue")).toBe(30);
});

test("all three colors - multi color input", () => {
    expect(extractSingleCube("red", "12 red, 15 blue")).toBe(12);
    expect(extractSingleCube("green", "16 red, 15 green")).toBe(15);
    expect(extractSingleCube("blue", "12 red, 30 blue, 10 green")).toBe(30);
});

test("color is not contained", () => {
    expect(extractSingleCube("red", "12 blue")).toBe(0);
    expect(extractSingleCube("yellow", "")).toBe(0);
});

test("draw with one color", () => {
    expect(extractDraw("12 red")).toStrictEqual({red: 12, green: 0, blue: 0});
    expect(extractDraw("30 green")).toStrictEqual({red: 0, green: 30, blue: 0});
    expect(extractDraw("60 blue")).toStrictEqual({red: 0, green: 0, blue: 60});
})

test("draw with two colors", () => {
    expect(extractDraw("12 red, 20 green")).toStrictEqual({red: 12, green: 20, blue: 0});
    expect(extractDraw("30 green, 99 blue")).toStrictEqual({red: 0, green: 30, blue: 99});
    expect(extractDraw("60 blue, 1 red")).toStrictEqual({red: 1, green: 0, blue: 60});
})

test("draw with three colors", () => {
    expect(extractDraw("12 red, 4 blue, 20 green")).toStrictEqual({red: 12, green: 20, blue: 4});
    expect(extractDraw("30 green, 99 blue, 10 red")).toStrictEqual({red: 10, green: 30, blue: 99});
    expect(extractDraw("0 green, 60 blue, 1 red")).toStrictEqual({red: 1, green: 0, blue: 60});
})

test("read complete game", () => {
    expect(readGame("Game 10: 1 red, 2 green, 3 blue; 4 blue; 5 red, 6 green")).toStrictEqual(
        {
            round: 10,
            draws: [
                {
                    red: 1,
                    green: 2,
                    blue: 3,
                },
                {
                    red: 0,
                    green: 0,
                    blue: 4,
                },
                {
                    red: 5,
                    green: 6,
                    blue: 0,
                }
            ]
        }
    );
});

test("is valid game", () => {
    expect(isValidGame({round: 1, draws: [{red: 1, green: 1, blue: 1}]}, {red: 5, green: 5, blue: 5})).toBe(true);
});

test("is invalid game", () => {
    expect(isValidGame({round: 1, draws: [{red: 1, green: 1, blue: 10}]}, {red: 5, green: 5, blue: 5})).toBe(false);
});