/// # insertion sort
/// type: in place
/// order/rate of growth
/// - best case: n
/// - average/worst case: n2
#[allow(dead_code)]
pub fn insertion_sort<T>(arr: &mut [T])
where
    T: Ord + Copy,
{
    for i in 1..arr.len() {
        let cur = arr[i];
        let mut j = i;
        while j > 0 && arr[j - 1] > cur {
            arr[j] = arr[j - 1];
            j -= 1;
        }
        arr[j] = cur;
    }
}

#[cfg(test)]
mod test {

    use super::insertion_sort;

    #[test]
    fn sort_empty_collection() {
        let mut arr = Vec::<u32>::new();
        insertion_sort(&mut arr);
        assert_eq!(arr, vec![]);
    }

    #[test]
    fn sort_one_element_collection() {
        let mut arr = vec![1];
        insertion_sort(&mut arr);
        assert_eq!(arr, vec![1]);
    }

    #[test]
    fn sort_a_sorted_collection() {
        let mut arr = vec![1, 2, 3];
        insertion_sort(&mut arr);
        assert_eq!(arr, vec![1, 2, 3]);
    }

    #[test]
    fn sort_multiple_item_vector() {
        let mut arr = vec![2, 1, 3, 7, 6, 4, 5, 9, 8, 0];
        insertion_sort(&mut arr);
        assert_eq!(arr, vec![0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn sort_multiple_item_array() {
        let mut arr: [u32; 10] = [2, 1, 3, 7, 6, 4, 5, 9, 8, 0];
        insertion_sort(&mut arr);
        assert_eq!(arr, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
    }

    #[test]
    fn sort_collection_with_repeated_items() {
        let mut arr: [u32; 6] = [1, 2, 3, 1, 2, 3];
        insertion_sort(&mut arr);
        assert_eq!(arr, [1, 1, 2, 2, 3, 3]);
    }
}
