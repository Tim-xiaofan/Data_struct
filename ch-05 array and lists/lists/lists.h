/** 20210412 20:23, zyj, GuangDong*/
#ifndef LISTS_H
#define LISTS_H
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

#define SEP(info) cout <<"-------------" << info << "-------------" <<endl

/** input str of htlists*/
struct istr
{
	/** (),(e),(a,(b,c,d)), no spaces*/
	const char * str;
	static const char * empty;
	istr(const char * mstr = nullptr):str(mstr){}
	/** get head "()" and tail"(e),(a,(b,c,d)"*/
	void de_head(char *head);
    static bool is_empty(const char *s){return strcmp(empty, s) == 0;}
	/** is atom ?*/
	static bool is_atom(const char * s);
	/** rm outermost parenthesis*/
	static void remove_lr(char * s);
};

const char * istr:: empty = "()";

/** get and rm head*/
inline void istr::
de_head(char *head)
{
	int left = 0, right = 0, len, i;
	len = strlen(str);
	if(len == 0)
	{
		strcpy(head, empty);
		return;
	}
	
	/** get head*/
	for(i = 0; i < len; ++i)
	{
	  switch(str[i])
	  {
		  case '(':left++; break;
		  case ')':right++; break;
	  }
	  head[i] = str[i];
	  if(left == right)
	  {
		  ++i;
		  break;
	  }
	}
	head[i] = '\0';
	if(str[i] == ',') ++i;
	str += i;
}


/** single layer ?
  * test if there is  a '(', yes for false, no for true 
 **/
inline bool istr::
is_atom(const char * s)
{
	int i, len = strlen(s);
	for(i = 0; i < len; ++i)
	  if(s[i] == '(') return false;
	return true;
}

/** O(1) */
inline void istr::
remove_lr(char *  s)
{
	int i, len = strlen(s);
	if(s[0] != '(' || s[len-1] !=')')
	  return;
	for(i = 1; i < len - 1; ++i)
	  s[i-1] = s[i];
	s[len - 2] = '\0';
	//s+=1;
	//s[len - 2] = '\0';
}

template <typename Atom>
class htlists
{
	private:
		template<typename Atom1>
			struct Node
			{
				typedef enum{UNKNOW = -1, ATOM = 0, LIST = 1} elem_type;
				elem_type tag;
				union 
				{
					Atom1 atom;
					struct {Node *hp, *tp;} ptr;
				};
				Node():tag(UNKNOW){}
			};
		typedef Node<Atom> node;
	private:
		node *_lists;
		int length;
	private:
		int depth(node * lists) const;
		/** create lists*/
		void create(int n, node * &lists, char * str);   
		void show(const node * lists, bool)const;
	public:
		typedef node htnode;
		typedef node* phtnode;
	public:
		htlists():_lists(nullptr){}
		htlists(const char * str);
		int depth(void) const{return depth(_lists);}
		const phtnode & get_head(void) const {return _lists;};
		phtnode & get_head(void){return _lists;};
		void show(void)const;
};

template <typename Atom>
class llists
{
	private:
		template<typename Atom1>
			struct Node
			{
				typedef enum{ATOM = 0, LIST = 0} elem_type;
				elem_type tag;
				union 
				{
					Atom1 atom;
					Node *hp;
				};
				Node * tp;
			};
	private:
		typedef Node<Atom> node;
		node *_lists;
};

template <typename Coef>
class mplist
{
	private:
		template<typename Coef1>
			struct mpnode
			{
				union
				{
					Coef1 coef;
					mpnode *hp;
				};
				int exp;
				mpnode * tp;
			};
	private:
		typedef mpnode<Coef> node;
		node *_lists;
};


/** htlists methods*/
template<typename Atom>
htlists<Atom>::
htlists(const char * str)
{
	char input[1024];
	if(strlen(str) == 0 || str[0] != '(')
	{
		input[0] = '(';
		input[1] = ')';
		input[2] = '\0';
	}
	else strcpy(input, str);
	create(0, _lists, input);
}

template<typename Atom>
int htlists<Atom>::
depth(node * lists) const
{
	int max, dep;
	node *p;
	if(!lists) return 1;/** depth of empty lists is 1*/
	if(lists->tag == node::ATOM) return 0;/** depth of atom is 0*/

	for(max = 0, p = lists; p; p = p->ptr.tp)
	{
		dep = depth(p->ptr.hp);
		if(max < dep) max = dep;
	}
	return max + 1;
}

template<typename Atom>
void htlists<Atom>::
create(int n, node * & ls, char *str)
{
	//SEP(n << " enter");
	//cout << "with str = " << str  << ", &ls = " << (void *)&ls << endl;
	if(n >= 20) return;
	//cout << str << " is empty : " << std::boolalpha << istr::is_empty(str) << endl;
	if(istr::is_empty(str))/** create an empty list*/
	{
		ls = nullptr;
	}
	else
	{
		ls = new htnode();
		if(istr::is_atom(str))/** atom */
		{
			ls->tag = htnode::ATOM;
			/**FIXME: atom may be int, long, float types*/
			ls->atom = str[0]; 
			//cout << "creat atom : " << ls->atom << ", " << (void*)&ls->atom << endl;
			//cout << "list:";
			//show();
		}
		else
		{/**sub list*/
			char head[512];
			istr::remove_lr(str);
			//cout << "after rm str:" << str << endl;
			istr is(str);
			ls->tag = htnode::LIST;
			node * p = ls, *tmp = nullptr;
			do
			{
				is.de_head(head);
				//cout << "head : " << head << endl;
				//cout << "remain : " << is.str << endl;
				/** creat head*/
				create(n + 1, p->ptr.hp, head);
				tmp = p;
				if(strlen(is.str))
				{
					p = new node;
					p->tag = node::LIST;
					tmp->ptr.tp = p;
				}
				//cout << "list:";
				//show();
			}while(strlen(is.str));
			tmp->ptr.tp = nullptr;
		}
	}
	//SEP(n << " leave");
}
template<typename Atom>
void htlists<Atom>::
show(void)const
{
	cout << "(";
	show(_lists, (_lists && _lists->tag == node::LIST)&&(_lists->ptr.tp));
	cout << ")";
	cout << endl;
}

template<typename Atom>
void htlists<Atom>::
show(const node * lists, bool tail)const
{
	int dep, i;
	if(lists == nullptr)
	{
		cout << "";
	}
	else
	{
		if(lists->tag == node::ATOM)
		{
			cout << lists->atom;
			if(tail) cout << ",";
		}
		else if(lists->tag == node::LIST)
		{
			dep = depth(lists->ptr.hp);
			if(dep > 1) --dep;
			for(i = 0; i < dep; ++i)
			  cout << "(";
			show(lists->ptr.hp, lists->ptr.tp);
			for(i = 0; i < dep; ++i)
			  cout << ")";
			if(i > 0 && tail)cout << ",";

			/** tail*/
			if(lists->ptr.tp)
			{
				show(lists->ptr.tp, (lists->ptr.tp->tag == node::LIST) && (lists->ptr.tp->ptr.tp));
			}
		}
	}
}
#endif
