#include <iostream>

using namespace std;
typedef pair<int, int> pi;
const int MAX=1e6+5;
char str[MAX+2];
pi tree[4*MAX];

void build(int st, int en, int p=1){

    if(st==en){
        tree[p].first= (str[st]=='(');
        tree[p].second= (str[st]==')');
        return ;
    }
    int mid=(st+en)/2;
    build(st, mid, 2*p);
    build(mid+1, en, 2*p+1);

    pi p1=tree[2*p], p2=tree[2*p+1];
    int re=min(p2.second, p1.first);
    p2.second-=re;p1.first-=re;
    pi p3=pi(p1.first + p2.first, p1.second + p2.second);
    tree[p]=p3;

    return;
}
int from, to;

pi query(int st, int en, int p=1){

    if(from <= st && en <= to) return tree[p];
    if(st > to || en < from) return pi(0, 0);

    int mid=(st+en)/2;

    if(to <= mid) return query(st, mid, 2*p);
    if(from > mid) return query(1+mid, en, 2*p+1);

    pi p1=query(st, mid, 2*p);
    pi p2=query(mid+1, en, 2*p+1);
    int re=min(p2.second, p1.first);
    p2.second-=re;p1.first-=re;
    pi p3=pi(p1.first + p2.first, p1.second + p2.second);

    return p3;

}
int idx;
void update(int st, int en, int p=1){


    if(st==en && st==idx){
        if(str[st]=='(')tree[p].first--, tree[p].second++;
        else tree[p].first++, tree[p].second--;
        return;
    }

    int mid=(st+en)/2;
    if(idx <= mid){
        update(st, mid, 2*p);
    } else {
        update(1+mid, en, 2*p+1);
    }

    pi p1=tree[2*p];
    pi p2=tree[2*p+1];
    int re=min(p2.second, p1.first);
    p2.second-=re;p1.first-=re;
    pi p3=pi(p1.first + p2.first, p1.second + p2.second);
    tree[p] = p3;

}

int main(){
    int q, n;
    int i=1;
    while(cin >> n){
    cin >> str;
    build(0, n-1, 1);
    cin >> q;
    cout << "Test " << i++ << "\n";
    while(q--){
        int a;
        cin >> a;
        if(!a){
            int from=0, to=n-1;
            pi p=query(0, n-1, 1);
            if(!tree[1].first && !tree[1].second) cout << "YES\n";
            else cout << "NO\n";
        } else {
            a--;
            idx=a;
            if(str[idx]=='(') str[idx]==')';
            else str[idx]=='(';

            update(0, n-1, 1);
        }
    }


    }

    return 0;
}
