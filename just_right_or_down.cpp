#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//структура позиции клетки, хранит два целых числа,
struct point {
    int i, j;

    bool operator==(point& other) {
        return i==other.i && j==other.j;
    }
};

//структура 
struct cell {
    point position;                  //позиция клетки
    int value;                       //значение клетки
    vector<vector<point>> paths;     //массив всех возможных путей до этой, представленный как массив путей, путь в свою очередь это массив позиций
};

//функция сравнений двух путей
bool path_cmp(vector<point>& p1, vector<point>& p2) {
    return p1.size() < p2.size();
}


struct game {
    int n, m;                       //размеры поля
    vector<vector<cell>> field;     //поле (матрица клеток)

    //создаем поле размером _n x _m
    game(int _n, int _m) {

        //размеры поля
        n = _n;
        m = _m;

        field = vector<vector<cell>>(n); //генерируем пустые строчки поля

        for (int i = 0; i < n; ++i) {
            //генерируем i'ую строку
            field[i] = vector<cell>(m); 
            for (int j = 0; j < m; ++j) {
                field[i][j].position = { i, j};
            }
        }
    }

    //проверка, что есть клетка с позициец i, j;
    bool in_field(int i, int j) {
        return i >= 0 && j >= 0 && i < n && j < m;
    }

    //функция считывания значений 
    void scan() {
        cout << "Введите поле:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> field[i][j].value;
                field[i][j].paths = vector<vector<point>>(); //сбрасываем все пути до этой клетки
            }
        }
    }

    //функция, которая имитирует переход из клетки c в клетку [i][j]
    void from_to(cell c, int i, int j) {

        if (in_field(i, j)) { //если мы не выходим за пределы игрового поля

            //добавляем все пути текующей клетки в следующую, а также добавляем туда следующую клетку
            for (vector<point> path: c.paths) {
                field[i][j].paths.push_back(path);
                field[i][j].paths.back().push_back({i, j});
            }
        }
    }

    //функция которая считает все возможные пути и строит пути для каждой клетки
    void calc() {
        
        //к нулевой клетке есть единственный путь, который хранит эту же клетку
        field[0][0].paths.push_back(vector<point>()); 
        field[0][0].paths[0].push_back({ 0, 0 });
        
        //перебираем клетки и делаем переходы из тех, у которых не пустой путь
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (field[i][j].value == 0) { continue; } 

                //если к точке есть путь, проходим через нее вправо и вниз
                if (field[i][j].paths.size() != 0) {
                    from_to(field[i][j], i + field[i][j].value, j);
                    from_to(field[i][j], i, j + field[i][j].value);
                }
            }
        }
    }

    //вывод поля 
    void print_field() {
        cout << "\nИгровое поле:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << field[i][j].value << "\t";
            }cout << '\n';
        }cout << '\n';
    }

    //функция для вывода пути
    void print_path(vector<point>& path) {
        for (point& p : path) {
            printf(" -> (%d, %d)[%d]", p.i, p.j, field[p.i][p.j].value);
        }
        cout << '\n';
    }


    //вывод клетки поля (вcех путей до этой клетки)
    void print_cell(int _i, int _j) {

        //сортируем
        sort(field[_i][_j].paths.begin(), field[_i][_j].paths.end(), path_cmp);
        
        //перебираем пути
        for (size_t p = 0; p < field[_i][_j].paths.size(); ++p) {

            //k указывает на рассматриваемую точку p'ого пути
            size_t k = 0;
            printf("%zu'й путь:\n", p+1);
            print_path(field[_i][_j].paths[p]);
            //перебираем все клетки поля, и если они соответствуют текущей точки, обозначаем ее при выводе и переходим к k+1'ой точке
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    printf("\t%3d", field[i][j].value);
                    if (k < field[_i][_j].paths[p].size() && field[_i][_j].paths[p][k] == field[i][j].position) {
                        ++k;
                        cout << "<-";
                    }
                }
                cout << '\n';
            }
            cout << '\n';
        }

        
        int min_ind = -1;   //индекс пути с минимальной суммой цифр
        int min_sum = 0;    //сама мин сумма

        //поиск пути с минимальной суммой цифр
        for (size_t pi = 0; pi < field[_i][_j].paths.size(); ++pi) {
            int sum = 0;

            //перебираем все точки пути и считаем сумму цифр
            for (point p : field[_i][_j].paths[pi]) {
                int v = field[p.i][p.j].value;
                while (v > 0) {
                    sum += v % 10;
                    v /= 10;
                }
            }

            //если нашли ответ лучше, обновляем
            if (min_ind == -1 || min_sum > sum) {
                min_ind = pi;
                min_sum = sum;
            }
        }

        //выводим
        if (min_ind != -1) {
            printf("Путь с минимальной суммой цифр: ");
            print_path(field[_i][_j].paths[min_ind]);
        }
        else {
            cout << "Нет ни одного пути.";
        }
    }
    
};

int main() {
    setlocale(LC_ALL, "Russian");

    int n, m;
    cout << "Введите размеры поля: ";
    cin >> n >> m;
    game g(n, m);

    //считываем поле
    g.scan();

    //выводим поле
    g.print_field();

    //считаем пути
    g.calc();

    //выводим все пути последней клетки
    g.print_cell(n-1, m-1);
    
    return 0;
}
