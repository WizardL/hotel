/*
 * Copyright (c) 2018 zypeh. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum { LEAF_NODE, INTERNAL_NODE } NodeType;

typedef struct TreeNode {
    NodeType type;
    uint32_t len;
} TreeNode;

typedef struct LeafNode {
    NodeType type;
    uint32_t len;
    const void *child[];
} LeafNode;

typedef struct InternalNode {
    NodeType type;
    uint32_t len;
    struct InternalNode *child[];
} InternalNode;

struct rrb {
    uint32_t cnt;
    uint32_t shift;
    uint32_t tail_len;
    LeafNode *tail;
    TreeNode *root;
};

// -------------------------------[ Initialization ]
struct rrb create_rrb() {
    struct rrb a = {
        .cnt = 0,
        .shift = 0,
        .tail_len = 0,
        .tail = 0,
        .root = 0,
    };
    return a;
}

// -------------------------------[ Operations ]
// -------------------------------[ Transient ]
// -------------------------------[ API ]

// int main() {
//     struct rrb a = create_rrb();
//     printf("%d", a.shift);
// }