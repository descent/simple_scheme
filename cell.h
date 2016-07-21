#ifndef CELL_H
#define CELL_H

#include "x86_16.h"

#include "mytype.h"

#ifdef OS_CPP
#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#define myprint printf
using namespace std;
#else
#include "myiostream.h"
#include "k_string.h"
#include "k_stdio.h"
#define strcpy s_strcpy
using namespace DS;
#endif


#define MM_STATUS

#ifdef X86_16
const int MAX_POOL = 48;
#else
const int MAX_POOL = 512;
#endif

extern int free_pair_index;
extern int free_cell_index;
extern int previous_free_pair_index;
extern int previous_free_cell_index;

enum PairAttr {HEAD, FIRST, SECOND};
enum CellType {STRING, SYMBOL, NUMBER, PAIR, PRIMITIVE_PROC, NULL_CELL, TIMER, INVALID};

struct Environment;

struct Cell;
typedef Cell *(*ProcType)(Cell *);

const int MAX_SIZE = 10;
// a variant that can hold any kind of lisp value
struct Cell 
{

#if 0
    Cell(cell_type type = Symbol) 
      : type(type), env_(0), proc_kind_(NORMAL_CELL)
    {}

    Cell(cell_type type, const std::string & val)
      : type(type), val(val), env_(0), proc_kind_(NORMAL_CELL)
    {}

    Cell(ProcType proc, const std::string proc_name) 
      :type(Proc), proc_(proc), val(proc_name), env_(0), proc_kind_(PRIMITIVE)
    {}
#endif
    bool is_null() 
    {
      if (type() == NULL_CELL)
        return true;
      else
        return false;
    }

    CellType type() const {return type_;}
    //ProcKind proc_kind() const {return proc_kind_;}

    const char* type_str() const;

    //ProcKind proc_kind_; // if type is Proc need check it.
    CellType type_;
    PairAttr pair_attr_;
    char val_[MAX_SIZE]; 
    Cell *first_;
    Cell *second_;
    ProcType proc_; 
    bool lambda_;
    Environment *env_;
#ifdef MM_STATUS
    int pool_index_;
#endif
};

extern Cell invalid_cell;
extern Cell null_cell;

extern Cell pair_pool[];
extern Cell cell_pool[];

void print_cell(const Cell *cell);
Cell *get_cell(const char *val, CellType type);
Cell *get_cell(const char *val, ProcType proc);

Cell *car_cell(Cell *cell);
Cell *cdr_cell(Cell *cell);
Cell *cons_cell(Cell *first, Cell *second);
bool is_list(const Cell *cell);
int length_cell(Cell *cell);

class Timer
{
  public:
    Timer(const string &name, u32 interval, Cell *func): 
      name_(name), interval_(interval), func_(func), cur_count_(0), enable_(false)
    {
    }

    void reset_counter()
    {
      cur_count_ = 0;
    }

    const string& name() const
    {
      return name_;
    }

    void add_count()
    {
    }

    void enable(bool e)
    {
      enable_ = e;
    }

    bool is_enable() const
    {
      return enable_;
    }
    bool timeup() const
    {
      if (interval_ == cur_count_)
        return true;
      return false;
    }

    string name_;
    Cell *func_;
    u32 interval_;
    u32 cur_count_;
    bool enable_;

  private:
};

#endif
