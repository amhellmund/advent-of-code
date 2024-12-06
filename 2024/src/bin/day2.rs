use aoc2024::io::{get_data_for_day, read_file_into_lines_with_numbers};

fn is_safe(line: &Vec<i32>) -> bool {
    let diff: Vec<i32> = line
        .windows(2)
        .map(|neighbors| neighbors[1] - neighbors[0])
        .collect();
    let strictly_increasing = diff.iter().all(|diff| *diff > 0);
    let strictly_decreasing = diff.iter().all(|diff| *diff < 0);
    let in_distance = diff.iter().all(|diff| diff.abs() <= 3);
    return (strictly_increasing || strictly_decreasing) && in_distance;
}

fn is_safe_with_tolerance(_line: &Vec<i32>) -> bool {
    return false;
}

fn compute_part2(values: &Vec<Vec<i32>>) {
    let result = values
        .iter()
        .filter(|line| is_safe_with_tolerance(line))
        .count();
    println!("The result for part2 is: {result}");
}

fn compute_part1(values: &Vec<Vec<i32>>) {
    let result = values.iter().filter(|line| is_safe(line)).count();
    println!("The result for part1 is: {result}");
}

fn main() {
    let values = read_file_into_lines_with_numbers(&get_data_for_day(2));

    compute_part1(&values);
    compute_part2(&values);
}
