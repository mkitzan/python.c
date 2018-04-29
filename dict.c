
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "efuncts.h"


void delete_entry(Entry *pair) {
    free(pair);
}


void delete_dict(Dict *dt) {
    unsigned int i;
    
    // free any filled entry, then table itself
    for(i = 0; i < dt->cap; i++) if(dt->table[i] != NULL) delete_entry(dt->table[i]);
    free(dt->table);
    
    // if the old table is active, free it aswell (does not lead to infinite recursion)
    if(dt->old != NULL) delete_dict(dt->old);
    // free struct itself
    free(dt);
}


Entry *new_entry(void *k, size_t ks, void *v) {
    Entry *temp;
    
    // malloc struct
    temp = (Entry *)emalloc(sizeof(Entry));
    // write values
    temp->key = k;
    temp->ksize = ks;
    temp->val = v;
    
    return temp;
}


Dict *new_dict(unsigned int max) {
    unsigned int i;
    Dict *temp;
    
    // malloc struct, table, then set all pointers to NULL
    temp = (Dict *)emalloc(sizeof(Dict));
    temp->table = (Entry **)emalloc(sizeof(Entry *) * max);
    for(i = 0; i < max; i++) temp->table[i] = NULL;
    
    // set defaults
    temp->cap = max;
    temp->count = 0;
    temp->old = NULL;
    
    return temp;
}


Dict *grow(Dict *curr) {
    Dict *temp;
    
    // double capacity, set old to the previous table
    temp = new_dict(curr->cap * 2);
    temp->old = curr;
    
    return temp;
}


double lf(unsigned int n, unsigned int k) {
    // count of entries div capacity
    return (double)n / (double)k;
}


unsigned int inithash(Dict *dt, void *k, size_t ks) {
    long long unsigned int temp;
    
    // clear all bits
    temp = 0;
    // copy of a limited amount of bits at pointer (prevents arithmetic on string longer than 64 bits)
    ememcpy(&temp, k, ks % (sizeof(long long unsigned int) + 1));
    
    return (temp + ks + (long unsigned int)dt->table) % dt->cap;
}


int checkat(Dict *dt, unsigned int i, void *k, size_t ks) {
    // checks if entry is NULL, and size matches, and keys match
    return (dt->table[i] != NULL && ks == (dt->table[i])->ksize && !memcmp(k, (dt->table[i])->key, ks));
}


long unsigned int hasher(Dict *dt, void *k, size_t ks) {
    unsigned int i, h;
    
    // gets initial hash, then linearly probes through table until finds key
    for(i = 0, h = inithash(dt, k, ks); i < dt->cap && checkat(dt, h, k, ks); i++) {
        h++;
        h %= dt->cap;
    }
    
    return h % dt->cap;
}


Entry *find(Dict *dt, void *k, size_t ks) {
    unsigned int i, h;
    
    // gets initial hash, then linearly probes through table until finds free space
    for(i = 0, h = inithash(dt, k, ks); i < dt->cap && !checkat(dt, h, k, ks); i++) {
        h++;
        h %= dt->cap;
    }
    
    if(checkat(dt, h, k, ks)) return dt->table[h];
    
    return NULL;
}


Entry *rem_old(Dict *dt) {
    unsigned int i;
    Entry *pair;
    
    // finds next filled entry
    for(i = 0; dt->table[i] == NULL; i++);
    
    // get address, set table's pointer to NULL, decrease count
    pair = dt->table[i];    
    dt->table[i] = NULL;
    dt->count--;
    
    return pair;
}


void deposit(Dict *dt, Entry *pair) {
    unsigned int h;
    
    // get hash, if filled (key already exists) overwrite
    h = hasher(dt, pair->key, pair->ksize);
    if(dt->table[h] != NULL) delete_entry(dt->table[h]);
    dt->table[h] = pair;
    
    dt->count++;
}


void transfer(Dict *curr) {
    Entry *pair;
    Dict *temp;
    
    temp = curr->old;
    if(temp != NULL && temp->count) {
        // remove the old value from old table, rehash into new table
        pair = rem_old(temp);
        deposit(curr, pair);
    }
}


Dict *hash(Dict *dt, void *key, size_t ks, void *val) {
    // if table exceeds LF, resize table
    if(lf(dt->count, dt->cap) > .6) {
        if(dt->old != NULL) delete_dict(dt->old);
        dt = grow(dt);
    }
    
    // attempt transfer from old table to new
    transfer(dt);
    // hash value into table
    deposit(dt, new_entry(key, ks, val));
    
    return dt;
}


void *lookup(Dict *dt, void *key, size_t ks) {
    Entry *temp;
    
    // attempt transfer from old table to new
    transfer(dt);
    
    // search current table for key
    temp = find(dt, key, ks);
    if(temp != NULL) return temp->val;
    // search old table for key
    temp = find(dt->old, key, ks);
    if(temp != NULL) return temp->val;
    
    return NULL;
}


void *removefrom(Dict *dt, void *key, size_t ks) {
    Entry *temp;
    void *value;
    
    // attempt transfer from old table to new
    transfer(dt);

    // search current table for key
    temp = find(dt, key, ks);
    if(temp != NULL) {
        value = temp->val;
        delete_entry(temp);
        return value;
    }
    // search old table for key
    temp = find(dt->old, key, ks);
    if(temp != NULL) {
        value = temp->val;
        delete_entry(temp);
        return value;
    }
    
    return NULL;
}

