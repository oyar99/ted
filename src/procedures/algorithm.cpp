#include <tree.h>
#include <algorithm.h>


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

// Función para emparejar componentes de dos árboles
// Aca solo empareja los componentes de ambos arboles tal como vienen del preorden y los que sobran con -1
std::vector<std::pair<int, int>> match_components(const std::vector<std::vector<int>>& components_T, const std::vector<std::vector<int>>& components_T1, const std::vector<int>& representatives_T, const std::vector<int>& representatives_T1) {
    std::vector<std::pair<int, int>> matching;

    int i = 0, j = 0;
    while (i < representatives_T.size() || j < representatives_T1.size()) {
        int rep_T = (i < representatives_T.size()) ? representatives_T[i] : -1;
        int rep_T1 = (j < representatives_T1.size()) ? representatives_T1[j] : -1;
        matching.push_back({rep_T, rep_T1});
        if (rep_T != -1) i++;
        if (rep_T1 != -1) j++;
    }

    return matching;
}

// Funcion principal que calcula la distancia de edicion entre dos arboles
int ted(const Tree& T, const Tree& T1) {
    std::vector<std::vector<int>> components_T = T.decompose();
    std::vector<std::vector<int>> components_T1 = T1.decompose();
    std::vector<int> representatives_T = T.leftmost(); 
    std::vector<int> representatives_T1 = T1.leftmost(); 
    std::vector<std::pair<int, int>> matching = match_components(components_T, components_T1, representatives_T, representatives_T1);

    int total_distance = 0;
    for (auto& pair : matching) {
        int i = pair.first;
        int j = pair.second;
        std::string s_T = T.pre_order();
        std::string s_T1 = T1.pre_order();
        int distance = string_edit_distance(s_T, s_T1);
        total_distance += distance;
    }

    return total_distance;
}