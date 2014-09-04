#include "cell.h"

#define TEST_CELL

#include <cstring>
#include <iostream>

using namespace std;

const int MAX_POOL = 1000;
Cell pair_pool[MAX_POOL];
Cell cell_pool[MAX_POOL];

int free_pair_index;
int free_cell_index;

Cell invalid_cell;
Cell null_cell;

Cell *get_pair()
{
  if (free_pair_index >= MAX_POOL) return 0;
  Cell *c = &pair_pool[free_pair_index++];
  c->type_ = PAIR;
  c->pair_attr_ = HEAD;
  return c;
}

Cell *get_cell(const char *val, CellType type)
{
  if (free_cell_index >= MAX_POOL) return 0;

  Cell *c = &cell_pool[free_cell_index++];
  c->type_ = type;
  strcpy(c->val_, val);
  c->first_ = 0;
  c->second_ = 0;
  return c;
}

void print_cell(const Cell *cell)
{
  if (cell->type() == PAIR)
  {
    if (cell->pair_attr_ == HEAD)
      cout << "( "; 
    print_cell(cell->first_);
    print_cell(cell->second_);
  }
  else
  {
    if (cell->type() != NULL_CELL)
      cout << cell->val_ << " , ";
    else
      cout << " () )" << endl;
  }
}

#ifdef TEST_CELL
int main(int argc, char *argv[])
{
  invalid_cell.type_ = INVALID;
  null_cell.type_ = NULL_CELL;
  // (+ 1 2), append null_cell
  Cell *c = get_cell("+", SYMBOL);
  Cell *pair = get_pair();
  Cell *head;
  Cell *iter_cell;

  head = iter_cell = pair;

  pair->first_ = c;
  pair->second_ = &null_cell;

  c = get_cell("1", NUMBER);
  pair = get_pair();

  pair->first_ = c;
  pair->second_ = &null_cell;

  pair->pair_attr_ = SECOND;
  iter_cell->second_ = pair;
  iter_cell = pair;

  c = get_cell("2", NUMBER);
  pair = get_pair();

  pair->first_ = c;
  pair->second_ = &null_cell;

  pair->pair_attr_ = SECOND;
  iter_cell->second_ = pair;
  iter_cell = pair;

  print_cell(head);

  return 0;
}
#endif
