
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "../efuncts.h"


void delete_dict(Dict *dt) {
    /* free entry array */
    free(dt->table);
    /* if the old table is active, free it aswell (does not lead to infinite recursion) */
    if(dt->old != NULL) delete_dict(dt->old);
    /* free struct itself */
    free(dt);
}


void set_entry(Entry *et, void *k, size_t ks, void *v) {
    et->key = k;
    et->ksize = ks;
    et->value = v;
}


Dict *new_dict(unsigned int max) {
    long unsigned int i;
    Dict *temp;
    
    /* malloc struct, table, then set all entries to NULL */
    temp = (Dict *)emalloc(sizeof(Dict));
    temp->table = (Entry *)emalloc(sizeof(Entry) * max);
    for(i = 0; i < max; i++) set_entry(&(temp->table[i]), NULL, sizeof(void *), NULL);
    
    /* set defaults */
    temp->cap = max;
    temp->count = 0;
    temp->old = NULL;
    
    return temp;
}


Dict *grow(Dict *curr) {
    Dict *temp;
    
    /* double capacity, set old to the previous table */
    temp = new_dict(curr->cap * 2);
    temp->old = curr;
    
    return temp;
}


double lf(long unsigned int n, long unsigned int k) {
    /* count of entries div capacity */
    return (double)n / (double)k;
}


long unsigned int inithash(Dict *dt, void *k, size_t ks) {
    long long unsigned int temp;
    
    /* clear all bits */
    temp = 0;
    /* copy of a limited amount of bits at pointer (prevents arithmetic on strings longer than 64 bits) */
    ememcpy(&temp, k, ks % (sizeof(long long unsigned int) + 1));
    
    return (temp + ks + (long unsigned int)dt->table) % dt->cap;
}


int checkat(Dict *dt, long unsigned int i, void *k, size_t ks) {
    Entry temp = dt->table[i];

    /* checks if entry is NULL, and size matches, and keys match */
    return (temp.key != NULL && temp.ksize == ks && memcmp(temp.key, k, ks));
}


long unsigned int find(Dict *dt, void *k, size_t ks) {
    long unsigned int i, h;
    
    /* gets initial hash, then linearly probes through table until finds key */
    for(i = 0, h = inithash(dt, k, ks); i < dt->cap && checkat(dt, h, k, ks); i++) {
        h++;
        h %= dt->cap;
    }
    
    return h % dt->cap;
}


void rem_old(Dict *dt, Entry *et) {
    long unsigned int i;
    Entry pair;
    
    /* finds next filled entry */
    for(i = 0; (dt->table[i]).key == NULL; i++);
    pair = dt->table[i];
    
    /* get address, set table's pointer to NULL, decrease count */
    set_entry(et, pair.key, pair.ksize, pair.value);
    set_entry(&(dt->table[i]), NULL, sizeof(void *), NULL);
    dt->count--;
}


void deposit(Dict *dt, void *key, size_t ks, void *val) {
    long unsigned int h;
    
    /* get hash, if filled (key already exists) overwrite */
    h = find(dt, key, ks);
    set_entry(&(dt->table[h]), key, ks, val);
    
    dt->count++;
}


void transfer(Dict *curr) {
    Entry *pair;
    Dict *temp;
    
    temp = curr->old;
    if(temp != NULL && temp->count) {
        /* remove the old value from old table, rehash into new table */
        pair = (Entry *)emalloc(sizeof(Entry));
        rem_old(temp, pair);
        deposit(curr, pair->key, pair->ksize, pair->value);
        free(pair);
    }
}


Dict *hash(Dict *dt, void *key, size_t ks, void *val) {
    /* if table exceeds LF, resize table */
    if(lf(dt->count, dt->cap) > .6) {
        if(dt->old != NULL) delete_dict(dt->old);
        dt = grow(dt);
    }
    
    /* attempt transfer from old table to new */
    transfer(dt);
    /* hash value into table */
    deposit(dt, key, ks, val);
    
    return dt;
}


void *lookup(Dict *dt, void *key, size_t ks) {
    long unsigned int h;
    
    /* attempt transfer from old table to new */
    transfer(dt);
    
    /* search current table for key */
    h = find(dt, key, ks);
    if((dt->table[h]).key != NULL) return (dt->table[h]).value;
    
    /* search old table for key */
    h = find(dt->old, key, ks);
    if(((dt->old)->table[h]).key != NULL) return ((dt->old)->table[h]).value;
    
    return NULL;
}


void *clear(Dict *dt, void *key, size_t ks) {
    long unsigned int h;
    
    /* attempt transfer from old table to new */
    transfer(dt);

    /* search current table for entry */
    h = find(dt, key, ks);
    /* if allocated, set key to NULL return pointer */
    if((dt->table[h]).key != NULL) {
        (dt->table[h]).key = NULL;
        (dt->table[h]).ksize = sizeof(void *);
        dt->count--;
        
        return (dt->table[h]).value;
    }
    
    dt = dt->old;
    
    /* search old table for entry */
    h = find(dt, key, ks);
    /* if allocated, set key to NULL return pointer */
    if((dt->table[h]).key != NULL) {
        (dt->table[h]).key = NULL;
        (dt->table[h]).ksize = sizeof(void *);
        dt->count--;
        
        return (dt->table[h]).value;
    }
    
    return NULL;
}

