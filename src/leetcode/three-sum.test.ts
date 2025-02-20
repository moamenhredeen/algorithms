import { assertEquals } from "@std/assert";
import { threeSum } from "./three-sum.ts";

Deno.test("test case 1", () => {
    const res = threeSum([-1, 0, 1, 2, -1, -4]);
    res.sort();
    assertEquals(res, [
        [-1, -1, 2],
        [-1, 0, 1],
    ]);
});

Deno.test("test case 2", () => {
    const res = threeSum([0, 1, 1]);
    res.sort();
    assertEquals(res, []);
});

Deno.test("test case 3", () => {
    const res = threeSum([0, 0, 0]);
    res.sort();
    assertEquals(res, [[0, 0, 0]]);
});
