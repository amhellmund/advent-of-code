use std::collections::HashMap;

/// Constructs a counter-like hashmap for integer numbers.
///
/// The keys of the hashmap represent the numbers in the input sequence, while
/// the values represent the counts how often the numbers occurred in the input sequence.
pub fn construct_counter(values: &Vec<i32>) -> HashMap<i32, i32> {
    let mut counter: HashMap<i32, i32> = HashMap::new();
    for value in values {
        let entry = counter.entry(*value).or_insert(0);
        *entry += 1;
    }
    counter
}

#[cfg(test)]
mod tests {
    use crate::collections::construct_counter;

    #[test]
    fn test_construct_counter() {
        let input = vec![1, 2, 3, 1, 2, 1];
        let counter = construct_counter(&input);

        assert_eq!(counter.len(), 3);
        assert_eq!(counter.get(&1), Some(&3));
        assert_eq!(counter.get(&2), Some(&2));
        assert_eq!(counter.get(&3), Some(&1));
    }
}
