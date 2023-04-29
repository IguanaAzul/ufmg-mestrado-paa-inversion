// Trabalho de Projeto e Análise em Algoritmos - DCC UFMG.
// Ramon Griffo Costa.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int invert_number(int n) {
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed;
}

bool prune_and_search(vector<int>& v, int destination, vector<bool> visited) {
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
        if (visited[v[i]]) { // Se o valor já foi visitado, remove
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
        vector<bool> visited(destination * 10 + 1);
        visited[origin] = true;
        vector<int> v(n, origin);
        int steps = 1;
        while (true) {
            v.resize(2 * n);
            copy_n(v.begin(), n, v.begin() + n);
            for (unsigned int i = 0; i < n; i++) {
                visited[v[i]] = 1;
                if (!visited[v[i] + 1]){
                    v[i] += 1;
                }
            }
            for (unsigned int i = n; i < n * 2; i++) {
                if (!visited[invert_number(v[i])]){
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
