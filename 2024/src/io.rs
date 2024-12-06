use std::fs::read_to_string;
use std::path::{Path, PathBuf};

fn get_base_dir_for_test_data() -> PathBuf {
    let base = PathBuf::from(
        std::env::var("CARGO_MANIFEST_DIR")
            .expect("Environment variable 'CARGO_MANIFEST_DIR' is set."),
    );
    base.join("data")
}

/// Obtains the data file given the day number.
///
/// The parameter `day` indicates thereby which file to load.
/// The input files are expected to be stored in the top-level `data` directory.
pub fn get_data_for_day(day: i8) -> PathBuf {
    get_base_dir_for_test_data().join(format!("day{:02}.txt", day))
}

/// Reads a file into individual lines.
pub fn read_file_into_lines(path: &Path) -> Vec<String> {
    let content = read_to_string(path).expect("Input file is exists and is readable");
    content.lines().map(|line| String::from(line)).collect()
}

/// Reads a file linewise, splits each line at whitespaces and converts each entry to an integer number.
///
/// Example. Given the input file:
///
///   1 2 3
///   4 5 6
///
/// This function returns:
///
///   [
///     [1, 2, 3],
///     [4, 5, 6],
///   ]
pub fn read_file_into_lines_with_numbers(path: &Path) -> Vec<Vec<i32>> {
    read_file_into_lines(path)
        .iter()
        .map(|line| {
            line.split_ascii_whitespace()
                .map(|val| val.parse::<i32>().expect("Entries must contain numbers"))
                .collect()
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use crate::io::{get_data_for_day, read_file_into_lines, read_file_into_lines_with_numbers};
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn test_get_data_dir() {
        assert!(get_data_for_day(1).ends_with(std::path::PathBuf::from("data").join("day01.txt")));
    }

    fn write_test_file(path: &Path) {
        let mut file_handle = std::fs::File::create(path).unwrap();
        file_handle.write(b"1 2 3\n").unwrap();
        file_handle.write(b"4 5 6").unwrap();
        file_handle.flush().unwrap();
    }

    #[test]
    fn test_read_file_into_lines() {
        let testdir = tempfile::tempdir().unwrap();
        let testfile = testdir.path().join("test.txt");

        write_test_file(&testfile);

        let test_data = read_file_into_lines(&testfile);
        assert_eq!(test_data, vec!["1 2 3", "4 5 6"]);
    }

    #[test]
    fn test_read_file_into_lines_with_numbers() {
        let testdir = tempfile::tempdir().unwrap();
        let testfile = testdir.path().join("test.txt");

        write_test_file(&testfile);

        let test_data = read_file_into_lines_with_numbers(&testfile);
        assert_eq!(test_data, vec![[1, 2, 3], [4, 5, 6]]);
    }
}
