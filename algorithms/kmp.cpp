#include <iostream>
#include <string>
#include <vector>

std::vector<int> getFailureArray(const std::string &pattern) {
    int pattern_length = pattern.size();
    std::vector<int> failure(pattern_length + 1);
    failure[0] = -1;
    int j = -1;

    for (int i = 0; i < pattern_length; i++) {
        while (j != -1 && pattern[j] != pattern[i]) {
            j = failure[j];
        }
        j++;
        failure[i + 1] = j;
    }
    return failure;
}

bool kmp(const std::string &pattern, const std::string &text) {
    int text_length = text.size(), pattern_length = pattern.size();
    std::vector<int> failure = getFailureArray(pattern);

    int k = 0;
    for (int j = 0; j < text_length; j++) {
        while (k != -1 && pattern[k] != text[j]) {
            k = failure[k];
        }
        k++;
        if (k == pattern_length)
            return true;
    }
    return false;
}

int main() {
    std::string text = "alskfjaldsabc1abc1abc12k23adsfabcabc";
    std::string pattern = "abc1abc12l";

    if (kmp(pattern, text) == true) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    text = "abcabc";
    pattern = "bca";
    if (kmp(pattern, text) == true) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    return 0;
}

