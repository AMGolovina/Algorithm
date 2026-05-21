class StringGenerator {
    // Алфавит
    inline static const std::string symbols_ =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%:;^&*()-";

    std::mt19937 rng_;
    std::uniform_int_distribution<> symbolDist_;
    std::uniform_int_distribution<> prefixCountDist_;
    std::uniform_int_distribution<> almostSwapDist_;
public:
    static constexpr int stringsLen = 3000;
    static constexpr int stringMinLen = 10;
    static constexpr int stringMaxLen = 200;

    static constexpr int prefixMinLen = 3;
    static constexpr int prefixMaxLen = 10;
    static constexpr int countPrefix = 10;
    static constexpr int prefixStringsMinCount = 5;
    static constexpr int prefixStringsMaxCount = 30;

    StringGenerator()
        : rng_(42),
          symbolDist_(0, static_cast<int>(symbols_.size()) - 1),
          prefixCountDist_(prefixStringsMinCount, prefixStringsMaxCount),
          almostSwapDist_(50, 150) {
    }

    // Генерация одной строки
    std::string generateString(const int minLen = stringMinLen, const int maxLen = stringMaxLen) {
        std::uniform_int_distribution lenDist(minLen, maxLen);
        const int length = lenDist(rng_);

        std::string result;
        result.reserve(length);

        for (int i = 0; i < length; ++i) {
            result.push_back(symbols_[symbolDist_(rng_)]);
        }

        return result;
    }

    // Генерация страны с совпадающими префиксами
    std::vector<std::string> generatePrefixStrings() {
        std::vector<std::string> strings;

        for (int i = 0; i < countPrefix; ++i) {
            std::string prefix = generateString(prefixMinLen, prefixMaxLen);
            const int stringWithPrefixCount = prefixCountDist_(rng_);

            for (int j = 0; j < stringWithPrefixCount; ++j) {
                std::uniform_int_distribution<> currentPrefixLenDist(
                    prefixMinLen,
                    static_cast<int>(prefix.size())
                );

                const int currentPrefixLen = currentPrefixLenDist(rng_);
                strings.push_back(
                    prefix.substr(0, currentPrefixLen) + generateString()
                );
            }
        }

        return strings;
    }

    // Генерация массива строк
    std::vector<std::string> generate() {
        std::vector<std::string> strings = generatePrefixStrings();

        const int countWithoutPrefix = stringsLen - static_cast<int>(strings.size());
        for (int i = 0; i < countWithoutPrefix; ++i) {
            strings.push_back(generateString());
        }

        return strings;
    }

    // Отсортированный массив
    std::vector<std::string> generateSorted() {
        std::vector<std::string> strings = generate();
        std::ranges::sort(strings);
        return strings;
    }

    // В обратном порядке массив
    std::vector<std::string> generateReversedSorted() {
        std::vector<std::string> strings = generateSorted();
        std::ranges::reverse(strings);
        return strings;
    }

    // Почти отсортированный
    std::vector<std::string> generateAlmostSorted() {
        std::vector<std::string> strings = generateSorted();

        const int k = almostSwapDist_(rng_);
        std::uniform_int_distribution indexDist(0, static_cast<int>(strings.size()) - 1);

        for (int i = 0; i < k; ++i) {
            const int a = indexDist(rng_);
            const int b = indexDist(rng_);
            std::swap(strings[a], strings[b]);
        }

        return strings;
    }
};
