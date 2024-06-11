#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
void shuffle(vector<vector<int>>& puzzle, int size) {
  vector<int> temp;
  for (int i = 0; i < size * size; ++i) {
    temp.push_back(i + 1);
  }
  temp[size * size - 1] = 0; // Пустая клетка
  srand((unsigned)time(0));
  random_shuffle(temp.begin(), temp.end());
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      puzzle[i][j] = temp[i * size + j];
    }
  }
}
void display(const vector<vector<int>>& puzzle, int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << "+";
    for (int j = 0; j < size; j++)
    {
      cout << "===+";
    }
    cout << "\n";
    cout << "|";
    for (int j = 0; j < size; j++)
    {
      if (puzzle[i][j] == 0)
      {
        cout << "  |";
      }
      else {
        cout  << puzzle[i][j] << " |";
      }
    }
    cout << "\n";
  }
  cout << "+";
  for (int j = 0; j < size; j++)
  {
    cout << "===+";
  }
  cout << "\n";

}
bool move(vector<vector<int>>& puzzle, int size, int direction) {
  int zrow, zcol;
  // Найти пустую клетку
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (puzzle[i][j] == 0) {
        zrow = i;
        zcol = j;
        break;
      }
    }
  }
  // управление
  int new_row = zrow;
  int new_col = zcol;
  if (direction == 0)//вниз
  {
    new_row = zrow - 1;
  }
  else if (direction == 1)//вверх
  {
    new_row = zrow + 1;
  }
  else if (direction == 2)//влево
  {
    new_col = zcol + 1;
  }
  else if (direction == 3)//вправо
  {
    new_col = zcol - 1;
  }

  if (new_row < 0 || new_row >= size || new_col < 0 || new_col >= size)// проверка границ поля 
  {
    return false;
  }

  swap(puzzle[zrow][zcol], puzzle[new_row][new_col]);
  return true;

  swap(puzzle[zrow][zcol], puzzle[new_row][new_col]);
  return true;
}
bool is_solved(const vector<vector<int>>& puzzle, int size) {
  int count = 1;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (puzzle[i][j] != count % (size * size)) {
        return false;
      }
      count++;
    }
  }
  return true;
}
int main() {
  setlocale(LC_ALL , "Russian");
  int size_choice;
  cout << "Выберите размер игры: 1) 8 (3x3) 2) 15 (4x4): ";
  cin >> size_choice;
  int size = (size_choice == 1) ? 3 : 4;
  vector<vector<int>> puzzle(size, vector<int>(size));
  // Инициализация поля
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      puzzle[i][j] = i * size + j + 1;
    }
  }
  puzzle[size - 1][size - 1] = 0; // Пустая клетка
  int method;
  cout << "Выберите метод создания пазла: 1) Вручную 2) Перемешать: ";
  cin >> method;
  if (method == 2) {
    shuffle(puzzle, size);
  }
  display(puzzle, size);
  int moves = 0;
  while (!is_solved(puzzle, size)) {
    int direction;
    cout << "Сделайте ход (1: Вверх, 0: Вниз, 2: Влево, 3: Вправо): ";
    cin >> direction;
    if (move(puzzle, size, direction)) {
      moves++;
      display(puzzle, size);
    }
    else {
      cout << "Невозможно сделать этот ход!" << endl;
    }
  }
  cout << "Пазл решен за " << moves << " ходов!" << endl;
  return 0;
}