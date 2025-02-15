use std::collections::HashMap;

pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut map: HashMap<i32, usize> = HashMap::new();
    let mut res: Vec<i32> = Vec::new();
    for (i, val) in nums.iter().enumerate() {
        if map.contains_key(&val) {
            res.push(i as i32);
            res.push(*map.get(&val).unwrap() as i32);
            break;
        }
        let diff = target - val;
        map.insert(diff, i);
    }
    res
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example_1() {
        let res = two_sum(vec![2, 7, 11, 15], 9);
        assert!(res.contains(&0));
        assert!(res.contains(&1));
    }

    #[test]
    fn example_2() {
        let res = two_sum(vec![2, 3, 4], 6);
        assert!(res.contains(&0));
        assert!(res.contains(&2));
    }

    #[test]
    fn example_3() {
        let res = two_sum(vec![3, 3], 6);
        assert!(res.contains(&0));
        assert!(res.contains(&1));
    }
}
