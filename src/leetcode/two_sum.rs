//! # [LeetCode: Two Sum](https://leetcode.com/problems/two-sum/description/)
//! Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//! You may assume that each input would have exactly one solution, and you may not use the same element twice.
//! You can return the answer in any order.
//!
//! ## Example 1:
//! Input: nums = [2,7,11,15], target = 9
//! Output: [0,1]
//! Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
//!
//! ## Example 2:
//! Input: nums = [3,2,4], target = 6
//! Output: [1,2]
//!
//! ## Example 3:
//! Input: nums = [3,3], target = 6
//! Output: [0,1]
//!
//! ## Constraints:
//! 2 <= nums.length <= 104
//! -109 <= nums[i] <= 109
//! -109 <= target <= 109
//! Only one valid answer exists.
//!
//! Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

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
