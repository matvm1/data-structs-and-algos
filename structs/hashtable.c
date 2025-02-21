// Implements a dictionary's functionality
// Implemented for CS50's data structures problem set

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "structs.h"

// Represents a bucket with a range of values
// Used by earlier versions of hthash()
typedef struct rbucket
{
    int min;
    int max;
} rbucket;

static void hash_design_helper(const char *dictionary, char mode);
static void fill_rbucket_lettersums(rbucket *sb);
static int search_rbucket(int n, rbucket sb[], int start, int size);
static unsigned int hash_sum_chars(const char *word);
static unsigned int hash_word_len(const char *word);
static unsigned int hash_first_letter_freq(const char *word);
static unsigned int hash_vowel_freq(const char *word);
static unsigned int hash_char_factorization(const char *word);

// Number of buckets in hash table. Hash table is 1.084 times the sizeof the dictionary (155K/143K
// words)
const unsigned int htN = 155000;

// Constants used in earlier versions of the hash function.
const int htINT_MAX = 2147483647;
const int SB_SIZE = 34;
const int WORD_LEN_BUCK_SIZE = 4;

// Word count tracker
int load_count = 0;

// Load indicator
int is_table_loaded = 0;

// Hash table
htnode *table[htN];

// Returns 1 if word is in dictionary, else 0
int htcheck(const char *word)
{
    unsigned int hash_val = hthash(word);

    if (table[hash_val] == NULL)
        return 0;

    htnode *i = table[hash_val];
    // Search for the word with case insensitive string compare until found or the end of the list
    while (i != NULL)
    {
        if(strcmp_i(word, i->word))
            return 1;
        i = i->next;
    }

    return 0;
}

// Hashes word to a number
// Latest version uses factorization of characters in word
unsigned int hthash(const char *word)
{
    unsigned int h = hash_char_factorization(word);
    return (h == htINT_MAX) ? 0 : h;
}

// Returns a hash by summing each character value times its index times a factor
// Indexfactor is redcued for long words to enhance data distribution whilst maintaing memory usage
// low This likely canbe fine tuned to yield a greater load factor Returns htINT_MAX if long integer
// overflow occurs
unsigned int hash_char_factorization(const char *word)
{
    // Index factor
    float ind_factor = 28.5;
    // Index factor for long words
    float lengthy_ind_factor = 3.0;
    // Long word length
    int lengthy_word = 10;

    long h = 0;
    float i_factor = ind_factor;

    for (int i = 0; word[i] != '\0'; i++)
    {
        // Dictionary stores words in lower case
        char c = tolower(word[i]);

        // Index wieght is the index times the factor, squared
        float ind_weight = pow((float) i + i_factor, 2);

        // Get the value of the current character, 0.5 for apostrophes
        float char_val = (c == '\'') ? 0.5 : c - 'a' + 1;

        // Add weighted result to the total hash
        h += round(ind_weight * char_val);

        // Reduce the index factor for lengthy words
        if (i + 1 > lengthy_word)
        {
            i_factor = lengthy_ind_factor;
        }
    }

    // Long int overflow occurred
    if (h < 0)
    {
        printf("Overflow while hashing word: %s\n", word);
        return htINT_MAX;
    }

    // Mod by the size of the array if the hash key is greater than the size of the array
    if (h >= htN)
        h %= htN;

    return (unsigned int) h;
}

// Case insensitive string compare
// Returns 1 if a is lexicogrpahically equivalent to b, 0 otherwise
int strcmp_i(const char *a, const char *b)
{
    int i;

    for (i = 0; a[i] != '\0'; i++)
    {
        // String characters aren't equal at the current index
        if (tolower(a[i]) != tolower(b[i]))
            return 0;

        // b is shorther than a
        if (b[i] == '\0')
            return 0;
    }

    // At this point, i is the index of the NUL terminator in string a
    // Return 0 if both strings terminate at the same index
    if(b[i] == '\0')
        return 1;

    return 0;
}

// Loads dictionary into memory, returning 1 if successful, else 0
// Hash table is 1.084 times the size of the dictionary (155K/143K)
// Load factor = 58.8%
int htload(const char *dictionary)
{
    // Open the dictionary text file
    FILE *dict_source = fopen(dictionary, "r");
    if (dict_source == NULL)
    {
        return 0;
    }

    // Buffer for reading in a max possible htWORDLENGTH chars + '\n' + NUL terminator using fgets
    char buf[htWORDLENGTH + 2];

    // Read a line (terminated by newline) until the end of the file
    while (fgets(buf, sizeof(buf), dict_source) != NULL)
    {
        int buf_len = strlen(buf);

        // If buf contains a word and the newline separator (i.e. htWORDLENGTH chars (or less) + '\n' read
        // into buf) Skips load for words over the htWORDLENGTH limit
        if (buf[buf_len - 1] == '\n' && buf_len > 1)
        {
            // Move the NUL terminator back and replace the newline
            buf[buf_len - 1] = '\0';
            buf_len--;

            // Increate the load count
            load_count++;

            // Get the hash value for the word
            unsigned int hash_buf = hthash(buf);

            // Error handling in case hash_buf exceeds the size of the array
            if (hash_buf >= htN)
            {
                printf("Error hashing: %s resulted in %i\n", buf, hash_buf);
                fclose(dict_source);
                htunload();
                return 0;
            }

            // If memoery for the htnode has not been allocated
            if (table[hash_buf] == NULL)
            {
                // Allocate and copy the string into the htnode->word
                table[hash_buf] = calloc(1, sizeof(htnode));
                if (table[hash_buf] == NULL)
                {
                    fclose(dict_source);
                    htunload();
                    return 0;
                }
                strcpy(table[hash_buf]->word, buf);
            }
            else // Estend the nodes' linked list
            {
                htnode *i = table[hash_buf];

                // Find the last htnode in the list whilst mainting reference to the list
                while (i->next != NULL)
                {
                    i = i->next;
                }

                // Allocate memory and copy string into i->next->word
                i->next = calloc(1, sizeof(htnode));
                if (i->next == NULL)
                {
                    fclose(dict_source);
                    htunload();
                    return 0;
                }
                strcpy(i->next->word, buf);
            }
        }
        else if (buf[0] == '\n') // Handle newline "gaps" in the dictionary
        {
            continue;
        }
        else // Word is over the htWORDLENGTH limit, keep reading from file until a newline is found
        {
            while (fgetc(dict_source) != '\n' && !feof(dict_source))
            {
                continue;
            }
        }
    }

    //. Indicate globally that hash table has been loaded
    is_table_loaded = 1;

    fclose(dict_source);

    return 1;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int htsize(void)
{
    return (is_table_loaded) ? load_count : 0;
}

// Unloads dictionary from memory, returning 1 if successful, else 0
int htunload(void)
{
    // For all nodes
    for (int i = 0; i < htN; i++)
    {
        // If the htnode has been allocated
        if (table[i] != NULL)
        {
            // Keep track of the htnode whilst traversing its linked list
            htnode *n = table[i];

            // For all nodes in the list
            while (n != NULL)
            {
                // Get the next htnode in the list
                htnode *m = n->next;
                // Free the previous htnode
                free(n);
                // Move the tracker to the next htnode
                n = m;
            }
        }
    }

    return 1;
}

// 'f' - first letter count, 'c' - letter presence in words, 'l' - word length, 's' - sum of
// characters, 'v' - vowel count, 'i' - factorization
static void hash_design_helper(const char *dictionary, char mode)
{
    FILE *dict_source = fopen(dictionary, "r");
    if (dict_source == NULL)
    {
        return;
    }

    int alph[27];
    if (mode == 'f' || mode == 'c')
        for (int i = 0; i < 27; i++)
            alph[i] = 0;

    int lens[htWORDLENGTH];
    if (mode == 'l')
        for (int i = 0; i < htWORDLENGTH; i++)
            lens[i] = 0;

    const int MAX_SUM = 270;
    int sums[MAX_SUM + 1];
    if (mode == 's')
        for (int i = 0; i < MAX_SUM + 1; i++)
            sums[i] = 0;

    const int MAX_VOWEL_COUNT = 7;
    int vowel_counts[MAX_VOWEL_COUNT + 1];
    if (mode == 'v')
        for (int i = 0; i < MAX_VOWEL_COUNT + 1; i++)
            vowel_counts[i] = 0;

    const int MAX_INDEX_FACTORIZATION = 155000;
    int ind_f[MAX_INDEX_FACTORIZATION + 1];
    long max_f;
    float ind_factor = 28.5; // Fine tuning
    float lengthy_ind_factor = 3.0;
    float lengthy_char_factor = 0.9;
    int large_f_short_word = 0;
    int lengthy_word = 10;
    if (mode == 'i')
    {
        for (int i = 0; i < MAX_INDEX_FACTORIZATION + 1; i++)
            ind_f[i] = 0;
        max_f = 0;
    }

    char buf[htWORDLENGTH + 1];
    int d = 0;
    while (fgets(buf, sizeof(buf), dict_source) != NULL)
    {
        d++;
        int buf_len = strlen(buf);

        if (buf[buf_len - 1] == '\n')
        {
            buf[buf_len - 1] = '\0';
            buf_len--;
        }

        if (mode == 'f')
        {
            if (buf[0] == '\'')
                alph[26]++;
            else
                alph[buf[0] - 'a']++;
        }
        else if (mode == 'c')
        {
            int word_alph[27];
            for (int i = 0; i < 27; i++)
            {
                word_alph[i] = 0;
            }
            for (int i = 0; i < strlen(buf); i++)
            {
                if (buf[i] == '\'')
                    word_alph[26] = 1;
                else
                    word_alph[buf[i] - 'a'] = 1;
            }

            for (int i = 0; i < 27; i++)
            {
                alph[i] += word_alph[i];
            }
        }
        else if (mode == 'l')
        {
            lens[buf_len - 1]++;
        }
        else if (mode == 's')
        {
            int word_sum = 0;

            for (int i = 0; i < buf_len; i++)
            {
                if (buf[i] == '\'')
                    word_sum += 27;
                else
                    word_sum += buf[i] - 'a' + 1;
            }
            if (word_sum > MAX_SUM)
            {
                sums[MAX_SUM]++;
            }
            else
                sums[word_sum - 1]++;
        }
        else if (mode == 'v')
        {
            int word_vowel_count = 0;
            for (int i = 0; i < buf_len; i++)
            {
                if (buf[i] == 'a' || buf[i] == 'e' || buf[i] == 'i' || buf[i] == 'o' ||
                    buf[i] == 'u')
                    word_vowel_count++;
            }
            if (word_vowel_count > MAX_VOWEL_COUNT)
            {
                vowel_counts[MAX_VOWEL_COUNT]++;
            }
            else
                vowel_counts[word_vowel_count - 1]++;
        }
        else if (mode == 'i')
        {
            long f = 1;
            float i_factor = ind_factor;

            for (int i = 0; i < buf_len; i++)
            {
                float ind_weight = pow((float) i + i_factor, 2);

                float char_val = (buf[i] == '\'') ? 0.5 : buf[i] - 'a' + 1;

                f += round(ind_weight * char_val);

                if (i + 1 > lengthy_word)
                {
                    i_factor = lengthy_ind_factor;
                }
            }
            if (f < 0)
                printf("%s %li\n", buf, f);
            if (f > MAX_INDEX_FACTORIZATION)
            {
                f %= MAX_INDEX_FACTORIZATION;
                if (buf_len < lengthy_word)
                    large_f_short_word++;
            }
            ind_f[f - 1]++;
            if (f > max_f)
                max_f = f;
        }
    }

    if (mode == 'f')
    {
        for (int i = 0; i < 26; i++)
        {
            printf("%c:%i ", i + 'A', alph[i]);
            if ((i + 1) % 5 == 0)
                printf("\n");
        }
        printf("apostrophes: %i\n", alph[26]);
    }
    else if (mode == 'l')
    {
        for (int i = 0; i < htWORDLENGTH; i++)
        {
            printf("%i:%i ", i + 1, lens[i]);
            if ((i + 1) % 8 == 0)
                printf("\n");
        }
    }
    else if (mode == 's')
    {
        for (int i = 0; i < MAX_SUM; i++)
        {
            printf("%i:%i ", i + 1, sums[i]);
            if ((i + 1) % 10 == 0)
                printf("\n");
        }
        printf("%i+: %i\n", MAX_SUM + 1, sums[MAX_SUM]);
    }
    else if (mode == 'v')
    {
        for (int i = 0; i < MAX_VOWEL_COUNT; i++)
        {
            printf("%i:%i ", i + 1, vowel_counts[i]);
            if ((i + 1) % 3 == 0)
                printf("\n");
        }
        printf("%i+: %i\n", MAX_VOWEL_COUNT + 1, vowel_counts[MAX_VOWEL_COUNT]);
    }
    else if (mode == 'i')
    {
        int p = 0;
        int max_coll = 0;
        int max_coll_buck = 0;
        for (int i = 0; i < MAX_INDEX_FACTORIZATION; i++)
        {
            if (ind_f[i] > 0)
            {
                p++;

                if (ind_f[i] > max_coll)
                {
                    max_coll = ind_f[i];
                    max_coll_buck = i;
                }
            }
        }
        printf("%i+: %i\nNon-empty Buckets:%i\nMax Collisions: %i at bucket %i\nMax index: "
               "%li\nind_factor: %2.02f lengthy_ind_factor: %2.02f lengthy_word: %i\nShort words "
               "with large result: %i\n",
               MAX_INDEX_FACTORIZATION + 1, ind_f[MAX_INDEX_FACTORIZATION], p + 1, max_coll,
               max_coll_buck, max_f - 1, ind_factor, lengthy_ind_factor, lengthy_word,
               large_f_short_word);
    }
    printf("\n\nTotal words: %i\n\n", d);

    fclose(dict_source);
}

// Sum of characters (34 buckets)
static unsigned int hash_sum_chars(const char *word)
{
    rbucket sb[SB_SIZE];

    // Fill sb with range buckers used in sum of chars
    fill_rbucket_lettersums(sb);

    int word_sum = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '\'')
            word_sum += 27;
        else
            word_sum += word[i] - 'a' + 1;
    }

    // Search for the sum in the range buckets
    return search_rbucket(word_sum, sb, 0, SB_SIZE - 1);
}

// Frequency of initial letter of words: (11 buckets)
// A/G (13,633), C (13,042), F/I/J/Q (12,109), B/K/W (12,107), L/M (13,415), D/N (11,776), P
// (12,176), O/R/X/Y/Z (12,062), S (15,616), V/U/H (12,631), E/T/Apostrophes (13,525)
static unsigned int hash_first_letter_freq(const char *word)
{
    char f = word[0];

    if (f == 'a' || f == 'g')
        return 0;
    else if (f == 'c')
        return 1;
    else if (f == 'f' || f == 'i' || f == 'j' || f == 'q')
        return 2;
    else if (f == 'b' || f == 'k' || f == 'w')
        return 3;
    else if (f == 'l' || f == 'm')
        return 4;
    else if (f == 'd' | f == 'n')
        return 5;
    else if (f == 'p')
        return 6;
    else if (f == 'o' || f == 'r' || f == 'x' || f == 'y' || f == 'z')
        return 7;
    else if (f == 's')
        return 8;
    else if (f == 'v' || f == 'u' || f == 'h')
        return 9;

    return 10;
}

// Frequency of vowels in a word (4 buckets):
// 2/7 (34,342), 3 (39,826), 1/5/6 (34,693), 4/8+ (34,231)
static unsigned int hash_vowel_freq(const char *word)
{
    int v = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
            v++;
    }

    return (v == 2 | v == 7) ? 0 : (v == 3) ? 1 : (v == 1 || v == 5 || v == 6) ? 2 : 3;
}

// Word length with at least 10 words matching that length, plus one bucket for all others (14
// buckets): 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1 & 2 & 17+
// Warning - Results in unbalanced buckets
static unsigned int hash_word_len(const char *word)
{
    int len = strlen(word);

    return (len >= 4 && len <= 16) ? len - 4 : WORD_LEN_BUCK_SIZE - 1;
}

// Buckets used in sum of chars hash function
static void fill_rbucket_lettersums(rbucket *sb)
{
    // Populate the buckets directly
    sb[0] = (rbucket) {1, 42};
    sb[1] = (rbucket) {43, 51};
    sb[2] = (rbucket) {52, 57};
    sb[3] = (rbucket) {58, 62};
    sb[4] = (rbucket) {63, 66};
    sb[5] = (rbucket) {67, 70};
    sb[6] = (rbucket) {71, 73};
    sb[7] = (rbucket) {74, 76};
    sb[8] = (rbucket) {77, 79};
    sb[9] = (rbucket) {80, 82};
    sb[10] = (rbucket) {83, 85};
    sb[11] = (rbucket) {86, 88};
    sb[12] = (rbucket) {89, 91};
    sb[13] = (rbucket) {92, 94};
    sb[14] = (rbucket) {95, 97};
    sb[15] = (rbucket) {98, 100};
    sb[16] = (rbucket) {101, 103};
    sb[17] = (rbucket) {104, 106};
    sb[18] = (rbucket) {107, 109};
    sb[19] = (rbucket) {110, 112};
    sb[20] = (rbucket) {113, 115};
    sb[21] = (rbucket) {116, 118};
    sb[22] = (rbucket) {119, 122};
    sb[23] = (rbucket) {123, 126};
    sb[24] = (rbucket) {127, 130};
    sb[25] = (rbucket) {131, 134};
    sb[26] = (rbucket) {135, 139};
    sb[27] = (rbucket) {140, 145};
    sb[28] = (rbucket) {146, 151};
    sb[29] = (rbucket) {152, 158};
    sb[30] = (rbucket) {159, 167};
    sb[31] = (rbucket) {168, 179};
    sb[32] = (rbucket) {180, 198};
    sb[33] = (rbucket) {199, htINT_MAX}; // Use htINT_MAX for open-ended max
}

// Binary search for n in an array of range buckets
static int search_rbucket(int n, rbucket sb[], int start, int size)
{
    int mid = start + ceil((float) (size - start) / 2.0);

    if (n >= sb[mid].min && n <= sb[mid].max)
        return mid;

    if (start >= size)
        return -1;

    else if (n > sb[mid].max)
        return search_rbucket(n, sb, mid + 1, size);
    else if (n < sb[mid].min)
        return search_rbucket(n, sb, start, mid - 1);

    return -1;
}
