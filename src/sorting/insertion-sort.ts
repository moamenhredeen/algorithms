
/**
 * insertion sort implementation
 * it does sort the colleciton In Place
 * 
 * # example
 * ```ts
 * let arr = [1, 3, 2, 8, 4];
 * arr.sort();
 * ```
 * @param nums the array to sort
 * @returns sorted array
 */
export function insertionSort(nums: number[]) {
	for (let i = 0; i < nums.length ; i++){
		const cur = nums[i]
		let j = i;
		while (j > 0 && nums[j - 1] > cur) {
			nums[j] = nums[j - 1]; 
			j--;
		}
		nums[j] = cur;
	}
}
