#ifndef ALGORITHMS_LEETCODE_H
#define ALGORITHMS_LEETCODE_H


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/**
 * Given an array of integers nums and an integer target,
 * return indices of the two numbers such that they add up to the target.
 * You may assume that each input would have exactly one solution,
 * and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * @note  The returned array must be malloced, assume caller calls free().
 *
 * @param nums array of integers
 * @param numsSize size of the nums array
 * @param target the sum of the two numbers
 * @param returnSize  the length of the returned indices array
 * @return indices of the two numbers such that they add up to the target
 */
int *twoSum(const int *nums, int numsSize, int target, int *returnSize);

/**
 * The Longest Substring Without Repeating Characters
 * Given a string s, find the length of the longest without duplicate characters
 * @note A substring is a contiguous non-empty sequence of characters within a string.
 * @param s input string
 * @return the length of the longest without duplicate characters
 */
int lengthOfLongestSubstring(char *s);


/**
 * Definition for singly-linked list
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2);

/**
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
 * (you may want to display this pattern in a fixed font for better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows
 */
char* zigzag_convert(char* s, int numRows);

/**
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such
 * that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature.
 * If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 *
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 *
 * Constraints:
 * 1 <= temperatures.length <= 105
 * 30 <= temperatures[i] <= 100
 */
int* daily_temperatures(const int* temperatures, int temperaturesSize, int* returnSize);

/**
 * 61. Rotate List
 * level: medium
 *
 * Given the head of a linked list, rotate the list to the right by k places.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 * 
 * Example 2:
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 *
 * Constraints:
 * The number of nodes in the list is in the range [0, 500].
 * -100 <= Node.val <= 100
 * 0 <= k <= 2 * 109
 */
struct ListNode* rotateRight(struct ListNode* head, int k);

#endif
