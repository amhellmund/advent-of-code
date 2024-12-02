use std::fs::read_to_string;
use std::path::{Path, PathBuf};

pub fn read_file_into_lines(path: &Path) -> Vec<String> {
    let content = read_to_string(path).expect("Input file is exists and is readable");
    content.lines().map(|line| String::from(line)).collect()
}

fn get_base_dir_for_test_data() -> PathBuf {
    let base = PathBuf::from(
        std::env::var("CARGO_MANIFEST_DIR")
            .expect("Environment variable 'CARGO_MANIFEST_DIR' is set."),
    );
    base.join("data")
}

pub fn get_data_for_day(day: i8) -> PathBuf {
    get_base_dir_for_test_data().join(format!("day{:02}.txt", day))
}

#[cfg(test)]
mod tests {
    use std::{fs::File, io::Write};

    #[test]
    fn test_read_file_into_lines() {
        let testdir = tempfile::tempdir().unwrap();
        let testfile = testdir.path().join("test.txt");

        {
            let mut file_handle = File::create(&testfile).unwrap();
            file_handle.write(b"line1\n").unwrap();
            file_handle.write(b"line2").unwrap();
            file_handle.flush().unwrap();
        }

        let test_data = crate::read_file_into_lines(&testfile);
        assert_eq!(test_data.len(), 2);
        assert_eq!(test_data[0], "line1");
        assert_eq!(test_data[1], "line2");
    }

    #[test]
    fn test_get_data_dir() {
        assert!(crate::get_data_for_day(1)
            .ends_with(std::path::PathBuf::from("data").join("day01.txt")));
    }
}
