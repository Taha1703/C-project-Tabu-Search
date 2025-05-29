#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

struct Element {
    int profit, weight, touched;
};

class TabuSearch {
private:
    std::vector<Element> elements;
    int capacity;
    int tabu_duration;
    int max_iterations;
    int print_every;

    int current_iter = 0;
    int best_profit = 0;
    int best_weight = 0;
    std::vector<bool> best_solution;

public:
// daten einlesen lol 
    TabuSearch(const std::string& filename, int td, int iterations, int m) {
        readData(filename);
        tabu_duration = td;
        max_iterations = iterations;
        print_every = m;
    }

    void readData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
            exit(1);
        }

        int n;
        file >> n >> capacity;
        elements.resize(n);

        for (int i = 0; i < n; ++i) {
            file >> elements[i].profit >> elements[i].weight;
            elements[i].touched = -1000;
        }
    }

    void initializeSolution(std::vector<bool>& x, int& profit, int& weight) {
        // sortiere nach Profit pro Gwicht
        std::vector<std::pair<double, int>> ratio;
        for (size_t i = 0; i < elements.size(); ++i) {
            double r = (double)elements[i].profit / elements[i].weight;
            ratio.push_back({r, i});
        }
        std::sort(ratio.rbegin(), ratio.rend());

        for (auto& [_, i] : ratio) {
            if (weight + elements[i].weight <= capacity) {
                x[i] = true;
                profit += elements[i].profit;
                weight += elements[i].weight;
            }
        }
    }

    void run() {
        srand(time(nullptr)); //zufallszahl 
        std::vector<bool> x(elements.size(), false);
        int current_profit = 0;
        int current_weight = 0;

        initializeSolution(x, current_profit, current_weight);

        best_profit = current_profit;
        best_weight = current_weight;
        best_solution = x;

        for (current_iter = 1; current_iter <= max_iterations; ++current_iter) {
            int best_delta = -1e9;
            int best_index = -1;
            bool best_add = false;

            for (size_t i = 0; i < elements.size(); ++i) {
                Element& e = elements[i];
                bool is_in = x[i];

                int delta_profit = is_in ? -e.profit : e.profit;
                int delta_weight = is_in ? -e.weight : e.weight;

                int new_profit = current_profit + delta_profit;
                int new_weight = current_weight + delta_weight;

                bool is_tabu = (current_iter <= e.touched);
                bool aspiration = (new_profit > best_profit); // Aspirationsbedigung Quelle 3 Pasper 3472364832154892470

                if ((new_weight <= capacity) && (!is_tabu || aspiration)) {
                    if (delta_profit > best_delta) {
                        best_delta = delta_profit;
                        best_index = i;
                        best_add = !is_in;
                    }
                }
            }

            if (best_index == -1) break;

            // Bewegung durchführen
            if (best_add) {
                x[best_index] = true;
                current_profit += elements[best_index].profit;
                current_weight += elements[best_index].weight;
            } else {
                x[best_index] = false;
                current_profit -= elements[best_index].profit;
                current_weight -= elements[best_index].weight;
            }

            // Dynamische Tabuzeit
            int dynamic_td = tabu_duration + (rand() % 3 - 1); // td ±1
            if (dynamic_td < 1) dynamic_td = 1;
            elements[best_index].touched = current_iter + dynamic_td;

            // Beste Lösung aktualisieren
            if (current_profit > best_profit && current_weight <= capacity) {
                best_profit = current_profit;
                best_weight = current_weight;
                best_solution = x;
            }

            if (print_every > 0 && current_iter % print_every == 0) {
                std::cout << "Iteration " << current_iter << ": Profit = "
                          << current_profit << ", Weight = " << current_weight << std::endl;
            }
        }

        // Endausgabe
        std::cout << "\nBest Solution after " << max_iterations << " iterations:\n";
        std::cout << "Total Profit: " << best_profit << "\n";
        std::cout << "Total Weight: " << best_weight << "\n";
        std::cout << "Solution: ";
        for (size_t i = 0; i < best_solution.size(); ++i)
            if (best_solution[i]) std::cout << i << " ";
        std::cout << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: ./tabu <datafile> <tabu_duration> <iterations> <m>\n";
        std::cerr << "Example: ./tabu data.1 3 100 10\n";
        return 1;
    }

    std::string filename = argv[1];
    int tabu_duration = std::stoi(argv[2]);
    int iterations = std::stoi(argv[3]);
    int m = std::stoi(argv[4]);

    TabuSearch ts(filename, tabu_duration, iterations, m);
    ts.run();

    return 0;
}
