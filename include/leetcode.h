#ifndef ALGORITHMS_LEETCODE_H
#define ALGORITHMS_LEETCODE_H


#include <stdlib.h>
#include <stdbool.h>
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

#endif
