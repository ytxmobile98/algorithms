# KMP Algorithm for Pattern Searching

## Problem Description

Given a text `txt[0...n-1]` and a pattern `pat[0..m-1]`, write a function `search(char pat[], char txt[])` that prints all occurrences of `pat[]` in `txt[]`. You may assume that `n > m`.

### Examples

* **Example 1**
    * Input: `txt[] = "THIS IS A TEST TEXT", pat[] = "TEST"`
    * Output: `[10]`
* **Example 2**
    * Input: `txt[] = "AABAACAADAABAABA", pat[] = "AABA"`
    * Output: `[0, 9, 12]`

## Solution

The KMP algorithm uses degenerating property (pattern having the same sub-patterns appearing more than once) of the pattern so that it improves the _worst-case complexity_ to **O(n+m)**.

Basic idea: Whenever we detect a mismatch (after some matches), we already know some of the characters in the text of the next window. We take advantage of this information to avoid matching the characters that we know will anyway match.

### Example

`txt = "AAAAABAAABA", pat = "AAAA"`

1. Compare first window of `txt` with `pat`

    ```
    txt = "AAAAABAAABA"
           ↑
    pat = "AAAA"

    → ✅ Match found.
    ```
2. Compare next window of `txt` with `pat`

    ```
    txt = "AAAAABAAABA"
            ↑
    pat =  "AAAA"

    → ✅ We already know that the first three characters have matched. So we only need to compare the fourth A in pattern with the fourth character of the current window, skipping the first three characters.
    ```

### Preprocessing

The core issue is to know _how many characters to skip_. To know this we _pre-process_ the pattern and prepare an integer array `lps[]` that tells us the count of characters to skip.

#### Preprocessing Overview

* KMP algorithm preprocesses `pat[]` and constructs an auxiliary `lps[]` of size **m** (same as the size of the pattern) which is used to skip characters while matching.
* Name `lps` indicates the **longest proper prefix** which is also a suffix. A proper prefix is a prefix that is not the whole string. For example:
    * Prefixes of "ABC" are "", "A", "AB" and "ABC".
    * Proper prefixes of "ABC" are "", "A" and "AB".
    * Suffixes of the string are "", "C", "BC", and "ABC".
* We search for lps in sub-patterns. More clearly we focus on sub-strings of patterns that are both prefix and suffix.
* For each sub-pattern `pat[0..i]` where `i = 0 to m-1`, `lps[i]` stores the **length of the maximum matching proper prefix** which is also a suffix of the sub-pattern `pat[0..i]`.

    ```
    lps[i] = the longest proper prefix of pat[0..i]
             which is also a suffix of pat[0..i].
    ```

**Note:** `lps[i]` could also be defined as the longest prefix which is also a proper suffix. We need to use it properly in one place to make sure that the whole substring is not considered.

An example of the `lps[]` construction:

| Pattern | `lps[]` |
|---------|---------|
| `AAAAA` | `[0, 1, 2, 3]` |
| `ABCDE` | `[0, 0, 0, 0, 0]` |
| `AABAACAABAA` | `[0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]` |
| `AAACAAAAAC` | `[0, 1, 2, 0, 1, 2, 3, 3, 3, 4]` |
| `AAABAAA` | `[0, 1, 2, 0, 1, 2, 3]` |

## References

* [GeeksForGeeks: KMP Algorithm for Pattern Searching](https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/)