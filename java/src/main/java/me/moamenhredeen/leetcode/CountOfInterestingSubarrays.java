package me.moamenhredeen.leetcode;

import java.util.List;
import java.util.function.Function;

/// You are given a 0-indexed integer array `nums`, an integer `modulo`, and an integer `k`.
/// Your task is to find the count of subarrays that are interesting.
/// A subarray `nums[l..r]` is interesting if the following condition holds:
/// Let `cnt` be the number of indices i in the range `[l, r]` such that `nums[i] % modulo == k`. Then, `cnt % modulo == k`.
/// Return an integer denoting the count of interesting subarrays.
/// > [NOTE]: A subarray is a **contiguous** non-empty sequence of elements within an array.

public class CountOfInterestingSubarrays implements Function<CountOfInterestingSubarrays.Request, CountOfInterestingSubarrays.Response> {

    @Override
    public CountOfInterestingSubarrays.Response apply(CountOfInterestingSubarrays.Request request) {
        var nums = request.nums();
        var modulo = request.modulo();
        var k = request.k();

        int cnt = 0;
        int interesting = 0;
        for (int i = 0; i < nums.size(); i++) {
            cnt = 0;
            for (int j = i; j < nums.size(); j++) {
                if (nums.get(j) % modulo == k) {
                    cnt++;
                }

                if (cnt % modulo == k) {
                    interesting++;
                }
            }
        }

        return new Response(interesting);
    }

    public record Request(List<Integer> nums, Integer modulo, Integer k) {
    }

    public record Response(Integer count) {
    }
}
