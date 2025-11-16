class ArrayGenerator {
    std::vector<int> randomBaseArray;
    std::vector<int> reversedBaseArray;
    std::vector<int> almostBaseArray;

    int maxLength;
    int minRange;
    int maxRange;

    void generateRandomBaseArray() {
        std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(minRange, maxRange);

        randomBaseArray.clear();
        randomBaseArray.reserve(maxLength);
        for (int i = 0; i < maxLength; ++i) {
            randomBaseArray.push_back(dist(gen));
        }
    }

    void generateReversedBaseArray() {
        std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)) + 1);
        std::uniform_int_distribution<int> dist(minRange, maxRange);

        reversedBaseArray.clear();
        reversedBaseArray.reserve(maxLength);
        for (int i = 0; i < maxLength; ++i) {
            reversedBaseArray.push_back(dist(gen));
        }

        std::sort(reversedBaseArray.rbegin(), reversedBaseArray.rend());
    }

    void generateAlmostBaseArray() {
        std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)) + 2);
        std::uniform_int_distribution<int> dist(minRange, maxRange);

        almostBaseArray.clear();
        almostBaseArray.reserve(maxLength);
        for (int i = 0; i < maxLength; ++i) {
            almostBaseArray.push_back(dist(gen));
        }
    }

public:
    ArrayGenerator()
        : maxLength(100000),
          minRange(0),
          maxRange(6000)
    {
        generateRandomBaseArray();
        generateReversedBaseArray();
        generateAlmostBaseArray();
    }

    std::vector<int> getRandomArray(int size) {
        if (size > maxLength) {
            size = maxLength;
        }
        return std::vector<int>(randomBaseArray.begin(),
                                randomBaseArray.begin() + size);
    }

    std::vector<int> getReversedArray(int size) {
        if (size > maxLength) {
            size = maxLength;
        }
        return std::vector<int>(reversedBaseArray.begin(),
                                reversedBaseArray.begin() + size);
    }

    std::vector<int> getAlmostSortedArray(int size, int swaps) {
        if (size > maxLength) {
            size = maxLength;
        }

        std::vector<int> almostSortedArray(almostBaseArray.begin(),
                                           almostBaseArray.begin() + size);

        std::sort(almostSortedArray.begin(), almostSortedArray.end());

        std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(0, size - 1);

        for (int i = 0; i < swaps; ++i) {
            int i1 = dist(gen);
            int i2 = dist(gen);
            std::swap(almostSortedArray[i1], almostSortedArray[i2]);
        }

        return almostSortedArray;
    }
};
