#include <stdlib.h>
#include <stdio.h>

typedef enum Player
{
  FIRST_PLAYER = 1,
  SECOND_PLAYER = 2,
  NO_SELECTED = 0
} Player;

enum GameStates
{
  GAME_STATE_WIN = 1,
  GAME_STATE_TIE = -1,
  GAME_STATE_RUNNING = 0
};

int table[] = {
    NO_SELECTED, NO_SELECTED, NO_SELECTED, //
    NO_SELECTED, NO_SELECTED, NO_SELECTED, //
    NO_SELECTED, NO_SELECTED, NO_SELECTED, //
};

void clean_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

char render_pos(int position);
void getPosition(int player);
int check_winner(int player);
int wanna_keep_playing();
void new_lines(int n);
void render_table();

int main()
{
  Player player = FIRST_PLAYER;
  do
  {
    const char player_letter = player == FIRST_PLAYER ? 'X' : 'O';
    render_table();
    printf("[%c] turn, chose your position: ", player_letter);
    getPosition(player);

    printf("game[%d] ======== player[%d]\n", check_winner(player), player);

    if (check_winner(player) == GAME_STATE_WIN)
    {
      printf("PLAYER [%c] WON!!!!! CONGRATS PLAYER [%c]!", player_letter, player_letter);
      new_lines(2);
      if (!wanna_keep_playing())
      {
        break;
      }
    }
    else if (check_winner(player) == GAME_STATE_TIE)
    {
      printf("HO NO, LOOKS LIKE WE HAVE NO WINNER :/");
      new_lines(2);
      if (!wanna_keep_playing())
      {
        break;
      }
    }

    player = player == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;

  } while (1);

  return 0;
}

void getPosition(int player)
{
  int position;

  scanf("%d", &position);
  if (position < 0 && position > 8)
  {
    new_lines(1);
    printf("invalid position! try again\n");
    return getPosition(player);
  }

  if (table[position] != NO_SELECTED)
  {
    new_lines(1);
    printf("position already taken! try again\n");
    return getPosition(player);
  }

  table[position] = player;
  return;
}

char render_pos(int position)
{
  if (table[position] == FIRST_PLAYER)
  {
    return 'X';
  }
  if (table[position] == SECOND_PLAYER)
  {
    return 'O';
  }

  return position + '0'; // casting to char
}

void render_table()
{
  system("cls || clear");

  printf("   .   .    \n");
  printf("_%c_|_%c_|_%c_\n", render_pos(0), render_pos(1), render_pos(2));
  printf("_%c_|_%c_|_%c_\n", render_pos(3), render_pos(4), render_pos(5));
  printf(" %c | %c | %c  \n", render_pos(6), render_pos(7), render_pos(8));
  printf("   '   '    \n\n");
}

int check_winner(int player)
{
  int *t = table;

  // rows
  for (short int i = 0; i <= 6; i = i + 3)
  {
    if (t[i] == player && t[i + 1] == player && t[i + 2] == player)
    {
      return GAME_STATE_WIN;
    }
  }

  // columns
  for (short int i = 0; i < 3; i++)
  {
    if (t[i] == player && t[i + 3] == player && t[i + 6] == player)
    {
      return GAME_STATE_WIN;
    }
  }

  // diagonal
  if (t[0] == player && t[4] == player && t[8] == player || t[2] == player && t[4] == player && t[6] == player)
  {
    return GAME_STATE_WIN;
  }

  // tie
  for (short int i = 0; i < 9; i++)
  {
    if (t[i] == NO_SELECTED)
    {
      break;
    }
    if (i == 8)
    {
      return GAME_STATE_TIE;
    }
  }

  return GAME_STATE_RUNNING;
}

int wanna_keep_playing()
{
  char option;
  do
  {
    printf("Wanna play again?\n");
    printf("1 - Yes\n");
    printf("2 - No\n");
    clean_stdin();
    scanf("%c", &option);
  } while (option != '1' && option != '2');

  if (option == '1')
  {
    for (short int i = 0; i < 9; i++)
    {
      table[i] = NO_SELECTED;
    }

    return 1;
  }

  printf("\nGG, Have a nice day you both :D\n");
  return 0;
}

void new_lines(int n)
{
  for (int i = 0; i < n; i++)
    printf("\n");
}