import { insertionSort } from "./insertion-sort";
import { describe, test, expect } from "vitest";

describe("insertion sort", () => {
    test("empty collection", () => {
        const arr: number[] = [];
        insertionSort(arr);
        expect(arr).toEqual([]);
    });

    test("one element collection", () => {
        const arr: number[] = [1];
        insertionSort(arr);
        expect(arr).toEqual([1]);
    });

    test("multi element collection", () => {
        const arr: number[] = [2, 3, 1];
        insertionSort(arr);
        expect(arr).toEqual([1, 2, 3]);
    });
});
