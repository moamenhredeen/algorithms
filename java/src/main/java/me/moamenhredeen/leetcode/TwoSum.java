package me.moamenhredeen.leetcode;

import java.util.HashMap;
import java.util.List;
import java.util.function.BiFunction;

/// # Two Sum
/// Given an array of integers nums and an integer target,
/// return indices of the two numbers such that they add up to target.
/// You may assume that each input would have exactly one solution,
/// and you may not use the same element twice.
/// You can return the answer in any order.
///
/// ## Example 1:
/// Input: nums = `[2,7,11,15]`, target = `9`
/// Output: `[0,1]`
/// Explanation: Because `nums[0] + nums[1] == 9`, we return `[0, 1]`.
///
/// ## Example 2:
/// Input: nums = `[3,2,4]`, target = `6`
/// Output: `[1,2]`
///
/// ## Example `3`:
/// Input: nums = `[3,3]`, target = `6`
/// Output: `[0,1]`
public class TwoSum implements BiFunction<List<Integer>, Integer, List<Integer>> {

    @Override
    public List<Integer> apply(List<Integer> list, Integer sum) {
        var map = new HashMap<Integer, Integer>();
        for (int i = 0; i < list.size(); i++) {
            if (map.containsKey(list.get(i))) {
                return List.of(i, map.get(list.get(i)));
            }
            map.put((sum - list.get(i)), i);
        }
        return List.of();
    }
}
