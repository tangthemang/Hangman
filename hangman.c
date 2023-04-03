#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "words.h"
#include "hangman-io.h"

int main(void) {
    char playing = 'Y';

    while (playing == 'Y') {
        int N = 0;
        int valid = 0;
        while (!valid) {
            printf(enter_game_number, max_words);
            if (scanf("%d", &N)) {
                if ((N >= 1) && (N <= max_words)) {
                    valid = 1;
                }
                else {
                    printf("%s", invalid_game_number);
                }
            }
        }

        const char *word = get_word(N);
        int length = strlen(word);
        char guess[50] = {'*'};
        int blanks = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == ' ') {
                guess[i] = ' ';
            }
            else {
                guess[i] = '*';
                blanks++;
            }
        }
        int guessed[10000] = {0};
        int strikes = 0;
        int won = 0;

        while (!won && (strikes < max_strikes)) {
            print_hangman(strikes);
            printf("%s", letter_prompt);
            for (int i = 0; i < length; i++) {
                printf("%c", guess[i]);
            }            

            printf("\n");

            char letter = ' ';
            int scanned = 0;

            while (!scanned) {
                if (scanf("%c", &letter) && letter != '\n') {
                    scanned = 1;
                }
            }

            if (isalpha(letter)) {
                letter = toupper(letter);
                if (!guessed[(int)(letter)]) {
                    guessed[(int)(letter)] = 1;
                    int correct = 0;
                    for (int i = 0; i < length; i++) {
                        if (word[i] == letter) {
                            guess[i] = letter;
                            correct = 1;
                            blanks--;
                        }
                    }
                    if (!correct) {
                        strikes++;
                        printf(not_in_word, letter);

                        if (strikes < max_strikes) {
                            printf(not_last_guess, 6-strikes);
                        }
                    }
                    else {
                        if (blanks == 0) {
                            won = 1;
                        }
                    }
                }

                else{
                    printf(already_guessed_letter, letter);
                }
            }

            else if (letter == '\n') {
                break;
            }
            
            else {
                printf(not_a_letter, letter);
            }
            
        }

        if (won) {
            printf(congratulations, word);
        }

        else {
            print_hangman(strikes);
            printf(game_over, word);
        }

        int scanned = 0;
        
        while (!scanned) {
            if (playing != '\n') {
                printf("%s", play_again);
            }

            if (scanf("%c", &playing)) {
                if ((playing != 'Y') && (playing != 'N') && (playing != 'y') && (playing != 'n') && (playing != '\n')) {
                    printf("%s", invalid_play_again_response);
                }
                else if (playing != '\n') {
                    playing = toupper(playing);
                    scanned = 1;
                }
            }
        
            else {
                printf("%s", invalid_play_again_response);
            }
        }

    }

}
