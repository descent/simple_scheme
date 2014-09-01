#include <iterator>     // std::back_inserter
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <cstdlib>

using namespace std;


// return given mumber as a string
std::string str(long n) { std::ostringstream os; os << n; return os.str(); }

// return true iff given character is '0'..'9'
bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }


////////////////////// Cell

enum ProcKind {PRIMITIVE, LAMBDA};
enum cell_type {String, Symbol, Number, List, Proc, Lambda, SelfEval, Variable, INVALID};
std::string cell_type_string[] = {"String", "Symbol", "Number", "List", "Proc", "Lambda", "SelfEval", "Variable"};

struct environment; // forward declaration; cell and environment reference each other


// a variant that can hold any kind of lisp value
struct Cell 
{
    typedef Cell (*proc_type)(const std::vector<Cell> &);
    typedef Cell (*ProcType)(const Cell &);
    typedef std::vector<Cell>::const_iterator iter;
    typedef std::map<std::string, Cell> map;

    Cell(cell_type type = Symbol) : type(type), env(0) {}
    Cell(cell_type type, const std::string & val)
      : type(type), val(val), env(0)
    {}
    Cell(ProcType proc, const std::string proc_name) 
      :type(Proc), proc_(proc), val(proc_name), env(0), proc_kind_(PRIMITIVE)
    {}

    cell_type kind() const {return type;}
    ProcKind proc_kind() const {return proc_kind_;}
    std::string kind_str() const 
    {
      return cell_type_string[kind()];
    }
    cell_type type; 
    ProcKind proc_kind_; // if type is Proc need check it.
    std::string val; 
    std::vector<Cell> list; 
    proc_type proc; 
    ProcType proc_; 

    environment * env;

};

void print_cell(const Cell &exp);

Cell invalid_cell(INVALID);

Cell car_cell(const Cell &cell)
{
  if (cell.kind() != List)
    return invalid_cell;

  cout << "---" << endl;
  cout << cell.list[0].kind_str() << endl;
  //print_cell(cell.list[0]);
  cout << "\n---" << endl;
  return cell.list[0];
}

Cell cdr_cell(const Cell &cell)
{
  if (cell.kind() != List)
    return invalid_cell;

  // performance is veay poor
  Cell rear(List);
  std::copy(cell.list.begin()+1, cell.list.end(), back_inserter(rear.list));
  return rear;
}

Cell cons_cell(const Cell &c1, const Cell &c2)
{
  Cell cell(List);
  Cell cell1(List);
  Cell cell2(List);

  std::copy(c1.list.begin(), c1.list.end(), back_inserter(cell1.list));
  std::copy(c2.list.begin(), c2.list.end(), back_inserter(cell1.list));
  cell.list.push_back(c1);
  cell.list.push_back(c2);
  return cell;
}

Cell proc_cons(const Cell &c)
{
  return c;
  //print_cell(c);
}


    // the code is short, but I think 1 hours.
    void print_cell(const Cell &exp)
    {
      switch (exp.kind())
      {
        case List: 
        {
          cout << "(";
          for (int i=0 ; i < exp.list.size() ; ++i)
            print_cell(exp.list[i]);
          cout << ") ";
          break;
        }
        default:
        {
          //cout << exp.val << "(" << exp.kind_str() << ") , ";
          cout << exp.val << " , ";
          break;
        }
      }
      
    }



typedef std::vector<Cell> cells;
typedef cells::const_iterator cellit;

const Cell false_sym(Symbol, "#f");
const Cell true_sym(Symbol, "#t"); // anything that isn't false_sym is true
const Cell nil(Symbol, "nil");


////////////////////// environment
//

typedef std::map<std::string, Cell> Frame;
struct Environment 
{
  public:
    Environment(): outer_(0) {}
    Environment *outer_;

    Frame frame_;
  private:
};

const Cell& lookup_variable_value(const Cell &exp, const Environment *env)
{

  Frame::const_iterator it = env->frame_.find(exp.val);
  if (it != env->frame_.end()) // find it
    return (*it).second;
  else
  {
    if (env->outer_ != 0)
      return lookup_variable_value(exp, env->outer_);
    else
    {
      return invalid_cell;
    }
  }
}

Cell eval(const Cell &exp, Environment *env);

int add_cell(const Cell &c)
{
  switch (c.kind())
  {
    case List: 
    {
      int sum=0;

      for (int i=0 ; i < c.list.size() ; ++i)
        sum += add_cell(c.list[i]);
      return sum;
      break;
    }
    case Number:
    {
      int num = atol(c.val.c_str() );
      cout << "num: " << num << endl;
      return num;
      break;
    }
    default:
    {
      break;
    }
  }
}

Cell proc_add(const Cell &c)
{
  int sum = add_cell(c);
  cout << "sum: " << sum << endl;
  return Cell(Number, str(sum));
}

int sub_cell(const Cell &c)
{
  switch (c.kind())
  {
    case List: 
    {
      int result=0;
      if (c.list.size() >= 1)
        result = sub_cell(c.list[0]);

      for (int i=1 ; i < c.list.size() ; ++i)
        result -= sub_cell(c.list[i]);
      return result;
      break;
    }
    case Number:
    {
      int num = atol(c.val.c_str() );
      cout << "num: " << num << endl;
      return num;
      break;
    }
    default:
    {
      break;
    }
  }
}

Cell proc_sub(const Cell &c)
{
  int result = sub_cell(c);
  cout << "result: " << result << endl;
  return Cell(Number, str(result));
}

int mul_cell(const Cell &c)
{
  switch (c.kind())
  {
    case List: 
    {
      int product=1;

      for (int i=0 ; i < c.list.size() ; ++i)
        product *= mul_cell(c.list[i]);
      return product;
      break;
    }
    case Number:
    {
      int num = atol(c.val.c_str() );
      cout << "num: " << num << endl;
      return num;
      break;
    }
    default:
    {
      break;
    }
  }
}

Cell proc_mul(const Cell &c)
{
  int product = mul_cell(c);
  cout << "product: " << product << endl;
  return Cell(Number, str(product));
}

void create_primitive_procedure(Frame &frame)
{
  frame.insert(Frame::value_type("+", Cell(proc_add, "primitive add")));
  frame.insert(Frame::value_type("-", Cell(proc_sub, "primitive sub")));
  frame.insert(Frame::value_type("*", Cell(proc_mul, "primitive mul")));
  frame.insert(Frame::value_type("cons", Cell(proc_cons, "primitive cons")));
  frame.insert(Frame::value_type("car", Cell(car_cell, "primitive car")));
  frame.insert(Frame::value_type("cdr", Cell(cdr_cell, "primitive cdr")));
}

#if 0
// a dictionary that (a) associates symbols with cells, and
// (b) can chain to an "outer" dictionary
struct environment {
    environment(environment * outer = 0) : outer_(outer) {}

    environment(const cells & parms, const cells & args, environment * outer)
    : outer_(outer)
    {
        cellit a = args.begin();
        for (cellit p = parms.begin(); p != parms.end(); ++p)
            env_[p->val] = *a++;
    }

    // map a variable name onto a cell
    typedef std::map<std::string, cell> map;

    // return a reference to the innermost environment where 'var' appears
    map & find(const std::string & var)
    {
        if (env_.find(var) != env_.end())
            return env_; // the symbol exists in this environment
        if (outer_)
            return outer_->find(var); // attempt to find the symbol in some "outer" env
        std::cout << "unbound symbol '" << var << "'\n";
        exit(1);
    }

    // return a reference to the cell associated with the given symbol 'var'
    cell & operator[] (const std::string & var)
    {
        return env_[var];
    }
    
private:
    map env_; // inner symbol->cell mapping
    environment * outer_; // next adjacent outer env, or 0 if there are no further environments
};
#endif

#if 0
////////////////////// built-in primitive procedures

cell proc_div(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i) n /= atol(i->val.c_str());
    return cell(Number, str(n));
}

cell proc_greater(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i)
        if (n <= atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_less(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i)
        if (n >= atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_less_equal(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i)
        if (n > atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_length(const cells & c) { return cell(Number, str(c[0].list.size())); }
cell proc_nullp(const cells & c)  { return c[0].list.empty() ? true_sym : false_sym; }
cell proc_car(const cells & c)    { return c[0].list[0]; }

cell proc_cdr(const cells & c)
{
    if (c[0].list.size() < 2)
        return nil;
    cell result(c[0]);
    result.list.erase(result.list.begin());
    return result;
}

cell proc_append(const cells & c)
{
    cell result(List);
    result.list = c[0].list;
    for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

cell proc_cons(const cells & c)
{
    cell result(List);
    result.list.push_back(c[0]);
    for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

cell proc_list(const cells & c)
{
    cell result(List); result.list = c;
    return result;
}

// define the bare minimum set of primintives necessary to pass the unit tests
void add_globals(environment & env)
{
    env["nil"] = nil;   env["#f"] = false_sym;  env["#t"] = true_sym;
    env["append"] = cell(&proc_append);   env["car"]  = cell(&proc_car);
    env["cdr"]    = cell(&proc_cdr);      env["cons"] = cell(&proc_cons);
    env["length"] = cell(&proc_length);   env["list"] = cell(&proc_list);
    env["null?"]  = cell(&proc_nullp);    env["+"]    = cell(&proc_add);
    env["-"]      = cell(&proc_sub);      env["*"]    = cell(&proc_mul);
    env["/"]      = cell(&proc_div);      env[">"]    = cell(&proc_greater);
    env["<"]      = cell(&proc_less);     env["<="]   = cell(&proc_less_equal);
}
#endif


////////////////////// eval

#if 0
cell eval(cell x, environment * env)
{
    if (x.type == Symbol)
        return env->find(x.val)[x.val];
    if (x.type == Number)
        return x;
    if (x.list.empty())
        return nil;
    if (x.list[0].type == Symbol) {
        if (x.list[0].val == "quote")       // (quote exp)
            return x.list[1];
        if (x.list[0].val == "if")          // (if test conseq [alt])
            return eval(eval(x.list[1], env).val == "#f" ? (x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
        if (x.list[0].val == "set!")        // (set! var exp)
            return env->find(x.list[1].val)[x.list[1].val] = eval(x.list[2], env);
        if (x.list[0].val == "define")      // (define var exp)
            return (*env)[x.list[1].val] = eval(x.list[2], env);
        if (x.list[0].val == "lambda") {    // (lambda (var*) exp)
            x.type = Lambda;
            // keep a reference to the environment that exists now (when the
            // lambda is being defined) because that's the outer environment
            // we'll need to use when the lambda is executed
            x.env = env;
            return x;
        }
        if (x.list[0].val == "begin") {     // (begin exp*)
            for (size_t i = 1; i < x.list.size() - 1; ++i)
                eval(x.list[i], env);
            return eval(x.list[x.list.size() - 1], env);
        }
    }
                                            // (proc exp*)
    cell proc(eval(x.list[0], env));
    cells exps;
    for (cell::iter exp = x.list.begin() + 1; exp != x.list.end(); ++exp)
        exps.push_back(eval(*exp, env));
    if (proc.type == Lambda) {
        // Create an environment for the execution of this lambda function
        // where the outer environment is the one that existed* at the time
        // the lambda was defined and the new inner associations are the
        // parameter names with the given arguments.
        // *Although the environmet existed at the time the lambda was defined
        // it wasn't necessarily complete - it may have subsequently had
        // more symbols defined in that environment.
        return eval(/*body*/proc.list[2], new environment(/*parms*/proc.list[1].list, /*args*/exps, proc.env));
    }
    else if (proc.type == Proc)
        return proc.proc(exps);

    std::cout << "not a function\n";
    exit(1);
}
#endif


////////////////////// parse, read and user interaction

// convert given string to list of tokens
std::list<std::string> tokenize(const std::string & str)
{
    std::list<std::string> tokens;
    const char * s = str.c_str();
    while (*s) {
        while (*s == ' ')
            ++s;
        if (*s == '(' || *s == ')')
            tokens.push_back(*s++ == '(' ? "(" : ")");
        else {
            const char * t = s;
            while (*t && *t != ' ' && *t != '(' && *t != ')')
                ++t;
            tokens.push_back(std::string(s, t));
            s = t;
        }
    }
    return tokens;
}

// numbers become Numbers; every other token is a Symbol
Cell atom(const std::string & token)
{
    if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
        return Cell(Number, token);
    return Cell(Symbol, token);
}

// return the Lisp expression in the given tokens
Cell read_from(std::list<std::string> & tokens)
{
    const std::string token(tokens.front());
    tokens.pop_front();
    if (token == "(") {
        Cell c(List);
        while (tokens.front() != ")")
            c.list.push_back(read_from(tokens));
        tokens.pop_front();
        return c;
    }
    else
        return atom(token);
}

// return the Lisp expression represented by the given string
Cell read(const std::string & s)
{
    std::list<std::string> tokens(tokenize(s));
    return read_from(tokens);
}

Cell list_of_values(const Cell &exp, Environment *env)
{
  //cout << "list_of_values" << endl;
  Cell ret_cell(List);

  if (exp.list.size() != 0)
  {

    Cell rear(List);
    std::copy(exp.list.begin()+1, exp.list.end(), back_inserter(rear.list));

    Cell eval_cell = eval(exp.list[0], env);
    if (rear.list.size() != 0)
    {
      ret_cell.list.push_back(eval_cell);
      ret_cell.list.push_back(list_of_values(rear, env));
    }
    else
    {
      return eval_cell;
    }
    //cout << ret_cell.list[0].kind_str() << endl;
    //cout << ret_cell.list[1].kind_str() << endl;
  }
  return ret_cell;
}

Cell apply(const Cell &func, const Cell &args)
{
  cout << "apply:" << func.kind_str() << endl;
  cout << endl;
  cout << "func name:" << func.val << endl;
  //print_cell(func);
  //cout << endl;
  cout << "args:" << endl;
  print_cell(args);
  cout << endl;

  switch (func.proc_kind())
  {
    case LAMBDA:
    {
      // new a Environment
      // add parameters and arguments pair
      Environment env;

      Cell body(List); 
      body = cdr_cell(func);

      Cell parameters(List); 
      parameters = car_cell(func);
      cout << "body: " << endl;
      print_cell(body);
      cout << endl;

      cout << "para: " << parameters.kind_str() << endl;
      print_cell(parameters);
      cout << endl;

      exit(0);
      break;
    }
    case PRIMITIVE:
    {
      cout << "func name:" << func.val << endl;
      return func.proc_(args);
      break;
    }
  }

  return invalid_cell;
}

Cell make_procedure(const Cell &parameters, const Cell &body, Environment *env)
{
  Cell lambda_proc(List);

  lambda_proc = cons_cell(parameters, body);
  lambda_proc.proc_kind_ = LAMBDA;

  return lambda_proc;
}

Cell eval(const Cell &exp, Environment *env)
{
#if 0
  self-evaluating
  variable       //? exp) (lookup-variable-value exp env))
  ((application? exp)
#endif

  switch (exp.kind())
  {
    //case SelfEval: // number or string
    case Number: 
    case String: 
    {
      cout << "in exp:" << exp.val << endl;
      return exp;
      break;
    }
    //case Variable: // symbol
    case Symbol: // symbol
    {
      // lookup environment
      Cell func = lookup_variable_value(exp, env);
      return func;
      break;
    }
    case List: 
    {
      cout << "in list" << endl;
      if (exp.list[0].kind() == Symbol)
      {
        // (lambda (x) (+ x 4))
        // ((lambda (x) (+ x 4)) 5)
        if (exp.list[0].val == "lambda")
        {
          cout << "lambda expression" << endl;
          Cell parameters = car_cell(cdr_cell(exp));
          Cell body = cdr_cell(cdr_cell(exp));

          cout << "parameters: " << parameters.kind_str() << endl;
          print_cell(parameters);
          cout << endl;
          cout << "body: " << body.kind_str() << endl;
          print_cell(body);
          cout << endl;

          return make_procedure(parameters, body, env);
          //exit(0);
        }
        else if (exp.list[0].val == "define") // (define (plus4 y) (+ y 4))
             {
               cout << "define expression" << endl;
               exit(0);
             }
      }

      // application
      {
        // need check exp.list.size() >= 2
        Cell rear(List);
        std::copy(exp.list.begin()+1, exp.list.end(), back_inserter(rear.list));
        return apply(eval(exp.list[0], env), list_of_values(rear, env));
      }
      //apply(eval(exp.list[0]));
      #if 0
      cell cur = exp.list[0];
      return apply(eval(cur));
      #endif
      //cout << "after apply" << endl;
      //return exp;
      break;
    }
  }


}

#if 0
// convert given cell to a Lisp-readable string
std::string to_string(const Cell & exp)
{
    if (exp.type == List) {
        std::string s("(");
        for (cell::iter e = exp.list.begin(); e != exp.list.end(); ++e)
            s += to_string(*e) + ' ';
        if (s[s.size() - 1] == ' ')
            s.erase(s.size() - 1);
        return s + ')';
    }
    else if (exp.type == Lambda)
        return "<Lambda>";
    else if (exp.type == Proc)
        return "<Proc>";
    return exp.val;
}
#endif

// the default read-eval-print-loop
void repl(const std::string & prompt, Environment *env)
{
    for (;;) 
    {
        std::cout << prompt;
        std::string line; std::getline(std::cin, line);
        Cell exp = read(line);


        cout << endl;
        print_cell(exp);
        cout << endl;

        exp = eval(exp, env);
        cout << "result:" << endl;
        if (exp.kind() != INVALID)
        {
          print_cell(exp);
          cout << endl;
        }
        else
        {
          cout << "expression fail!" << endl;
        }
#if 0 
        cell exp2(List);
        std::copy(exp.list.begin()+3, exp.list.end(), back_inserter(exp2.list));
        //exp2.list = exp.list;

        cout << "exp2.list.size(): " << exp2.list.size() << endl;

#if 1
        cout << endl;
        print_cell(exp2);
        cout << endl;
#endif
#endif
        break;
        //std::cout << to_string(eval(read(line), env)) << '\n';
    }
}

int main ()
{
  Environment global_env; //add_globals(global_env);
  create_primitive_procedure(global_env.frame_);
  repl("90> ", &global_env);
}

