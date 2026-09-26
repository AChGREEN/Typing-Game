#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_INPUT_LEN 256
#define HIGH_SCORE_FILE "highscore.txt"

// ansi colors for the diff at the end
#define COLOR_GREEN "\033[32m"
#define COLOR_RED   "\033[31m"
#define COLOR_RESET "\033[0m"

// sentence banks, may do like random words but I did this for now
const char *easy_sentences[] = {
    "the cat sat on the mat",
    "i like to eat pizza",
    "she sells sea shells",
    "the sky is very blue today"
};

const char *medium_sentences[] = {
    "the quick brown fox jumps over the lazy dog",
    "practice makes perfect if you keep trying every day",
    "typing fast is a skill that improves with regular practice",
    "the weather changed quickly from sunny to stormy this afternoon"
};

const char *hard_sentences[] = {
    "the biggest difference between good and great programmers is attention to detail",
    "consistency and patience will get you further than raw talent ever could alone",
    "she whispered nervously as the old wooden floorboards creaked beneath her feet",
    "artificial intelligence has changed the way people write, research, and communicate daily"
};

#ifdef _WIN32
double get_time_ms(void) {
    static LARGE_INTEGER freq;
    static int freq_set = 0;
    LARGE_INTEGER now;

    if (!freq_set) {
        QueryPerformanceFrequency(&freq);
        freq_set = 1;
    }

    QueryPerformanceCounter(&now);
    return (double)now.QuadPart * 1000.0 / (double)freq.QuadPart;
}
#else
double get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000.0) + (ts.tv_nsec / 1000000.0);
}
#endif

// fgets leaves the newline on there, gotta chop it off
void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

const char *pick_sentence(int difficulty) {
    int idx;

    if (difficulty == 1) {
        idx = rand() % (sizeof(easy_sentences) / sizeof(easy_sentences[0]));
        return easy_sentences[idx];
    } else if (difficulty == 2) {
        idx = rand() % (sizeof(medium_sentences) / sizeof(medium_sentences[0]));
        return medium_sentences[idx];
    } else {
        idx = rand() % (sizeof(hard_sentences) / sizeof(hard_sentences[0]));
        return hard_sentences[idx];
    }
}

// prints the sentence back with red/green per character so you can see exactly where you messed up. probably the part i'm most happy with tbh
void print_diff(const char *original, const char *typed) {
    int orig_len = strlen(original);
    int typed_len = strlen(typed);
    int max_len = orig_len > typed_len ? orig_len : typed_len;

    printf("\nHere's how you did, character by character:\n");

    for (int i = 0; i < max_len; i++) {
        char o = (i < orig_len) ? original[i] : '\0';
        char t = (i < typed_len) ? typed[i] : '\0';

        if (t == '\0') {
            printf("%s_%s", COLOR_RED, COLOR_RESET); // didn't even get this far
        } else if (o == t) {
            printf("%s%c%s", COLOR_GREEN, t, COLOR_RESET);
        } else {
            printf("%s%c%s", COLOR_RED, t, COLOR_RESET);
        }
    }
    printf("\n");
}

double calculate_accuracy(const char *original, const char *typed) {
    int orig_len = strlen(original);
    int correct = 0;

    if (orig_len == 0)
        return 0.0;

    for (int i = 0; i < orig_len; i++) {
        if (typed[i] != '\0' && typed[i] == original[i])
            correct++;
    }

    return (correct / (double)orig_len) * 100.0;
}

double load_high_score(void) {
    FILE *fp = fopen(HIGH_SCORE_FILE, "r");
    double score = 0.0;

    if (fp == NULL)
        return 0.0; // no file yet, first time running probably

    if (fscanf(fp, "%lf", &score) != 1)
        score = 0.0;

    fclose(fp);
    return score;
}

void save_high_score(double score) {
    FILE *fp = fopen(HIGH_SCORE_FILE, "w");

    if (fp == NULL) {
        printf("(eh, couldn't save the high score, oh well)\n");
        return;
    }

    fprintf(fp, "%.2f\n", score);
    fclose(fp);
}

int choose_difficulty(void) {
    char input[10];
    printf("Choose a difficulty:\n");
    printf("  1) Easy\n");
    printf("  2) Medium\n");
    printf("  3) Hard\n");
    printf("Enter 1, 2, or 3: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 2;

    int choice = atoi(input);
    if (choice < 1 || choice > 3) {
        printf("didn't catch that, defaulting to medium\n");
        return 2;
    }

    return choice;
}

void play_round(double *high_score) {
    char typed[MAX_INPUT_LEN];
    double start_time, end_time, elapsed_seconds, elapsed_minutes;
    double wpm, accuracy;

    int difficulty = choose_difficulty();
    const char *sentence = pick_sentence(difficulty);

    printf("\nType this sentence exactly as shown, then press Enter:\n\n");
    printf("  %s\n\n", sentence);
    printf("Press Enter when you're ready to start...");
    
    // Safely clear the input buffer until a newline is reached
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    start_time = get_time_ms();

    printf("GO: ");
    fflush(stdout); // <--- CRITICAL: Forces "GO: " to appear on the screen immediately

    if (fgets(typed, sizeof(typed), stdin) == NULL) {
        printf("didn't catch that, try again next round\n");
        return;
    }

    end_time = get_time_ms();
    strip_newline(typed);

    elapsed_seconds = (end_time - start_time) / 1000.0;
    
    if (elapsed_seconds <= 0) {
        elapsed_seconds = 0.001; 
    }

    elapsed_minutes = elapsed_seconds / 60.0;

    int word_count = strlen(sentence) / 5;
    wpm = word_count / elapsed_minutes;
    accuracy = calculate_accuracy(sentence, typed);

    print_diff(sentence, typed);
    printf("\n---- Results ----\n");
    printf("Time taken : %.2f seconds\n", elapsed_seconds);
    printf("Speed      : %.1f WPM\n", wpm);
    printf("Accuracy   : %.1f%%\n", accuracy);

    if (wpm > *high_score) {
        printf("\nnew high score, nice\n");
        *high_score = wpm;
        save_high_score(wpm);
    } else {
        printf("High score : %.1f WPM\n", *high_score);
    }
}

int main(void) {
    char again[10];

    srand((unsigned int)time(NULL));
    double high_score = load_high_score();

    printf("=====================================\n");
    printf("         TYPING SPEED TEST\n");
    printf("=====================================\n");

    if (high_score > 0)
        printf("Current high score: %.1f WPM\n", high_score);

    do {
        play_round(&high_score);

        printf("\nGo again? (y/n): ");
        if (fgets(again, sizeof(again), stdin) == NULL)
            break;
    } while (tolower(again[0]) == 'y');

    printf("\nThanks for playing! Final high score: %.1f WPM\n", high_score);
    return 0;
}