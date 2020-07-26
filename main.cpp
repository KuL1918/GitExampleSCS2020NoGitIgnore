#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct node {
    int x;
    node *l, *r;

    node(int x_) {
        x = x_;
        l = r = 0;
    }
};

int n, y, used[100010], ans[100010], cnt = 0;
node *t;

node *merge(node *l, node *r) {
    if (!l)
        return r;
    if (!r)
        return l;
    if (rand() & 1) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
}

pair<node *, node *> split(node *t, int key) {
    if (!t)
        return {0, 0};

    if (t->x >= key) {
        pair<node *, node *> spl = split(t->l, key);
        t->l = spl.second;
        return {spl.first, t};
    } else {
        pair<node *, node *> spl = split(t->r, key);
        t->r = spl.first;
        return {t, spl.second};
    }
}

node *erase(node *t, int x) {
    pair<node *, node *> spl1 = split(t, x);
    pair<node *, node *> spl2 = split(spl1.second, x + 1);

    return merge(spl1.first, spl2.second);
}

node *insert(node *t, int x) {
    node *np = new node(x);

    pair<node *, node *> spl = split(t, x);

    return merge(spl.first, merge(np, spl.second));

}

void print(node *t) {
    if (!t)
        return;
    print(t->l);
    print(t->r);
}

int minimum(node *t) {
    if (!t)
        return -1;
    if (!(t->l))
        return t->x;

    return minimum(t->l);
}

node *next(node *t, int r) {
    pair<node *, node *> spl = split(t, r);
    y = minimum(spl.second);
    //cout << y << '\n';
    return merge(spl.first, spl.second);
}

int main() {
    srand(time(0));
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int x = a;
        if (a > 0) {
            if (!used[a]) {
                t = insert(t, a);
                used[a] = 1;
                ans[cnt] = a;
                cnt++;
            } else {
                while (y != -1) {
                    if (!used[a])
                        break;
                    a++;
                    t = next(t, a);
                }
                y = 0;
                t = insert(t, a);
                used[a] = 1;
                ans[cnt] = a;
                cnt++;
            }
        } else {
            t = erase(t, abs(a));
            used[abs(a)] = 0;
        }
    }

    for (int i = 0; i < cnt; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
