import {
    threeSumUsingMaps,
    threeSumUsingShrikingWindow,
    threeSumUsingTwoSum,
} from "./three-sum";
import { describe, test } from "node:test";
import assert from 'assert/strict'

// describe("leetcode: three sum using maps", () => {
//     test("test case 1", () => {
//         const res = threeSumUsingMaps([-1, 0, 1, 2, -1, -4]);

//         let expected = [
//             [-1, -1, 2],
//             [-1, 0, 1],
//         ];
//         expect(res.map((el) => el.toSorted()).toSorted()).toEqual(
//             expected.map((el) => el.toSorted()).toSorted(),
//         );
//     });

//     test("test case 2", () => {
//         const res = threeSumUsingMaps([0, 1, 1]);
//         res.sort();
//         expect(res).toEqual([]);
//     });

//     test("test case 3", () => {
//         const res = threeSumUsingMaps([0, 0, 0]);
//         res.sort();
//         expect(res).toEqual([[0, 0, 0]]);
//     });
// });

// describe("leetcode: three sum usign two sum", () => {
//     test("test case 1", () => {
//         const res = threeSumUsingTwoSum([-1, 0, 1, 2, -1, -4]);

//         let expected = [
//             [-1, -1, 2],
//             [-1, 0, 1],
//         ];
//         expect(res.map((el) => el.toSorted()).toSorted()).toEqual(
//             expected.map((el) => el.toSorted()).toSorted(),
//         );
//     });

//     test("test case 2", () => {
//         const res = threeSumUsingTwoSum([0, 1, 1]);
//         res.sort();
//         expect(res).toEqual([]);
//     });

//     test("test case 3", () => {
//         const res = threeSumUsingTwoSum([0, 0, 0]);
//         res.sort();
//         expect(res).toEqual([[0, 0, 0]]);
//     });

//     test("test case 4", () => {
//         const res = threeSumUsingTwoSum([-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4]);
//         res.sort();
//         expect(res).toEqual([
//             [-4, 0, 4],
//             [-4, 1, 3],
//             [-3, -1, 4],
//             [-3, 0, 3],
//             [-3, 1, 2],
//             [-2, -1, 3],
//             [-2, 0, 2],
//             [-1, -1, 2],
//             [-1, 0, 1],
//         ]);
//     });
// });

describe("leetcode: three sum using shrinking window", () => {
    // test("test case 1", () => {
    //     const res = threeSumUsingShrikingWindow([-1, 0, 1, 2, -1, -4]);

    //     let expected = [
    //         [-1, -1, 2],
    //         [-1, 0, 1],
    //     ];
    //     // expect(res.map((el) => el.toSorted()).toSorted()).toEqual(
    //     //     expected.map((el) => el.toSorted()).toSorted(),
    //     // );
    // });

    // test("test case 2", () => {
    //     const res = threeSumUsingShrikingWindow([0, 1, 1]);
    //     res.sort();
    //     assert.equal(res, []);
    // });

    // test("test case 3", () => {
    //     const res = threeSumUsingShrikingWindow([0, 0, 0]);
    //     res.sort();
    //     assert.equal(res, [[0, 0, 0]]);
    // });

    // test("test case 4", () => {
    //     const res = threeSumUsingShrikingWindow([
    //         -1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4,
    //     ]);
    //     res.sort();
    //     assert.equal(res, [
    //         [-4, 0, 4],
    //         [-4, 1, 3],
    //         [-3, -1, 4],
    //         [-3, 0, 3],
    //         [-3, 1, 2],
    //         [-2, -1, 3],
    //         [-2, 0, 2],
    //         [-1, -1, 2],
    //         [-1, 0, 1],
    //     ]);
    // });
});
