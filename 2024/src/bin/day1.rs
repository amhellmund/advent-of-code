use aoc2024::collections::construct_counter;
use aoc2024::io::{get_data_for_day, read_file_into_lines_with_numbers};

fn compute_part1(mut first_column: Vec<i32>, mut second_column: Vec<i32>) {
    first_column.sort();
    second_column.sort();

    let result: i32 = std::iter::zip(first_column, second_column)
        .map(|(first, second)| (first - second).abs())
        .sum();
    println!("The result of day01 - part01 is: {}", result);
}

fn compute_part2(first_column: &Vec<i32>, second_column: &Vec<i32>) {
    let counter = construct_counter(second_column);
    let result: i32 = first_column
        .iter()
        .map(|value| value * counter.get(value).or(Some(&0)).unwrap())
        .sum();

    println!("The result of day01 - part02 is: {}", result);
}

fn main() {
    let values = read_file_into_lines_with_numbers(&get_data_for_day(1));

    let first_column: Vec<i32> = values.iter().map(|values| values[0]).collect();
    let second_column: Vec<i32> = values.iter().map(|values| values[1]).collect();
    assert_eq!(first_column.len(), second_column.len());

    compute_part1(first_column.clone(), second_column.clone());
    compute_part2(&first_column, &second_column);
}
