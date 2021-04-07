/** 20210406 21:06, zyj, GuangDong*/
//bank_simulation.cpp
#include "linkqueue.h"
#include "List.h"
#include <cstdlib> /** for randon*/
#include <ctime>/** for time*/

struct event
{
	int occur_time, type;
	enum{ARRIVE = -1, NO1 = 0, NO2 = 1 , NO3 = 2, NO4 = 3};
	event(int t = 0, int tp = ARRIVE)
		:occur_time(t), type(tp){}
	friend std::ostream & operator<<(std::ostream & os, const event & ev);
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
static event ev = {0, event::ARRIVE};
static cu_queue cst_qs[4];/**four customer queues */
static customer cst;
static int tot_time, cst_ct;/** accumulative time and customer count*/
static int close_time = 60 * 8;


/** binary predicate(fake)*/
class cmp
{
	public:
		cmp(){}
		int operator()(const event & x, const event & y)const{ return x.occur_time - y.occur_time;}
};


static void 
open(void)
{
	/** init*/
	tot_time = 0, cst_ct = 0;
	evl.insert_sorted(ev, cmp());
}

/** in minutes*/
static void 
customer_arrived(void)
{
	int durtime, intertime, t, min, i;

	++cst_ct;
	durtime = rand() % 60;/** in minutes*/
	intertime = rand() % 15;/** in minutes*/
	t = ev.occur_time  + intertime; /** next customer arriving time*/
	if(t < close_time)/** not closed*/
	  evl.insert_sorted(event(t, event::ARRIVE), cmp());

	min = 0;
	for(i = 0; i < 4; i++)
	  if(cst_qs[i].length() < cst_qs[min].length()) 
		min = i;
	cst_qs[min].enqueue(customer(ev.occur_time, durtime));
	if(cst_qs[min].length() == 1)
	  evl.insert_sorted(event(ev.occur_time + durtime, min), cmp());/** set first departure time*/
}

static void
customer_departure(void)
{
	int i = ev.type;
	cst_qs[i].dequeue(cst);
	tot_time += ev.occur_time - cst.arrive_time;

	if(!cst_qs[i].is_empty())
	{
		cst_qs[i].get_top(cst);
		/** set next customer departure event*/
		evl.insert_sorted(event(ev.occur_time + cst.arrive_time, i), cmp());
	}
}

static void 
bank_simulation(void)
{
	open();
	while(!evl.is_empty())
	{
		evl.del_n(0, ev);
		if(ev.type == event::ARRIVE)
		  customer_arrived();
		else
		  customer_departure();
	}
	std::cout << "The average time is " << tot_time / cst_ct << std::endl;
}

int main()
{
	using namespace std;

	srand(time(NULL));

	bank_simulation();
	return 0;
}
