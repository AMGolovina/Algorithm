// Набор строк для разных типов входных данных
struct StringData {
    std::vector<std::string> random;
    std::vector<std::string> reversed;
    std::vector<std::string> almost_sorted;
};

// Результат экспиремента для конкретного алгоритма
struct ExperimentRow {
    std::string algorithm;
    std::string dataset;
    int size = 0;
    long long comparisons = 0;
    long long timeMicroseconds = 0;
};

class StringSortTester {
    StringData data_;
    int runs_;
    std::vector<ExperimentRow> results_;

    // Несколько запусков сортировки и усреднение
    std::pair<long long, long long> analyze(
        const std::vector<std::string>& strings,
        SortFunc sortFn
    ) const {
        long long timeSum = 0;
        long long comparisonSum = 0;

        for (int i = 0; i < runs_; ++i) {
            std::vector<std::string> copy = strings;
            long long comparisons = 0;

            const auto start = std::chrono::high_resolution_clock::now();
            sortFn(copy, comparisons);
            const auto end = std::chrono::high_resolution_clock::now();

            const auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            timeSum += duration;
            comparisonSum += comparisons;
        }

        return {comparisonSum / runs_, timeSum / runs_};
    }

    // Анализ для заданного размера
    void analyzeOnData(int count, SortFunc sortFn, const std::string& name) {
        {
            std::vector<std::string> v(data_.random.begin(), data_.random.begin() + count);
            auto [comp, time] = analyze(v, sortFn);
            results_.push_back({name, "random", count, comp, time});
        }
        {
            std::vector<std::string> v(data_.reversed.begin(), data_.reversed.begin() + count);
            auto [comp, time] = analyze(v, sortFn);
            results_.push_back({name, "reversed", count, comp, time});
        }
        {
            std::vector<std::string> v(data_.almost_sorted.begin(), data_.almost_sorted.begin() + count);
            auto [comp, time] = analyze(v, sortFn);
            results_.push_back({name, "almost_sorted", count, comp, time});
        }
    }
public:
    explicit StringSortTester(const StringData& inputData, int runs = 10)
        : data_(inputData), runs_(runs) {
    }

    // Тестируем один массив с заданным размером от 100 до 3000
    void testAlgorithm(const std::string& name, SortFunc sortFn) {
        for (int size = 100; size <= 3000; size += 100) {
            analyzeOnData(size, sortFn, name);
        }
    }

    // Сохранение результата в файл
    void saveResults(const std::string& outputPath) const {
        std::ofstream out(outputPath);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open output file: " + outputPath);
        }

        out << "algorithm,dataset,size,comparisons,time_microseconds\n";
        for (const auto& row : results_) {
            out << row.algorithm << ','
                << row.dataset << ','
                << row.size << ','
                << row.comparisons << ','
                << row.timeMicroseconds << '\n';
        }
    }
};
