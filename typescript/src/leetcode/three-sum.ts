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
export function threeSumUsingMaps(nums: number[]): number[][] {
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
    }
    return [...triplets.values()];
}

export function threeSumUsingTwoSum(nums: number[]): number[][] {
    const twoSum = (
        nums: number[],
        target: number,
        execludeIndex: number,
    ): number[] => {
        const map = new Map<number, number>();
        for (let i = 0; i < nums.length; i++) {
            if (i == execludeIndex) {
                continue;
            }
            if (map.has(nums[i])) {
                return [i, map.get(nums[i])!];
            } else {
                map.set(target - nums[i], i);
            }
        }
        return [];
    };

    let triplets: number[][] = [];
    let sorted = nums.toSorted();
    let duplicates = new Set<string>();
    let i = 0;

    while (sorted[i] <= 0 || i <= sorted.length) {
        let indecies = twoSum(nums, -nums[i], i);
        let xx = [...indecies.map((idx) => nums[idx]), nums[i]].toSorted();
        if (indecies.length == 2 && !duplicates.has(xx.join(""))) {
            triplets.push(xx);
            duplicates.add(xx.join(""));
        }
        i++;
    }
    return triplets;
}

/**
 * sort the input array
 * choose a number x at index i
 * find the two numbers y at index `i + 1` and z and index k = length(array) - 1
 * where: x = - 1 * (y + z)
 * note: because the array is sorted
 * - we should increment j if we want larger number
 * - and decrement k to find a smaller number
 * if x < -1 * (x + y):
 *      increment j
 * if x > -1 * (x + y):
 *      decrement k
 * if x == -1 (y + z)
 *      -> add the three numbers to result
 * [-4, -1, -1, 0, 1, 2]
 *   i   j ->      <- k
 * @param nums input numbers
 * @returns list of all combinations that sum up to zero
 */
export function threeSumUsingShrikingWindow(nums: number[]): number[][] {
    // can not be solved
    if (nums.length < 3) {
        return [];
    }
    const triplets: number[][] = [];
    nums.sort();
    let i = 0;
    // [-4, -1, -1, 0, 1, 2, 8] (sorted)
    //   i   j ->         <- k
    while (i < nums.length) {
        let j = i + 1;
        let k = nums.length - 1;
        while (j != k) {
            console.log(i, j, k);
            if (-nums[i] > nums[j] + nums[k]) {
                //  -(-4) > (-1 + 2) = 1
                j++;
            } else if (-nums[i] < nums[j] + nums[k]) {
                //  -(-4) > (-1 + 6) = 5
                k--;
            } else if (-nums[i] == nums[j] + nums[k]) {
                triplets.push([nums[i], nums[j], nums[k]]);
            }
        }
    }
    return [];
}
