#include "cell.h"

//#define TEST_CELL

const char *cell_type_string[] = {"STRING", "SYMBOL", "NUMBER", "PAIR", "PRIMITIVE_PROC", "LAMBDA_PROC", "NULL_CELL", "INVALID"};

const char* Cell::type_str() const 
{
  return cell_type_string[type()];
}

const int MAX_POOL = 1000;
Cell pair_pool[MAX_POOL];
Cell cell_pool[MAX_POOL];

int free_pair_index;
int free_cell_index;

#if 0
Cell invalid_cell;
Cell null_cell;
#endif

Cell *get_pair()
{
  if (free_pair_index >= MAX_POOL) return 0;
  Cell *c = &pair_pool[free_pair_index++];
  c->type_ = PAIR;
  c->pair_attr_ = HEAD;
  c->first_ = 0;
  c->second_ = 0;
  return c;
}

Cell *get_cell(const char *val, ProcType proc)
{
  if (free_cell_index >= MAX_POOL) return 0;

  Cell *c = &cell_pool[free_cell_index++];
  c->proc_ = proc;
  c->type_ = PRIMITIVE_PROC;
  strcpy(c->val_, val);
  c->first_ = 0;
  c->second_ = 0;
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
  if (cell == 0)
  {
    cout << "null ptr" << endl;
    return;
  }
  if (cell->type() == PAIR)
  {
    if (cell->pair_attr_ == FIRST || cell->pair_attr_ == HEAD)
      cout << "( "; 
    print_cell(cell->first_);
    print_cell(cell->second_);
  }
  else
  {
    if (cell->type() != NULL_CELL)
      cout << cell->val_ << " , ";
    else
      cout << " () ) ";
  }
}

const int MAX_LINE_LEN = 1000;

#define LEN_TOO_SHORT -1
#define OK 0

int add_space_to_parenthesis(const char *org_str, char *new_str, int new_str_size)
{
  const char *c = org_str;
  int i=0;

  while (*c)
  {
    if (*c == '(' || *c == ')')
    {
      if (i+3 > new_str_size)
        return LEN_TOO_SHORT;
      new_str[i++] = ' ';
      new_str[i++] = *c;
      new_str[i++] = ' ';
    }
    else
    {
      if (i+1 > new_str_size)
        return LEN_TOO_SHORT;
      new_str[i++] = *c;
    }
    ++c;
  }
  new_str[i] = '\0';
  
  return OK;
}

#if 0
Cell *create_expression(const char *exp)
{
  char val[MAX_SIZE]; 
  const char *c = exp;
  int i=0;
  Cell *head;
  Cell *prev_pair;
  Cell *cell;
  Cell *pair;

  while(*c)
  {
    while (*c == ' ') // skip blank
      ++c;
    if (*c == '(')
    {
      pair = get_pair();
      pair->pair_attr_ = HEAD;
      head = prev_pair = pair;

      ++c;
      while (*c == ' ') // skip blank
        ++c;
    }


    while (*c != ' ' && *c != '(' && *c != ')')
      val[i++] = *c++;
    val[i] = '\0';
    cout << val << endl;

    cell = get_cell(val, SYMBOL);

    pair->first_ = cell;
    pair->second_ = &null_cell;


    if (prev_pair != pair)
    {
      cout << "add to prev_pair" << endl;

      pair->pair_attr_ = SECOND;
      prev_pair->second_ = pair;
      prev_pair = pair;
    }
    pair = get_pair();

    i=0;
    if (*c == ')')
    {
      cout << ")))" << endl;
      return head;
    }
    ++c;
  }
  return head;
}
#endif

Cell *car_cell(Cell *cell)
{
  if (cell->type_ != PAIR)
  {
    strcpy(invalid_cell.val_, "not pair");
    return &invalid_cell;
  }
  else
    return cell->first_; // first_ should not be 0.
}

Cell *cdr_cell(Cell *cell)
{
  if (cell->type_ != PAIR)
  {
    strcpy(invalid_cell.val_, "not pair");
    return &invalid_cell;
  }
  else
    return cell->second_; // second_ should not be 0.
}

Cell *cons_cell(Cell *first, Cell *second)
{
  Cell *pair = get_pair();
  pair->first_ = first; 
  pair->second_ = second;
  if (first->type_ == PAIR)
    first->pair_attr_ = FIRST;
  if (second->type_ == PAIR)
    second->pair_attr_ = SECOND;

  return pair; // PairAttr not set.
}

Cell *make_exp(const char *exp_str)
{
#if 0
  Cell *cell_ptr_pool[MAX_POOL];
  char val[MAX_SIZE]; 
  int i=0;

  char *s = exp_str;

  while (*s == ' ') // skip blank
    ++s;

  if (*s == '(')
  {
    while (*s != ')')
    {
      if (*s == '(')
        make_exp(*s);

    ++s;
    while (*s == ' ') // skip blank
      ++s;

    while (*s != ' ' && *s != '(' && *s != ')')
      val[i++] = *c++;
    val[i] = 0;

    cell_ptr_pool[i++] = get_cell(val, SYMBOL);
      
    }
     
  }
  else
  {
  }
#endif
}

Cell *make_exp()
{
  Cell *cell = get_cell("5", SYMBOL);
  Cell *new_cell = cons_cell(cell, &null_cell);
  new_cell->pair_attr_ = HEAD;

  cell = get_cell("3", SYMBOL);
  Cell *c1 = cons_cell(cell, new_cell);

  cell = get_cell("*", SYMBOL);
  Cell *c2 = cons_cell(cell, c1);

  return c2;
}

Cell *make_list(vector<Cell *> cells)
{
  Cell *c;
  c = cons_cell(cells[cells.size()-1], &null_cell); 

  for (int i = cells.size()-2 ; i>=0 ; --i)
  {
    c = cons_cell(cells[i], c);
  }
  return c;
}

//Cell *read_from(const char *tokens[])


#ifdef TEST_CELL
int main(int argc, char *argv[])
{
  char input_str[MAX_LINE_LEN];
  char for_split[MAX_LINE_LEN]; // appned ' ' for ( or ): ex "(" => " ( ", ")" => " ) "
  invalid_cell.type_ = INVALID;
  null_cell.type_ = NULL_CELL;

#if 1
  std::list<std::string> tokens;
  tokens.push_back("(");
  tokens.push_back("+");
  tokens.push_back("(");
  tokens.push_back("*");
  tokens.push_back("3");
  tokens.push_back("5");
  tokens.push_back(")");
  tokens.push_back("2");
  tokens.push_back(")");
#else
  const char *tokens[MAX_POOL];
  tokens[0] = "(";
  tokens[1] = "+";
  tokens[2] = "(";
  tokens[3] = "*";
  tokens[4] = "3";
  tokens[5] = "5";
  tokens[6] = ")";
  tokens[7] = "2";
  tokens[8] = ")";
  tokens[9] = 0;

  cout << tokens[0] << endl;
  cout << tokens[1] << endl;
  //cout << *tokens << endl;
#endif

  Cell *exp = read_from(tokens);
#if 1
  cout << "\n-----" << endl;
  print_cell(exp);
  cout << "\n-----" << endl;
#endif

#if 0
  Cell *exp = make_exp();
  print_cell(exp);

  Cell *cell = get_cell("2", SYMBOL);
  Cell *new_cell = cons_cell(cell, &null_cell);
  new_cell->pair_attr_ = HEAD;

  print_cell(new_cell);

  cell = get_cell("1", SYMBOL);
  Cell *c1 = cons_cell(exp, new_cell);
  cout << "\n-----" << endl;
  print_cell(c1);
  cout << "\n-----" << endl;

  cell = get_cell("+", SYMBOL);
  Cell *c2 = cons_cell(cell, c1);
  cout << "\n-----" << endl;
  print_cell(c2);
  cout << "\n-----" << endl;
#endif

#if 0
  strcpy(input_str, "(+ 123 789)");

  Cell *head = create_expression(input_str);
  cout << "free_pair_index: " << free_pair_index << endl;
  cout << "free_cell_index: " << free_cell_index << endl;
  print_cell(head);
  cout << endl;

  //strcpy(input_str, "(+ (* 6 7) 2)");
  int r = add_space_to_parenthesis(input_str, for_split, MAX_LINE_LEN);
  cout << input_str << endl;
  if (r==OK)
    cout << for_split << endl;
  else
    cout << r << endl;

#endif
#if 0
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
#endif
  return 0;
}
#endif
