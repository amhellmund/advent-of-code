import {determineCalibrationValue} from './day01';

test("only numbers", () => {
    expect(determineCalibrationValue("1")).toBe(11);
    expect(determineCalibrationValue("12")).toBe(12);
    expect(determineCalibrationValue("123")).toBe(13);
});

test("single digit", () => {
    expect(determineCalibrationValue("1sdfd")).toBe(11);
    expect(determineCalibrationValue("akdk3hs")).toBe(33);
    expect(determineCalibrationValue("ajdk9")).toBe(99);
});

test("digits are next to each other", () => {
    expect(determineCalibrationValue("10abc")).toBe(10);
    expect(determineCalibrationValue("abc53cde")).toBe(53);
    expect(determineCalibrationValue("abc30")).toBe(30);
});

test("first and last digit", () => {
    expect(determineCalibrationValue("3sldk9")).toBe(39);
});

test("three or more digits", () => {
    expect(determineCalibrationValue("1dkc9dldl3")).toBe(13);
    expect(determineCalibrationValue("ak4ksh39")).toBe(49);
    expect(determineCalibrationValue("ak391kjs9sk3")).toBe(33);
});

test("one word", () => {
    expect(determineCalibrationValue("one")).toBe(11);
    expect(determineCalibrationValue("two")).toBe(22);
    expect(determineCalibrationValue("three")).toBe(33);
    expect(determineCalibrationValue("four")).toBe(44);
    expect(determineCalibrationValue("five")).toBe(55);
    expect(determineCalibrationValue("six")).toBe(66);
    expect(determineCalibrationValue("seven")).toBe(77);
    expect(determineCalibrationValue("eight")).toBe(88);
    expect(determineCalibrationValue("nine")).toBe(99);
});

test("two words", () => {
    expect(determineCalibrationValue("onetwo")).toBe(12);
    expect(determineCalibrationValue("three4five")).toBe(35);
    expect(determineCalibrationValue("aeight0abnine")).toBe(89);
})

test("misc input", () => {
    expect(determineCalibrationValue("1dk4honethree3four")).toBe(14);
    expect(determineCalibrationValue("kcnine92onefour")).toBe(94);
    expect(determineCalibrationValue("1one4four6six9")).toBe(19);
    expect(determineCalibrationValue("twothreefdbl6five3zcqvcqxkcvdfkl4")).toBe(24);
    expect(determineCalibrationValue("98126")).toBe(96);
    expect(determineCalibrationValue("99")).toBe(99);
    expect(determineCalibrationValue("5z")).toBe(55);
    expect(determineCalibrationValue("twotj9l8onetwoned")).toBe(21);
    expect(determineCalibrationValue("23eightwo")).toBe(22);
})