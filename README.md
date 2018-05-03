# python.c
It's all your favorite Python functions, but in C.
Composed of three interfaces: array.h, list.h, dict.h.

# array.h
Has functions which operate on static arrays.

- Min / max integer or double getter from array
- Array reversal functions
- Map function to array
- Filter out array values
- Array slicing functions
- Array join
- Array sort (recursive merge sort)
- Array to set functions (removes duplicate values from array)
- Set intersection
- Set symetric-difference
- Set difference
- Set union

# list.h
Has functions and structs for generic linked lists.

- New list node
- List length
- List insertion
- Push to list
- Append to list
- Node getter
- Remove node at
- Pop from list
- Free list
- Free node
- Make copy of list
- Make copy of node
- Return list's tail node
- List extend
- List reverse
- List map
- List filter
- List slice
- Convert list to static array
- Convert array to linked list

# dict.h
Has functions and structs for generic hash tables.

Hash table specs:
- Open addressing
- Incremental rehashing*
- Hash function = (key + key_size + address_of_table) % table_capacity
- Max load factor before resizing: 60% full
- Exponential table growth: capacity doubles on resize (when old table's max LF is exceeded)

*If there exists a value in the old table at the time of a hash, lookup, or removefrom, then a single value from the old table will be rehashed into the new table. Because the table size grows exponentially, the old table will always be empty of values by the time the new table hits max LF.

Functions:
- New hash table
- Free hash table
- Hash key:value pair
- Lookup value by key
- Remove value by key
