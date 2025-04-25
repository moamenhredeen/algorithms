package me.moamenhredeen.leetcode;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

class CountOfInterestingSubarraysTest {

    /// # Explanation
    /// In this example the interesting subarrays are:
    /// The subarray `nums[0..0]` which is `[3]`.
    /// - There is only one index, i = 0, in the range `[0, 0]` that satisfies `nums[i] % modulo == k`.
    /// - Hence, `cnt = 1` and `cnt % modulo == k`.
    /// The subarray `nums[0..1]` which is `[3,2]`.
    /// - There is only one index, `i = 0`, in the range `[0, 1]` that satisfies `nums[i] % modulo == k`.
    /// - Hence, `cnt = 1` and `cnt % modulo == k`.
    /// The subarray `nums[0..2]` which is `[3,2,4]`.
    /// - There is only one index, `i = 0`, in the range `[0, 2]` that satisfies `nums[i] % modulo == k`.
    /// - Hence, `cnt = 1` and `cnt % modulo == k`.
    /// It can be shown that there are no other interesting subarrays.
    /// So, the answer is `3`.
    @Test
    void testcase1() {
        var countOfInterestingSubarrays = new CountOfInterestingSubarrays();
        var req = new CountOfInterestingSubarrays.Request(List.of(3, 2, 4), 2, 1);
        var res = countOfInterestingSubarrays.apply(req);
        assertThat(res.count()).isEqualTo(3);
    }


    /// # Explanation
    /// In this example the interesting subarrays are:
    /// The subarray `nums[0..3]` which is `[3,1,9,6]`.
    /// - There are three indices, `i = 0, 2, 3`, in the range `[0, 3]` that satisfy `nums[i] % modulo == k`.
    /// - Hence, `cnt = 3` and `cnt % modulo == k`.
    /// The subarray `nums[1..1]` which is `[1]`.
    /// - There is no index, `i`, in the range `[1, 1]` that satisfies `nums[i] % modulo == k`.
    /// - Hence, `cnt = 0` and `cnt % modulo == k`.
    /// It can be shown that there are no other interesting subarrays.
    /// So, the answer is `2`.
    @Test
    void testcase2() {
        var countOfInterestingSubarrays = new CountOfInterestingSubarrays();
        var req = new CountOfInterestingSubarrays.Request(List.of(3, 1, 9, 6), 3, 0);
        var res = countOfInterestingSubarrays.apply(req);
        assertThat(res.count()).isEqualTo(2);
    }

}