#define INF (NAN)

#include "kdeader.hpp"

std::function<bool(double)> isinf = [](double elem) { return std::isnan(elem); };

int main() {
    matvec cost_matrix{
{INF, 10, 8, 19, 12},
  {10, INF, 20, 6, 3},
  {8, 20, INF, 4, 2},
  {19, 6, 4, INF, 7},
  {12, 3, 2, 7, INF}
};
    ivec best_path = tsp(cost_matrix);
    std::cout<<"Found path: \n";
    for(auto elem = best_path.begin(); elem!=best_path.end(); elem++){
        std::cout<< (*elem)+1 << ", ";
    }
    return 0;

}

ivec tsp(matvec cost_matrix){

    ivec path;
    std::map<int, ivec> pairs;
    std::size_t iteration = (cost_matrix.size()/2) +1;
    while(iteration<cost_matrix.size()){
        /*  Redukcja w pionie  */
        for(std::size_t i=0; i<cost_matrix.size(); i++){
            double min_el = infinity;
            for(std::size_t j=0; j<cost_matrix.size(); j++){
                if (min_el>cost_matrix[i][j]) min_el = cost_matrix[i][j];
            }
            for(std::size_t j=0; j<cost_matrix.size(); j++){
                cost_matrix[i][j] -= min_el;
            }
        }

    /*  Redukcja w poziomie  */
        for(std::size_t j=0; j<cost_matrix.size(); j++){
            double min_el = infinity;
            for(std::size_t i=0; i<cost_matrix.size(); i++){
                if (min_el>cost_matrix[i][j]) min_el = cost_matrix[i][j];
            }
            for(std::size_t i=0; i<cost_matrix.size(); i++){
                cost_matrix[i][j] -= min_el;
            }
        }
    /*  Minimalna wartoœæ dla przeciec w 0  */
        int max_path_val[3] = {0,0,0};  //tablica przechowuje kolejno sume wartości dla skrzyżowania, wiersz i kolumne dla odrzucanego skrzyzowania
        for(std::size_t j=0; j<cost_matrix.size(); j++){
            for(std::size_t i=0; i<cost_matrix.size(); i++){
                if(cost_matrix[i][j]==0){
                    int min_xing_val = find_min_value(cost_matrix, i, j);
                    if(min_xing_val > max_path_val[0]){
                        max_path_val[0] = min_xing_val;
                        max_path_val[1] = i;
                        max_path_val[2] = j;
                    }
                }
            }
        }
    /* Usuwanie odpowiedniego rzędu i kolumny*/
        pairs[max_path_val[1]].push_back(max_path_val[2]);
        pairs[max_path_val[2]].push_back(max_path_val[1]);
        for(std::size_t i=0; i<cost_matrix.size(); i++){
            cost_matrix[i][max_path_val[2]]=INF;
        }
        for(std::size_t j=0; j<cost_matrix.size(); j++){
            cost_matrix[max_path_val[1]][j]=INF;
        }
        cost_matrix[max_path_val[2]][max_path_val[1]] = INF;

        iteration--;
    }
/* ostatnie przejście */
for(int i=0; i<cost_matrix.size(); i++){
    int licznik = 0;
    int col;
    for(int j=0; j<cost_matrix.size(); j++){
            if(cost_matrix[i][j]==0){
                licznik++;
                col = j;
            }
        }
    if(licznik==1){
        pairs[col].push_back(i);
        pairs[i].push_back(col);
    }
}
for(int j=0; j<cost_matrix.size(); j++){
    int licznik = 0;
    int row;
    for(int i=0; i<cost_matrix.size(); i++){
            if(cost_matrix[i][j]==0){
                licznik++;
                row = i;
            }
        }
    if(licznik==1){
        pairs[j].push_back(row);
        pairs[row].push_back(j);
    }
}

/* Wpisywanie kolejnych elementów do ścieżki - zaczynając od wierzchołka 1 (0 w macierzy) */
    return write_path(pairs, 0);
}

double find_min_value(matvec cost_matrix, int i, int j){
    double min_row_value = infinity;
    double min_col_value = infinity;

    for(std::size_t i_it=0; i_it<cost_matrix.size(); i_it++){
        if(cost_matrix[i_it][j]<min_col_value && i_it!=i) min_col_value=cost_matrix[i_it][j];
    }
    for(std::size_t j_it=0; j_it<cost_matrix.size(); j_it++){
        if(cost_matrix[i][j_it]<min_row_value && j_it!=j) min_row_value=cost_matrix[i][j_it];
    }

    return min_row_value + min_col_value;
}
ivec write_path(std::map<int,ivec> pairs, int start){
    ivec path;
    path.push_back(start);
    int next = pairs[start][0];
    while(next!=start){
        path.push_back(next);
        if(pairs[next][0]==*(path.end()-2)) next=pairs[next][1];
        else next = pairs[next][0];
    }
    path.push_back(next);
    return path;
}
