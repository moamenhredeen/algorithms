
import { assertEquals } from "@std/assert/equals";
import { insertionSort } from "./insertion-sort.ts";

Deno.test("empty collection", () => {
	const arr: number[] = [];
	insertionSort(arr);
	assertEquals(arr, [])
})
