use std::vec::Vec;
use rand::Rng;

/// merge sort
pub fn merge_sort(arr: &[i32]) -> Vec<i32> {

    if arr.is_empty() || arr.len() == 1 {
        return arr.to_vec();
    }

    let mut sorted = Vec::with_capacity(arr.len());
    sorted.push(arr[0]);

    for i in 1..arr.len() {
        let mut j = i - 1;
        while (j != 0) && ( arr[i] < sorted[j] ) {
            sorted.insert(j + 1, sorted[j]);
            j -= 1;
        }

        sorted.insert(j + 1, arr[i]);
    }
    sorted
}


#[cfg(test)]
mod test {
     use rand::{rngs::mock::StepRng, Rng};

    use super::merge_sort;

    #[test]
    fn sort_empty_collection() {
        let arr = vec![];
        let sorted = merge_sort(&arr);
        assert_eq!(sorted, vec![]);
    }


    #[test]
    fn sort_one_element_collection() {
        let arr = vec![1];
        let sorted = merge_sort(&arr);
        assert_eq!(sorted, vec![1]);
    }


    #[test]
    fn sort_multiple_item_collection() {
        let arr = vec![2, 1, 3];
        let sorted = merge_sort(&arr);
        assert_eq!(sorted, vec![1, 2, 3]);
    }


    #[test]
    fn sort_large_collection() {
        let arr: [i32; 1000] = rand::rng().random();
        let sorted = merge_sort(&arr);
        assert!(sorted.is_sorted());
    }
}

