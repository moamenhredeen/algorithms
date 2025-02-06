use std::vec::Vec;

/// merge sort
pub fn sort(arr: &[i32]) -> Vec<i32> {

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

    use super::sort;

    #[test]
    fn sort_empty_collection() {
        let arr = vec![];
        let sorted = sort(&arr);
        assert_eq!(sorted, vec![]);
    }


    #[test]
    fn sort_one_element_collection() {
        let arr = vec![1];
        let sorted = sort(&arr);
        assert_eq!(sorted, vec![1]);
    }


    #[test]
    fn sort_multiple_item_collection() {
        let arr = vec![2, 1, 3, 7, 6, 4, 5, 9, 8, 0];
        let sorted = sort(&arr);
        assert_eq!(sorted, vec![0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }
}

