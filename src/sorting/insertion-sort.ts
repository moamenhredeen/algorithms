
/**
 * insertion sort
 * @param nums the array to sort
 * @returns sorted array
 */
export function insertionSort(nums: number[]) {
	for (let i = 0; i < nums.length ; i++){
		let cur = nums[i]
		let j = i;
		while (j >= 0 && nums[j - 1] > cur) {
			nums[j - 1] = nums[j]; 
			j--;
		}
		nums[j] = cur;
	}
	return [];
}
