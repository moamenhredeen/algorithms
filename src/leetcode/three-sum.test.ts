import { threeSum } from "./three-sum";
import { describe, test, expect } from "vitest";

describe("leetcode: three sum", () => {
    test("test case 1", () => {
        const res = threeSum([-1, 0, 1, 2, -1, -4]);

        let expected = [
            [-1, -1, 2],
            [-1, 0, 1],
        ];
        expect(res.map((el) => el.toSorted()).toSorted()).toEqual(
            expected.map((el) => el.toSorted()).toSorted(),
        );
    });

    test("test case 2", () => {
        const res = threeSum([0, 1, 1]);
        res.sort();
        expect(res).toEqual([]);
    });

    test("test case 3", () => {
        const res = threeSum([0, 0, 0]);
        res.sort();
        expect(res).toEqual([[0, 0, 0]]);
    });
});
