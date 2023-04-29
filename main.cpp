// Trabalho de Projeto e Análise em Algoritmos - DCC UFMG.
// Ramon Griffo Costa.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int invert_number(int n) {
    string to_reverse = to_string(n);
    reverse(to_reverse.begin(), to_reverse.end());
    int inverted = stoi(to_reverse);
    return inverted;
}

bool prune_and_search(vector<int>& v, int destination, set<int> visited) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end()); // Remove duplicados
    for (int i = 0; i < v.size(); i++) {
        // Podem haver casos em que a solução ótima passa por valores maiores que o valor final.
        // Mas não pode passar de 10 * destination porque o valor vai ter mais dígitos do que o possível.
        if (v[i] > destination * 10) {
            v.erase(v.begin() + i);
            i--;
        }
        if (v[i] == destination) { // Valor final encontrado
            return true;
        }
        if (visited.find(v[i] + 1) != visited.end()) { // Se o valor já foi visitado, remove
            v.erase(v.begin() + i);
            i--;
        }
    }
    return false;
}

int main() {
    int n_cases, origin, destination;
    cin >> n_cases;

    while (cin >> origin >> destination) {
        unsigned int n = 1;
        set<int> visited;
        visited.insert(origin);
        vector<int> v(n, origin);
        int steps = 1;
        while (true) {
            v.resize(2 * n);
            copy_n(v.begin(), n, v.begin() + n);
            for (unsigned int i = 0; i < n; i++) {
                visited.insert(v[i]);
                if (!(visited.find(v[i] + 1) != visited.end())){
                    v[i] += 1;
                }
            }
            for (unsigned int i = n; i < n * 2; i++) {
                if (!(visited.find(invert_number(v[i])) != visited.end())){
                    v[i] = invert_number(v[i]);
                }
            }
            if (prune_and_search(v, destination, visited)) {
                cout << steps << "\n";
                break;
            }
            steps++;
            n = v.size();
        }
    }
    return 0;
}
