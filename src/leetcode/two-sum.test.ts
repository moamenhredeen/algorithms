import { assertEquals } from "@std/assert";
import { twoSum } from "./two-sum.ts";

Deno.test("test case 1", () => {
    const res = twoSum([2, 7, 11, 15], 9);
    res.sort();
    assertEquals(res, [0, 1]);
});

Deno.test("test case 2", () => {
    const res = twoSum([3, 2, 4], 6);
    res.sort();
    assertEquals(res, [1, 2]);
});

Deno.test("test case 3", () => {
    const res = twoSum([3, 3], 6);
    res.sort();
    assertEquals(res, [0, 1]);
});
