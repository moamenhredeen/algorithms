import { insertionSort } from "./insertion-sort";
import { describe, test } from "node:test";
import assert from "assert/strict";

describe("insertion sort", () => {
    test("empty collection", () => {
        const arr: number[] = [];
        insertionSort(arr);
        assert.deepEqual(arr, []);
    });

    test("one element collection", () => {
        const arr: number[] = [1];
        insertionSort(arr);
        assert.deepEqual(arr, [1]);
    });

    test("multi element collection", () => {
        const arr: number[] = [2, 3, 1];
        insertionSort(arr);
        assert.deepEqual(arr, [1, 2, 3]);
    });
});
