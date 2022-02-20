#!/usr/bin/env python3

import collections

# Structures                                    # Review: singly linked list
                                                # Review: namedtumple
Node = collections.namedtuple('Node', 'data next')

# Functions

def slist_data(head):                           # Discuss: Iterative (List)
    data = []
    curr = head
    while curr:
        data.append(curr.data)
        curr = curr.next
    return data

def slist_data(head):                           # Discuss: Iterative (Generator)
    curr = head
    while curr:
        yield curr.data
        curr = curr.next


def slist_reverse(head):                        # Discuss: Recursion (List)
    return slist_reverse_r(head.next, head)

def slist_reverse_r(curr, prev):                # Discuss: Helper Function
    if curr is not None:                        # Recursive case
        data = slist_reverse_r(curr.next, curr)
    else:                                       # Base case
        data = []

    return data + [prev.data]                   # Discuss: Concatenating lists

def slist_reverse(head):                        # Discuss: Recursion (Generator)
    return slist_reverse_r(head.next, head)

def slist_reverse_r(curr, prev):                # Discuss: Helper Function
    if curr is not None:                        # Discuss: yield from
        yield from slist_reverse_r(curr.next, curr)

    yield prev.data

# Main Execution

def main():
    slist = Node('a', Node('b', Node('c', Node('d', None))))

    for item in slist_data(slist):
        print(item)

    print()

    for item in slist_reverse(slist):
        print(item)

if __name__ == '__main__':
    main()
