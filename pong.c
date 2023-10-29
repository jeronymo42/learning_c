#include <math.h>
#include <stdio.h>

int command();
void field();

int main() {
    int racket1_y = 12;
    int racket2_y = 12;
    int ball_x = 40;
    int ball_y = 12;
    int score_player1 = 0;
    int score_player2 = 0;
    int ball_x_speed = 4;
    int ball_y_speed = 0;
    while (score_player1 != 21 || score_player2 != 21) {
        field(ball_x, ball_y, racket1_y, racket2_y);
        printf("                                     %d - %d  \n", score_player1, score_player2);
        printf("x: %d, y: %d", ball_x, ball_y);

        printf("Player #1");
        int player_1_step = command(1);
        if ((racket1_y + player_1_step - 1) > 0 && (racket1_y + player_1_step + 1) < 25) {
            racket1_y += player_1_step;
        }
        field(ball_x, ball_y, racket1_y, racket2_y);
        printf("                                     %d - %d  \n", score_player1, score_player2);

        printf("Player #2");
        int player_2_step = command(2);
        if ((racket2_y + player_2_step - 1) > 0 && (racket2_y + player_2_step + 1) < 25) {
            racket2_y += player_2_step;
        }

        if ((ball_x + ball_x_speed >= 80) && (ball_y >= racket2_y + 2 || ball_y <= racket2_y - 2)) {
            score_player1 += 1;
            ball_y = racket2_y;
            ball_x = 79;
            ball_x_speed = -ball_x_speed;
            ball_y_speed = 0;
        } else if ((ball_x + ball_x_speed <= 0) && (ball_y >= racket1_y + 2 || ball_y <= racket1_y - 2)) {
            score_player2 += 1;
            ball_y = racket1_y;
            ball_x = 1;
            ball_x_speed = -ball_x_speed;
            ball_y_speed = 0;
        } else if (ball_x + ball_x_speed >= 0 && ball_x + ball_x_speed <= 80) {
            ball_x += ball_x_speed;
            if (ball_y + ball_y_speed <= 0) {
                ball_y = 1;
                ball_y_speed = -ball_y_speed;
            }
            if (ball_y + ball_y_speed >= 25) {
                ball_y = 24;
                ball_y_speed = -ball_y_speed;
            } else {
                ball_y += ball_y_speed;
            }
        } else {
            if (ball_x + ball_x_speed <= 0) {
                ball_x = 1;
                if (ball_y == racket1_y - 1) {
                    ball_y_speed = -2;
                } else if (ball_y == racket1_y + 1) {
                    ball_y_speed = 2;
                } else {
                    ball_y_speed = 0;
                }
            }
            if (ball_x + ball_x_speed >= 80) {
                ball_x = 79;
                if (ball_y == racket2_y - 1) {
                    ball_y_speed = -2;
                } else if (ball_y == racket2_y + 1) {
                    ball_y_speed = 2;
                } else {
                    ball_y_speed = 0;
                }
            }
            ball_x_speed = -ball_x_speed;
        }
    }
    return 0;
}

int command(int x) {
    char input_com;
    while (1) {
        if (scanf("%c", &input_com) == 1) {
            if (x == 1) {
                if (input_com == 'A' || input_com == 'a') {
                    return -1;
                } else if (input_com == 'Z' || input_com == 'z') {
                    return 1;
                } else if (input_com == ' ') {
                    return 0;
                } else {
                    continue;
                }
            } else {
                if (input_com == 'K' || input_com == 'k') {
                    return -1;
                } else if (input_com == 'M' || input_com == 'm') {
                    return 1;
                } else if (input_com == ' ') {
                    return 0;
                } else {
                    continue;
                }
            }
        }
    }
}

void field(int ball_x, int ball_y, int racket1_y, int racket2_y) {
    int height = 25;
    int width = 80;
    printf("\e[1;1H\e[2J");
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            if (i == 0 || i == height) {
                printf("=");
            } else if ((j == 0 && (i >= racket1_y - 1 && i <= racket1_y + 1)) ||
                       (j == width && (i >= racket2_y - 1 && i <= racket2_y + 1))) {
                printf("|");
            } else {
                if (i == ball_y && j == ball_x) {
                    printf("o");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}
