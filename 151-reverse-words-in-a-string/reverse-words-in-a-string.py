class Solution(object):
    def reverseWords(self, s):
        words = []
        n = len(s)
        i = 0

        while i < n:
            # Skip spaces
            while i < n and s[i] == " ":
                i += 1
            if i >= n:
                break

            # Find the end of the current word
            j = i
            while j < n and s[j] != " ":
                j += 1

            # Extract the word and add to our list
            words.append(s[i:j])
            i = j

        # Reverse the list of words and join with a single space
        words.reverse()
        return " ".join(words)
        