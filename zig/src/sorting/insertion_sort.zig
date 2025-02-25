const std = @import("std");

pub fn insertion_sort(arr: []u32) void {
    if (arr.len == 0 or arr.len == 1) return;
    // we start at index 1, because the first item is already sorted
    var i: usize = 1;
    var j: usize = undefined;
    var current: u32 = undefined;
    while (i < arr.len) : (i += 1) {
        j = i;
        current = arr[i];
        while (j > 0 and (arr[j - 1] > current)) : (j -= 1) {
            arr[j] = arr[j - 1];
        }
        arr[j] = current;
    }
}

test "empty collection" {
    var arr = [_]u32{};
    insertion_sort(&arr);
    try std.testing.expect(std.mem.eql(u32, &arr, &[_]u32{}));
}

test "single item collection" {
    var arr = [_]u32{1};
    insertion_sort(&arr);
    try std.testing.expect(std.mem.eql(u32, &arr, &[_]u32{1}));
}

test "multiple item collection" {
    var arr = [_]u32{ 2, 1, 3 };
    insertion_sort(&arr);
    try std.testing.expect(std.mem.eql(u32, &arr, &[_]u32{ 1, 2, 3 }));
}

test "larger collection" {
    var arr = [_]u32{ 2, 1, 3, 8, 7, 4, 6, 9, 0, 5 };
    insertion_sort(&arr);
    try std.testing.expect(std.mem.eql(u32, &arr, &[_]u32{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));
}
