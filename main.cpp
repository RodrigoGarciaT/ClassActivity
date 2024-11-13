#include <bits/stdc++.h>
using namespace std;

/*
Casos de prueba:

Input:
6
2, 3
12, 30
40, 50
5, 1
12, 10
3, 4
Output:
La distancia mas corta es: 1.41421

Input:
5
0, 2
6, 67
43, 71
39, 107
189, 140

Output:
La distancia mas corta es: 36.2215

Input:
3
0, 0
10000, 10000
20000, 20000

Output:
La distancia mas corta es: 14142.1

Input:
6
-2, -3
-12, -30
-40, -50
-5, -1
-12, -10
-3, -4
Output:
La distancia mas corta es: 1.41421

Input:
6
7, -3
12, -30
-88, -5
-5, -99
12, 10
3, 120

Output:
La distancia mas corta es: 13.9284
*/
// Creamos estructura punto
struct pt {
    int x, y, id;
};

// O(1) comparador en x
struct cmp_x {
    bool operator()(const pt & a, const pt & b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

// O(1) comparador en y
struct cmp_y {
    bool operator()(const pt & a, const pt & b) const {
        return a.y < b.y;
    }
};

int n;
vector<pt> a;

double mindist;
pair<int, int> best_pair;

// o(1) checa la distancia de 2 puntos y si es menor a la distancia mas corta actual la actualiza
void upd_ans(const pt & a, const pt & b) {
    double dist = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    if (dist < mindist) {
        mindist = dist;
        best_pair = {a.id, b.id};
    }
}

vector<pt> t;

// O(nlogn) Saca nuestra respuesta con divide and conquer
// divide entre 2 e itera n puntos en total
// haciendo n operaciones, log n veces
void rec(int l, int r) {

    // O(6) bruteforce de la respuesta cuando tenemos maximo 3 puntos
    if (r - l <= 3) {
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                upd_ans(a[i], a[j]);
            }
        }
        sort(a.begin() + l, a.begin() + r, cmp_y());
        return;
    }

    int m = (l + r) >> 1;
    int midx = a[m].x;
    rec(l, m);
    rec(m, r);

    // ordenamos el arreglo de l a r por y
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, t.begin(), cmp_y());
    copy(t.begin(), t.begin() + r - l, a.begin() + l);

    // iteramos todos los puntos en nuestro rango l, r
    // maximo 7 puntos pasaran en el segundo for por cada punto, O(7(r-l))
    int tsz = 0;
    for (int i = l; i < r; ++i) {
        if (abs(a[i].x - midx) < mindist) {
            for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
                upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
    }
}

int main() {
    int n;
    cin >> n;

    // o(n) processing input
    cin.ignore();
    for(int i = 0; i < n; i++){
        string inputStr;
        getline(cin, inputStr);
        inputStr += ',';
        string currNum = "";
        vector<int> point;
        for(auto c: inputStr){
            if(c == ','){
                point.push_back(stoi(currNum));
                currNum = "";
            }else if(c != ' '){
                currNum += c;
            }
        }
        a.push_back({point[0], point[1], i});
    }
    t.resize(n);

    // o(nlogn)
    sort(a.begin(), a.end(), cmp_x());
    mindist = 1E20;

    // o(nlogn)
    rec(0, n);
    cout << "La distancia mas corta es: " <<  mindist << endl;
    return 0;
}
