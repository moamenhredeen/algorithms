package me.moamenhredeen.leetcode;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.function.Function;

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
public class TwoSum implements Function<TwoSum.Request, TwoSum.Response> {

    @Override
    public TwoSum.Response apply(TwoSum.Request req) {
        var map = new HashMap<Integer, Integer>();
        for (int i = 0; i < req.nums().size(); i++) {
            if (map.containsKey(req.nums().get(i))) {
                return new Response(List.of(i, map.get(req.nums().get(i))));
            }
            map.put((req.target() - req.nums().get(i)), i);
        }
        return new Response(Collections.emptyList());
    }

    public record Request(List<Integer> nums, Integer target) {
    }

    public record Response(List<Integer> indices) {
    }
}
