import { twoSum } from "./two-sum";
import { describe, test } from "node:test";
import assert from 'assert/strict'

describe("leetcode: two sum", () => {
    test("test case 1", () => {
        const res = twoSum([2, 7, 11, 15], 9);
        res.sort();
        assert.deepEqual(res, [0, 1]);
    });

    test("test case 2", () => {
        const res = twoSum([3, 2, 4], 6);
        res.sort();
        assert.deepEqual(res, [1, 2]);
    });

    test("test case 3", () => {
        const res = twoSum([3, 3], 6);
        res.sort();
        assert.deepEqual(res, [0, 1]);
    });
});
