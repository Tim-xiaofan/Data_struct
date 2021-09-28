/** 20210404 19:04, zyj, GuangDong*/
//evaluate_expression.cpp -- caculate  the result of expression
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "sqstack.h"

template<typename Value>
struct item
{
	enum{OPND = 0, OPTR = 1, UNKNOWN = 2};
	Value _value;
	int _type;
	~item(){}
	item(){};
	item(const Value & value, int type):_value(value), _type(type){}
	Value value(void) const {return _value;}
	int type(void) const {return _type;}
};

std::ostream & operator<<(std::ostream & os, const item<std::string> & i)
{
	os << "<";
	if(i._type == item<std::string>::OPND) os << "OPND,";
	else if(i._type == item<std::string>::OPTR)os << "OPTR,";
	else os << "UNKNOWN,";
	os << i._value << ">";
	return os;
}

class expression
{
	public:
		typedef item<std::string> item_type;
	public:
		static const int OPND, OPTR, UNKNOWN;
		enum{LOW = -1, EQUAL = 0, HIGH = 1, NB_OPTRS = 7};
		static const std::string optrs[NB_OPTRS];
		static const int precede_tbl[NB_OPTRS][NB_OPTRS];
		static const item_type delimiter;
	private:
		std::string _expr;
		int _pos, _count;
		bool _valid;
		item_type _items[256];
	private:
		bool is_number(char ch){return (ch >= '0' && ch <= '9');}
		bool is_optr(char ch){return (ch == ')'||ch == '('|| ch == '#'||
					ch == '+' || ch == '-' || ch == '*' || ch == '/');}
		bool is_space(char ch){return ch == ' ';}
		static int get_index(const std::string & val);
	public:
		~expression(){}
		expression(const std::string & expr);
		bool is_valid(void)const{return _valid;}
		int count(void)const{return _count;}
		int next(std::string & result);
		void show(void)const;
		const item_type & operator[](int pos)const {return _items[pos];}
		item_type & operator[](int pos){return _items[pos];}
		static int precede(const item_type & i1, const item_type &i2);
		static void show_tbl(void);
		static item_type operator_theta(const item_type & theta, const item_type & a, 
						const item_type & b);
};

/** 运算集合*/
const std::string expression::optrs[expression::NB_OPTRS] = {"+", "-", "*", "/","(", ")","#"};
const expression::item_type expression::delimiter("#", expression::OPTR);
const int expression::OPND = expression::item_type::OPND;
const int expression::OPTR = expression::item_type::OPTR;
const int expression::UNKNOWN = expression::item_type::UNKNOWN;
/** 优先关系表*/
const int expression::precede_tbl[NB_OPTRS][NB_OPTRS] = 
{
	{HIGH, HIGH, LOW, LOW, LOW, HIGH, HIGH},
	{HIGH, HIGH, LOW, LOW, LOW, HIGH, HIGH},
	{HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},
	{HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},
	{LOW, LOW, LOW, LOW, LOW, EQUAL, UNKNOWN},
	{HIGH, HIGH, HIGH, HIGH, UNKNOWN, HIGH, HIGH},
	{LOW, LOW, LOW, LOW, LOW, UNKNOWN, EQUAL}
};

int expression::
get_index(const std::string & val)
{
	int i;
	for(i = 0; i < NB_OPTRS; i++)
	  if(val == optrs[i]) return i;
	return -1;
}

void expression::
show_tbl(void)
{
	int i, j;
	
	for(i = 0; i < expression::NB_OPTRS; i++)
	{
	  for(j = 0; j < expression::NB_OPTRS; j++)
		std::cout << std::setw(2) << expression::precede(item<std::string>(expression::optrs[i], 0), 
					item<std::string>(expression::optrs[j], 0)) << " ";
	  std::cout << std::endl;
	}
}

int expression::
precede(const item_type & i1, const item_type &i2)
{
	int i, j;

	i = get_index(i1._value);
	j = get_index(i2._value);
	return precede_tbl[i][j];
}

expression::item_type expression:: 
operator_theta(const item_type & theta, const item_type & a, 
			const item_type & b)
{
	/** FIXME: maybe not only int*/
	int ia, ib;
	ia = std::atoi(a._value.c_str());
	ib = std::atoi(b._value.c_str());
	if(theta._value == "+")
	  return item_type(std::to_string(ia + ib), OPND);
	if(theta._value == "-")
	  return item_type(std::to_string(ia - ib), OPND);
	if(theta._value == "*")
	  return item_type(std::to_string(ia * ib), OPND);
	if(theta._value == "/")
	  return item_type(std::to_string(ia / ib), OPND);
	return item_type(theta._value, UNKNOWN);
}

expression::
expression(const std::string & expr):_expr(expr), _pos(0), _count(0),_valid(false)
{
	int ret;
	std::string val;

	while((ret = next(val)) != UNKNOWN)
	  _items[_count++] = item_type(val, ret);

	while(_expr[_pos] == ' ') ++_pos;
	if((unsigned long int)_pos == expr.length()) _valid = true; 
}

void expression::
show(void) const
{
	int i;
	for(i = 0; i <_count; i++)
	  std::cout << _items[i] << " ";
	std::cout << std::endl;
}

int expression::
next(std::string & result)
{
	result.clear();
	while(_expr[_pos] == ' ') ++_pos;

	if((is_number(_expr[_pos])))
	{
		while(is_number(_expr[_pos]))
		  result.push_back(_expr[_pos++]);
		return OPND;
	}
	else if((is_optr(_expr[_pos])))
	{
		result.push_back(_expr[_pos++]);
		return OPTR;
	}
	return UNKNOWN;
}

template<typename Expression, typename Operand>
bool evaluate_expression(const Expression & expr, Operand & result)
{
	if(!expr.is_valid())
		return false;

	typedef typename Expression::item_type item;

	int count = expr.count(), i;
	sqstack<item> optr(count);
	optr.push(Expression::delimiter);
	sqstack<item> opnd(count);
	item a, b, theta, top;

	for(i = 0; i < count; i++)
	{
		std::cout << "#"<< i <<"---------------\n";
		std::cout << "cur = " << expr[i] << std::endl;
		if((expr[i]).type() == Expression::OPND)/** It's operand, just push into operand stack*/
		  opnd.push(expr[i]);
		else/** It's operator*/
		{
			optr.get_top(top);//peek(not push top from statck)
			switch(Expression::precede(top, expr[i]))
			{
				case Expression::LOW: /** top < current*/
					optr.push(expr[i]);
					break;
                case Expression::EQUAL: /** equal : rm bracket*/
					optr.pop(theta);
					break;
				case Expression::HIGH:/** top > current*/
					if(!opnd.pop(b) || !opnd.pop(a))
					  return false;
					optr.pop(theta);
					/** get result and push result into operator stack*/
					opnd.push(Expression::operator_theta(theta, a, b));
					--i;
					//optr.push(expr[i]);
					break;
				case Expression::UNKNOWN:/** incomparable*/
					return false;/** error*/
			}
		}
        std::cout << "operands : ";
		opnd.show();
        std::cout << "operator : ";
		optr.show();
		std::cout << "#"<< i <<"---------------\n";
	}
	opnd.get_top(result);
	return true;
}

int main()
{
	using namespace std;

	int i;
	expression expr("(7/2 + 8) * (9 + 5) / 2    # ");
	cout << "expression : (7/2 + 8) * (9 + 5) / 2   #  " << endl;
	expr.show();
	cout << "valid : " << std::boolalpha << expr.is_valid() << endl;
	for(i = 0; i < expr.count(); ++i)
	  cout << expr[i] << " ";
	cout << endl;
    cout << "precede table : " << endl;
	expression::show_tbl();
	item<string> a("12", item<string>::OPND);
	item<string> b("18", item<string>::OPND);
	item<string> theta_plus("+", item<string>::OPTR);
	item<string> theta_minus("-", item<string>::OPTR);
	item<string> theta_multi("*", item<string>::OPTR);
	item<string> theta_divide("/", item<string>::OPTR);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << expression::operator_theta(theta_plus, a, b) << endl;;
	cout << expression::operator_theta(theta_minus, a, b) << endl;;
	cout << expression::operator_theta(theta_multi, a, b) << endl;;
	cout << expression::operator_theta(theta_divide, a, b) << endl;;

	expression::item_type result("-1", expression::UNKNOWN);
	evaluate_expression(expr, result);
	cout << "result : " << result << endl;
}
