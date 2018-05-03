#ifndef _DICT_H_
#define _DICT_H_

typedef struct entry Entry;
typedef struct dict Dict;

struct entry {
    void *key;
    size_t ksize;
    void *value;
};   


struct dict {
    Entry *table;
    
    long unsigned int cap;
    long unsigned int count;
    
    Dict *old;
};


/* creates/returns new dict */
Dict *new_dict(unsigned int);


/* frees the passed dictionary */
void delete_dict(Dict *);


/* hashes pointer to value, returns dict, because dict may be resized creating a new dict reference
   if the key exists in the table, the value at its entry will be overwritten */
Dict *hash(Dict *, void *, size_t, void *);


/* searches dict returns pointer to value */
void *lookup(Dict *, void *, size_t);

/* returns pointer to hashed value, and removes the entry it was contained in from the dict */
void *clear(Dict *, void *, size_t);

#endif

