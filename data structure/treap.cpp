typedef int KEY;
typedef char VALUE;
struct Treap {
    static Treap nil;
    KEY key;
    VALUE value;
    Treap *l,*r;
    int size, pri;
    Treap() : l(&nil), r(&nil), size(0), pri(rand()) {}
    Treap(KEY k, VALUE v) : key(k), value(v), l(&nil), r(&nil), size(1), pri(rand()) {}
    Treap(VALUE v) : Treap(0, v) {}
} Treap::nil;

int size(Treap *t) { return t->size; }

void push(Treap *t) {
    if (!size(t)) return;
}

void pull(Treap *t) {
    push(t->l);
    push(t->r);
    t->size = size(t->l) + size(t->r) + 1;
}

Treap *merge(Treap *a,Treap *b) {
    if (!size(a)) return b;
    if (!size(b)) return a;
    push(a);
    push(b);
    if (a->pri > b->pri) {
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else {
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

void split_by_key(Treap *t, KEY k, Treap *&a, Treap *&b) {
    if (!size(t)){
        a = b = &Treap::nil;
        return;
    }
    push(t);
    if (t->key > k) {
        b = t;
        split_by_key(t->l, k, a, b->l);
        pull(b);
    }
    else {
        a = t;
        split_by_key(t->r, k, a->r, b);
        pull(a);
    }
}

void split_by_size(Treap *t, int k, Treap *&a, Treap *&b) {
    if (!size(t)){
        a = b = &Treap::nil;
        return;
    }
    push(t);
    if (size(t->l) >= k) {
        b = t;
        split_by_size(t->l, k, a, b->l);
        pull(b);
    }
    else {
        a = t;
        split_by_size(t->r, k - size(t->l) - 1, a->r, b);
        pull(a);
    }
}

void kill(Treap *t) {
    if (!size(t)) return;
    kill(t->l);
    kill(t->r);
    delete t;
}
