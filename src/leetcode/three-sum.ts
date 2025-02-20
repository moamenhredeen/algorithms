/**
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 *
 * Notice that the solution set must not contain duplicate triplets.
 *
 * Example 1:
 *
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation:
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not matter.
 *
 * Example 2:
 *
 * Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum up to 0.
 *
 * Example 3:
 *
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums up to 0.
 *
 * Constraints:
 *
 * 3 <= nums.length <= 3000
 * -105 <= nums[i] <= 105
 *
 * @param nums
 * @returns
 */
export function threeSum(nums: number[]): number[][] {
    const triplets = new Map<string, number[]>();
    let cache = new Map<number, number[][]>();

    for (const num of nums) {
        if (cache.has(-num)) {
            let matrix = cache.get(-num)!;
            for (let i = 0; i < matrix.length; i++) {
                if (matrix[i].length == 2) {
                    let triplet = [...matrix[i], num].toSorted();
                    triplets.set(triplet.join(""), triplet);
                    matrix.splice(i, 1);
                }
            }
        }
        // we have to take snapshot, otherwise we enter
        // endless loop of adding to the map
        let keySnapshot = [...cache.keys()];
        for (const key of keySnapshot) {
            if (cache.has(key + num)) {
                cache.get(key + num)?.push([key, num]);
            } else {
                cache.set(key + num, [[key, num]]);
            }
        }
        if (cache.has(num)) {
            cache.get(num)?.push([num]);
        } else {
            cache.set(num, [[num]]);
        }
        console.log(cache);
    }
    return [...triplets.values()];
}
