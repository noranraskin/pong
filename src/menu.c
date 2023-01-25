//
// Created by Noran Raskin on 23.01.23.
//

#include "menu.h"
#include "game.h"
#include <string.h>
#include <curses.h> // ncurses library

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

void menu() {

    initscr(); // initialize ncurses
    cbreak();  // disable buffering of typed characters
    noecho();  // don't echo typed characters
    keypad(stdscr, TRUE);  // enable arrow keys

    // Show the menu
    int highlight = 0;
    int choice;
    GameMode gameMode = NORMAL;
    int chosenResolution = 1;
    const char* options[] = {"Gamemode: %s", "Resolution: %s", "Start Game", "Exit"};
    const char* gameModes[] = {"PVP   ", "Normal", "Hard  "};
    const char* resolutions[] = {" 640 x 480 ", " 800 x 600 ", "1200 x 900 ", "1400 x 1050"};
    const double resFactors[] = {0.8, 1.0, 1.5, 1.75};
    int n_options = sizeof(options) / sizeof(options[0]);

    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    while(1) {
        attron(A_UNDERLINE | A_BLINK);
        mvprintw(terminalHeight / 2 - n_options, terminalWidth / 2 - strlen("Pong") /2, "Pong");
        attroff(A_UNDERLINE | A_BLINK);
        for (int i = 0; i < n_options; i++) {
            if (i == highlight)
                attron(A_STANDOUT);
            if (i == 0) {
                mvprintw(terminalHeight / 2 - n_options / 2 + i, terminalWidth / 2 - (strlen(options[i])+5) / 2, options[i], gameModes[gameMode]);
            } else if (i == 1) {
                mvprintw(terminalHeight / 2 - n_options / 2 + i, terminalWidth / 2 - (strlen(options[i]) + 8) / 2, options[i], resolutions[chosenResolution]);
            } else if (i == 2) {
                attron(A_BOLD);
                mvprintw(terminalHeight / 2 - n_options / 2 + i + 1, terminalWidth / 2 - strlen(options[i]) / 2, options[i]);
                attroff(A_BOLD);
            } else {
                attron(A_DIM);
                mvprintw(terminalHeight / 2 - n_options / 2 + i + 3, terminalWidth / 2 - strlen(options[i]) / 2, options[i]);
                attroff(A_DIM);
            }
            attroff(A_STANDOUT);
        }
        choice = getch();

        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == n_options)
                    highlight = n_options - 1;
                break;
            case KEY_LEFT:
                if (highlight == 0) {
                    if (gameMode > 0) {
                        gameMode--;
                    }
                }
                if (highlight == 1) {
                    if (chosenResolution > 0) {
                        chosenResolution--;
                        scale_factor = resFactors[chosenResolution];
                    }
                }
                break;
            case KEY_RIGHT:
                if (highlight == 0) {
                    if (gameMode < 2) {
                        gameMode++;
                    }
                }
                if (highlight == 1) {
                    if (chosenResolution < 3) {
                        chosenResolution++;
                        scale_factor = resFactors[chosenResolution];
                    }
                }
                break;
            case KEY_ENTER:
            case ' ':
                if (highlight == 2) {
                    game(gameMode, 5);
                    break;
                }
                else if (highlight == 3){
                    endwin();
                    return;
                }
                break;
            default:
                break;
        }
    }
 }

