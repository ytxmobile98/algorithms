#include <cstring>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

static ostream& operator<<(ostream& ostream, vector<int>& result) {
    ostream << "[";

    for (size_t i = 0; i < result.size(); ++i) {
        ostream << result[i];
        if (i < result.size() - 1) {
            ostream << ", ";
        }
    }

    return ostream << "]";
}

static vector<int> computeLPS(const char* pattern) {
    vector<int> lps(strlen(pattern));
    lps[0] = 0;
    size_t len = 0;
    for (size_t i = 1; i < lps.size();) {
        if (pattern[i] == pattern[len]) {
            lps[i] = ++len;
            ++i;
        } else {
            if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }
    return lps;
}

static vector<int> computeKMP(const char* text, const char* pattern) {
    size_t textLen = strlen(text);
    size_t patternLen = strlen(pattern);
    if (textLen < patternLen) {
        return vector<int>();
    }

    vector<int> lps = computeLPS(pattern);

    vector<int> result;
    size_t i = 0;
    size_t j = 0;
    while ((textLen - i) >= (patternLen - j)) {
        if (pattern[j] == text[i]) {
            ++i;
            ++j;
        }

        if (j == patternLen) {
            result.push_back(i - j); // record the starting position
            j = lps[j - 1];
        } else if (i < textLen && (pattern[j] != text[i])) {
            // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1];
            } else {
                ++i;
            }
        }
    }

    return result;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <text> <pattern>" << endl;
        return 0;
    }

    const char* text = argv[1];
    const char* pattern = argv[2];

    vector<int> result = computeKMP(text, pattern);
    cout << result << endl;

    return 0;
}