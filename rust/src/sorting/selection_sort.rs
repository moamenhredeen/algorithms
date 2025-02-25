/// selection sort
/// type: in place
/// order/rate of growth: n2
#[allow(dead_code)]
pub fn selection_sort<T>(arr: &mut [T])
where
    T: Ord + Copy,
{
    let mut min: T;
    for i in 0..arr.len() {
        // to make the implementation more effecient
        // we could check here if reach the last element
        // if so we continoue (when we reach the last element, the array
        // is already sorted)
        if i == arr.len() - 1 {
            continue;
        }
        let mut min_idx = i;
        let mut j = i + 1;
        while j < arr.len() {
            if arr[j] < arr[min_idx] {
                min_idx = j;
            }
            j += 1;
        }
        min = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = min;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty_collection() {
        let mut arr: [u32; 0] = [];
        selection_sort(&mut arr);
        assert_eq!(arr, []);
    }

    #[test]
    fn one_element_collection() {
        let mut arr: [u32; 1] = [1];
        selection_sort(&mut arr);
        assert_eq!(arr, [1]);
    }

    #[test]
    fn multiple_elements_collection() {
        let mut arr: [u32; 5] = [3, 2, 4, 1, 5];
        selection_sort(&mut arr);
        assert_eq!(arr, [1, 2, 3, 4, 5]);
    }

    #[test]
    fn sorted_collection() {
        let mut arr: [u32; 5] = [1, 2, 3, 4, 5];
        selection_sort(&mut arr);
        assert_eq!(arr, [1, 2, 3, 4, 5]);
    }

    #[test]
    fn reversed_sorted_collection() {
        let mut arr: [u32; 5] = [5, 4, 3, 2, 1];
        selection_sort(&mut arr);
        assert_eq!(arr, [1, 2, 3, 4, 5]);
    }
}
