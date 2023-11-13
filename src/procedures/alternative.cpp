#include <alternative.h>
#include <tree.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

// Función para calcular la distancia de edición entre dos cadenas
// Aca utilize el algoritmo de Levenshtein para calcular eso rapido con dp en O(n^2)
int string_edit_distance(const std::string& s1, const std::string& s2) {
    int m = s1.size(), n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min(std::min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
            }
        }
    }

    return dp[m][n];
}

// Implementación del algoritmo húngaro para el problema de asignación
std::vector<int> hungarian_algorithm(const std::vector<std::vector<int>>& cost_matrix) {
    int n = cost_matrix.size();
    std::vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(n + 1, std::numeric_limits<int>::max());
        std::vector<char> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = std::numeric_limits<int>::max(), j1;
            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    int cur = cost_matrix[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= n; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return std::vector<int>(p.begin() + 1, p.end());
}

// Función para emparejar componentes de dos árboles
std::vector<std::pair<int, int>> match_components(const Tree& T, const Tree& T1, const std::vector<std::vector<int>>& components_T, const std::vector<std::vector<int>>& components_T1, const std::vector<int>& representatives_T, const std::vector<int>& representatives_T1) {
    int n = std::max(components_T.size(), components_T1.size());
    std::vector<std::vector<int>> cost_matrix(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    for (int i = 0; i < components_T.size(); i++) {
        for (int j = 0; j < components_T1.size(); j++) {
            cost_matrix[i][j] = string_edit_distance(T.pre_order(components_T[i][0], components_T[i].back(), {}), T1.pre_order(components_T1[j][0], components_T1[j].back(), {}));
        }
    }
    std::vector<int> matching_indices = hungarian_algorithm(cost_matrix);
    std::vector<std::pair<int, int>> matching;
    for (int i = 0; i < n; i++) {
        matching.push_back({representatives_T[i], representatives_T1[matching_indices[i]]});
    }
    return matching;
}


// Funcion principal que calcula la distancia de edicion entre dos arboles
int Alternative::ted(const Tree& T, const Tree& T1) {
    std::vector<std::vector<int>> components_T = T.decompose();
    std::vector<std::vector<int>> components_T1 = T1.decompose();
    std::vector<int> representatives_T = T.leftmost(); 
    std::vector<int> representatives_T1 = T1.leftmost(); 
    std::vector<std::pair<int, int>> matching = match_components(T, T1, components_T, components_T1, representatives_T, representatives_T1);

    int total_distance = 0;
    for (auto& pair : matching) {
        int i = pair.first;
        int j = pair.second;
        std::string s_T = T.pre_order();
        std::string s_T1 = T1.pre_order();
        int distance = string_edit_distance(s_T, s_T1);
        total_distance += distance/int(std::min(T.n, T1.n));
    }

    return total_distance;
}