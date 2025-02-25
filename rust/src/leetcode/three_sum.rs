//! LeetCode: [3Sum](https://leetcode.com/problems/3sum/description/?envType=problem-list-v2&envId=sorting)
//! Given an integer array nums,
//! return all the triplets
//! [nums[i], nums[j], nums[k]]
//! such that
//! i != j, i != k, and j != k,
//! and
//! nums[i] + nums[j] + nums[k] == 0.
//! Notice that the solution set must not contain duplicate triplets.

/// the first obvious solution is to get all
/// permutations that sum up to zero
fn three_sum(arr: Vec<i32>) -> Vec<Vec<i32>> {
    let mut res: Vec<Vec<i32>> = Vec::new();

    // split array
    // [-4, -1, -1]
    // [0]
    // [1, 2, 3, 4]
    // -4: 1, 2
    // map:
    // -> -4: 1
    // ->

    // note: (1,1,1)
    // 1 2 3 4 5
    //
    // i:1
    // j:2
    // z:3, 4, 5
    //
    // i:1
    // j:3
    // z:4, 5
    //
    // i:1
    // j:4
    // z:5
    //
    // i: 2
    // 1
    for i in 0..arr.len() {
        for j in (i + 1)..arr.len() {
            for z in (j + 1)..arr.len() {
                if arr[i] + arr[j] + arr[z] == 0 {
                    res.push(Vec::from([arr[i], arr[j], arr[z]]));
                }
            }
        }
    }
    res
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example_1() {
        let arr = vec![-1, 0, 1, 2, -1, -4];
        let res = three_sum(arr);
        assert_eq!(res, [[-1, -1, 2], [-1, 0, 1]]);
    }
}
