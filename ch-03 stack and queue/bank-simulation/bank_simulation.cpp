/** 20210406 21:06, zyj, GuangDong*/
#include "linkqueue.h"
#include "List.h"

struct event
{
	int occur_time, type;
	enum{ARRIVE, NO1, NO2, NO3, NO4};
	event(int t = 0, int tp = ARRIVE)
		:occur_time(t), type(tp){}
};


struct customer
{
	int arrive_time, duration;/** arrive and processing time*/
	customer(int arri = 0, int dur = 0)
		:arrive_time(arri), duration(dur){}
};

typedef List<event> ev_list;/** event list type*/
typedef linkqueue<customer> cu_queue;/** customer queue type*/

static ev_list evl;/** event list*/
static event ev = {0, 0};
static cu_queue cu_qs[4];/**four customer queues */
static customer cst;
static int tot_time, cst_ct;/** accumulative time and customer count*/


/** binary predicate(fake)*/
class cmp
{
	public:
		cmp(){}
		int operator()(const event & x, const event & y)const{ return x.occur_time - y.occur_time;}
};


static void open(void)
{
	/** init*/
	tot_time = 0, cst_ct = 0;
	evl.insert_sorted(ev, cmp());
}

int main()
{
	using namespace std;
	return 0;
}
