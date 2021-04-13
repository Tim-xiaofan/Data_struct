/** 20210412 20:23, zyj, GuangDong*/
#ifndef LISTS_H
#define LISTS_H
#include <cstring>

/** input str of htlists*/
struct istr
{
	/** (),(e),(a,(b,c,d)), no spaces*/
	const char * str;
	static const char * empty;
	istr(const char * mstr = nullptr):str(mstr){}
	/** get head "()" and tail"(e),(a,(b,c,d)"*/
	void get_ht(char *head, char *tail);
    static bool is_empty(const char *s){return strcmp(empty, s) == 0;}
	/** is atom ?*/
	static bool is_atom(const char * s);
	/** rm outermost parenthesis*/
	static void remove_lr(char * s);
};

const char * istr:: empty = "()";

inline void istr::
get_ht(char *head, char *tail)
{
	int left = 0, right = 0, len, i, pos;
	len = strlen(str);
	if(len == 0)
	{
		strcpy(head, empty);
		strcpy(tail, empty);
		return;
	}
	
	/** get head*/
	for(i = 0, pos = 0; i < len; ++i)
	{
	  switch(str[i])
	  {
		  case '(':left++; break;
		  case ')':right++; break;
	  }
	  head[pos++] = str[i];
	  if(left * right != 0 && left == right)
		break;
	}
	head[pos] = '\0';

	/** get tail*/
	if(pos >= len)
	{/** empty*/
		strcpy(tail, empty);
	}
	else
	{
		for(i = pos + 1, pos = 0; i < len; ++i)
		  tail[pos++] = str[i];
		tail[pos] = '\0';
	}
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

inline void istr::
remove_lr(char * s)
{
	int i, len = strlen(s);
	if(s[0] != '(' || s[len-1] !=')')
	  return;
	for(i = 1; i < len - 1; ++i)
	  s[i-1] = s[i];
	s[len - 2] = '\0';
}

template <typename Atom>
class htlists
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
					struct {Node *hp, *tp;} ptr;
				};
			};
		typedef Node<Atom> node;
	private:
		node *_lists;
		int length;
	private:
		int depth(node * lists) const;
		/** create lists*/
		void create(node * & lists, char * str);   
	public:
		typedef node htnode;
		typedef node* phtnode;
	public:
		htlists():_lists(nullptr){}
		htlists(const char * str);
		int depth(void) const{return depth(_lists);}
		const phtnode & get_head(void) const {return _lists;};
		phtnode & get_head(void){return _lists;};
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
	char head[512], tail[512];
	istr is(str);
	is.get_ht(head, tail);
	istr::remove_lr(head);
	create(_lists, head);
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
create(node * & ls, char *str)
{
	if(istr::is_empty(str))/** create an empty list*/
	  ls = nullptr;
	else
	{
		ls = new htnode();
		if(istr::is_atom(str))/** atom */
		{
			ls->tag = htnode::ATOM;
			/**FIXME: atom may be int, long, float types*/
			ls->atom = str[0]; 
		}
		else
		{/**sub list*/
			char head[512], tail[512];
			istr::remove_lr(str);
			ls->tag = htnode::LIST;
			node * p = ls, *tmp = nullptr;
			do
			{
				istr is(str);
				is.get_ht(head, tail);
				/** creat head*/
				create(p->ptr.hp, head);
				tmp = p;
				if(!istr::is_empty(tail))
				{
					p = new node;
					p->tag = node::LIST;
					tmp->ptr.tp = p;
				}
			}while(!istr::is_empty(tail));
			tmp->ptr.tp = nullptr;
		}
	}
}
#endif
