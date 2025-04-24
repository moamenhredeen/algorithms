package me.moamenhredeen.leetcode;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

class TwoSumTest {

    @Test
    void testcase1() {
        var twoSum = new TwoSum();
        var res = twoSum.apply(List.of(2, 7, 11, 15), 9);
        assertThat(res).containsExactlyInAnyOrder(0, 1);
    }


    @Test
    void testcase2() {
        var twoSum = new TwoSum();
        var res = twoSum.apply(List.of(3, 2, 4), 6);
        assertThat(res).containsExactlyInAnyOrder(1, 2);
    }

    @Test
    void testcase3() {
        var twoSum = new TwoSum();
        var res = twoSum.apply(List.of(3, 3), 6);
        assertThat(res).containsExactlyInAnyOrder(0, 1);
    }

}