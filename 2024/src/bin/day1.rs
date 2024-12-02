use std::collections::HashMap;

use aoc2024::{get_data_for_day, read_file_into_lines};

fn compute_part1(mut first_column: Vec<i32>, mut second_column: Vec<i32>) {
    first_column.sort();
    second_column.sort();

    let result: i32 = std::iter::zip(first_column, second_column)
        .map(|(first, second)| (first - second).abs())
        .sum();
    println!("The result of day01 - part01 is: {}", result);
}

fn compute_part2(first_column: Vec<i32>, second_column: Vec<i32>) {
    let mut counter: HashMap<i32, i32> = HashMap::new();
    for value in second_column {
        let value = counter.entry(value).or_insert(0);
        *value += 1;
    }

    let result: i32 = first_column
        .iter()
        .map(|value| value * counter.get(value).or(Some(&0)).unwrap())
        .sum();

    println!("The result of day01 - part02 is: {}", result);
}

fn main() {
    let lines = read_file_into_lines(&get_data_for_day(1));
    let values: Vec<Vec<i32>> = lines
        .iter()
        .map(|line| {
            line.split_ascii_whitespace()
                .map(|val| val.parse::<i32>().unwrap())
                .collect()
        })
        .collect();

    let first_column: Vec<i32> = values.iter().map(|values| values[0]).collect();
    let second_column: Vec<i32> = values.iter().map(|values| values[1]).collect();
    assert_eq!(first_column.len(), second_column.len());

    compute_part1(first_column.clone(), second_column.clone());
    compute_part2(first_column.clone(), second_column.clone());
}
