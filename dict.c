
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
    
    for(i = 0; i < dt->cap; i++) if(dt->table[i] != NULL) delete_entry(dt->table[i]);
    free(dt->table);
    
    if(dt->old != NULL) delete_dict(dt->old);
    
    free(dt);
}


Entry *new_entry(void *k, size_t ks, void *v) {
    Entry *temp;
    
    temp = (Entry *)emalloc(sizeof(Entry));
    
    temp->key = k;
    temp->ksize = ks;
    temp->val = v;
    
    return temp;
}


Dict *new_dict(unsigned int max) {
    unsigned int i;
    Dict *temp;
    
    temp = (Dict *)emalloc(sizeof(Dict));
    temp->table = (Entry **)emalloc(sizeof(Entry *) * max);
    for(i = 0; i < max; i++) temp->table[i] = NULL;
    
    temp->cap = max;
    temp->count = 0;
    temp->old = NULL;
    
    return temp;
}


Dict *grow(Dict *curr) {
    Dict *temp;
    
    temp = new_dict(curr->cap*2);
    temp->old = curr;
    
    return temp;
}


double lf(unsigned int n, unsigned int k) {
    return (double)n / (double)k;
}


unsigned int inithash(Dict *dt, void *k, size_t ks) {
    long long unsigned int mask;
    
    mask = 0;
    ememcpy(&mask, k, ks % (sizeof(long long unsigned int) + 1));
    
    return (mask + ks + (long unsigned int)dt->table) % dt->cap;
}


int checkat(Dict *dt, unsigned int i, void *k, size_t ks) {
    return (dt->table[i] != NULL && ks == (dt->table[i])->ksize && !memcmp(k, (dt->table[i])->key, ks));
}


long unsigned int hasher(Dict *dt, void *k, size_t ks) {
    unsigned int i, h;
    
    for(i = 0, h = inithash(dt, k, ks); i < dt->cap && checkat(dt, h, k, ks); i++) {
        h++;
        h %= dt->cap;
    }
    
    return h % dt->cap;
}


Entry *find(Dict *dt, void *k, size_t ks) {
    unsigned int i, h;
    
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
    
    for(i = 0; dt->table[i] == NULL; i++);
    
    pair = dt->table[i];    
    dt->table[i] = NULL;
    dt->count--;
    
    return pair;
}


void deposit(Dict *dt, Entry *pair) {
    unsigned int h;
    
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
        pair = rem_old(temp);
        deposit(curr, pair);
    }
}


Dict *hash(Dict *dt, void *key, size_t ks, void *val) {
    if(lf(dt->count, dt->cap) > .6) {
        if(dt->old != NULL) delete_dict(dt->old);
        dt = grow(dt);
    }

    transfer(dt);

    deposit(dt, new_entry(key, ks, val));
    
    return dt;
}


void *lookup(Dict *dt, void *key, size_t ks) {
    Entry *temp;
    
    transfer(dt);

    temp = find(dt, key, ks);
    if(temp != NULL) return temp->val;
    
    temp = find(dt->old, key, ks);
    if(temp != NULL) return temp->val;
    
    return NULL;
}


void *removefrom(Dict *dt, void *key, size_t ks) {
    Entry *temp;
    void *value;
    
    transfer(dt);

    temp = find(dt, key, ks);
    if(temp != NULL) {
        value = temp->val;
        delete_entry(temp);
        return value;
    }
    
    temp = find(dt->old, key, ks);
    if(temp != NULL) {
        value = temp->val;
        delete_entry(temp);
        return value;
    }
    
    return NULL;
}

