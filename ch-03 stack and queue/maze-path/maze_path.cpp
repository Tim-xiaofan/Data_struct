/** 20210403 14:21, zyj, GuangDong*/
// maze_path.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <initializer_list>
#include "../sqstack-adt/sqstack.h"

#define N 2
#define M 5


template<typename Array>
void 
show(const Array & a, int rows, int cols);

class room
{
	private:
		int _val, _i, _j;
		bool _in_path;/** whether in path, true is yes*/
		int _nb_exp; /** number of explorations from this room*/
	public:
		typedef int value_type;
		~room(){}
		room(int val = 0, int i = 0, int j = 0, bool in_path = false, int nb_exp = 0)
			:_val(val), _i(i), _j(j), _in_path(in_path), _nb_exp(nb_exp){}
		room(const room &) = default;
		room & operator=(const room &) = default;
		bool operator==(const room & r) const {return _i == r._i && _j == r._j;}
		bool operator!=(const room & r) const {return !operator==(r);}
		bool is_room(void) const {return _val == 0;}
		int i(void)const{return _i;};
		int j(void)const{return _j;};
		/** check whether in path*/
		bool in_path(void) const {return _in_path;}
		/** chang path status*/
		void in_path(bool in_path) {_in_path = in_path;}
		/** whether can explore starting from this room*/
		bool has_other(void)const{return _nb_exp < 4;} 
		void reset_status(void) {_in_path = false; _nb_exp = 0;}
		/** return next direction*/
		bool next(room & next);
		friend std::ostream & operator<<(std::ostream & os, const room & i);
};


bool room::
next(room & next)
{
	switch(_nb_exp)
	{
		case 0 : /** turn right*/
			//std::cout << "(" << _i << "," << _j << "):right\n";
			next._i = _i;
			next._j = _j + 1;
			break;
		case 1:/** turn down*/
			//std::cout << "(" << _i << "," << _j << "):down\n";
			next._i = _i + 1;
			next._j = _j;
			break;
		case 2:/** turn left*/
			//std::cout << "(" << _i << "," << _j << "):left\n";
			next._i = _i;
			next._j = _j - 1;
			break;
		case 3:/** turn up*/
			//std::cout << "(" << _i << "," << _j << "):up\n";
			next._i = _i - 1;
			next._j = _j;
			break;
		default:
			return false;
	}
	++_nb_exp;
	return true;
}

std::ostream & operator<<(std::ostream & os, const room & r)
{

	//std::cout << "\033[1;32m" <<"bold red text" << "\033[0m\n";
	os << "<" << r._val << ",(" << r._i << ","
		<< r._j << "),";
	//if(r._in_path)
	//  os << "\033[1;32m"  <<std::setw(5) << std::left
	//	 << std::boolalpha <<r._in_path <<  "\033[0m";
	//else
	os << std::setw(5) << std::left
		<< std::boolalpha <<r._in_path; 

	os << ","<< r._nb_exp << ">";
	return os;
}

template<typename T>
class array_2d
{
	private:
		T * _vals;
		int _rows, _cols;
	public:
		~array_2d(){delete[] _vals;}
		array_2d(int rows = 0, int cols = 0);
		array_2d(const std::initializer_list<std::initializer_list<T>> &ils);
		array_2d(const array_2d &) = delete;
		array_2d & operator=(const array_2d &) = delete;
		array_2d & operator=(array_2d &&);
		T * operator[](int i) {return &_vals[i * _cols];}
		//T & operator[][](int i, int j) {return &_vals[i * _cols + j];}
		const T * operator[](int i) const {return &_vals[i * _cols];}
		int rows(void)const{return _rows;}
		int cols(void)const{return _cols;}
		void show(void)const;
};

template<typename T>
array_2d<T>::
array_2d(int rows, int cols)
{
	_vals = nullptr;
	if(rows * cols != 0)
	  _vals = new T[rows * cols];
	_rows = rows;
	_cols = cols;
}


template<typename T>
array_2d<T>::
array_2d(const std::initializer_list<std::initializer_list<T>> & ils)
{
	int i, j;
	typename std::initializer_list<std::initializer_list<T> >::const_iterator iti;
	typename std::initializer_list<T>::const_iterator itj;

	_rows = ils.size();
	_cols = (*ils.begin()).size();
	_vals = new T[_rows * _cols]; 
	
	//std::cout << "rows = " << _rows << std:: endl;
	//std::cout << "cols = " << _cols << std:: endl;
	for(i = 0, iti  = ils.begin(); i < _rows; ++i, ++iti)
	{
		for(j = 0, itj = (*iti).begin(); j < _cols; ++j, ++itj)
		{
			_vals[i * _cols + j] = *itj;
			//std::cout << "(" << i * _cols +j <<")";
			//std::cout << *itj << " ";
		}
		//std::cout << std::endl;
	}
	//std::cout << "\n\n";
}

template<typename T>
array_2d<T> & array_2d<T>::
operator=(array_2d && a)
{
	//std::cout << "array_2d : move assignment operator\n";
	if(&a == this)
	  return *this;

	delete _vals;
	_vals = a._vals;
	_rows = a._rows;
	_cols = a._cols;

	a._vals = nullptr;
	a._rows = 0;
	a._cols = 0;
	return *this;
}

template<typename T>
void array_2d<T>::
show(void)const
{
	int i, j;
	for(i = 0; i < _rows; ++i)
	{
		for(j = 0; j < _cols; ++j)
		  std::cout << _vals[i * _cols + j] <<" ";
		std::cout << std::endl;
	}
}

template <typename Room = room>
class maze
{
	public:
		typedef typename Room::value_type value_type;
		typedef Room room_type;
	private:
		int _rows, _cols;
		array_2d<Room> _rooms;
		Room _start, _end, _invalid;
	public:
		~maze(){};
		maze(const array_2d<value_type> & a);
		maze(const maze &) = delete;
		maze operator=(const maze &) = delete;
		int rows(void){return _rows;}
		int cols(void){return _cols;}
		Room start(void)const{return _start;};
		void start(int x, int y);/** set start*/
		Room end(void)const{return _end;}
		void end(int x, int y);/** set end*/
		/** explore next direction*/
		bool get_next(const Room & cur, Room & next);
		/** set status is in path*/
		void in_path(const Room & cur, bool in_path){_rooms[cur.i()][cur.j()].in_path(in_path);}
		bool in_path(const Room & cur)const{return _rooms[cur.i()][cur.j()].in_path();}
		void show(void)const{_rooms.show();};
		/** check whether the room is out of bound and check whether in path*/
		bool is_valid(const Room & cur) const {
			return !(cur.i() < 0 || cur.j() < 0 || cur.i() >= _rows || cur.j() >= _cols);}
		void reset_status(const Room & cur){_rooms[cur.i()][cur.j()].reset_status();}
		bool has_other(const Room & cur)const;
		bool is_room(const Room & cur)const{return(cur != _invalid)&&_rooms[cur.i()][cur.j()].is_room();}
};

template<typename Room>
maze<Room>::
maze(const array_2d<value_type> & a)
{
	int i, j;

	_rows = a.rows();
	_cols = a.cols();
	_rooms = std::move(array_2d<Room>(_rows, _cols));
	for(i = 0; i < _rows; ++i)
	  for(j = 0; j < _cols; ++j)
		_rooms[i][j] = Room(a[i][j], i, j); 
	_start = _rooms[0][0];
	_end = _rooms[_rows - 1][_cols -1];
	_invalid = Room(1, -1, -1);
}

/** check whether current pos can explore continue */
template<typename Room>
bool maze<Room>::
has_other(const Room & cur)const
{
	int i, j;
	Room tmp, next;

	i = cur.i();
	j = cur.j();
	if(cur == _invalid) return false;
	tmp = _rooms[i][j];
	if(tmp.has_other())/** check direction*/
	  while(tmp.next(next))
		if(is_valid(next) && !in_path(next))/** valid and not in path*/ 
		  return true;
	return false;
}


/** explore next direction*/
template<typename Room>
bool maze<Room>::
get_next(const Room & cur, Room & next)
{

	while(_rooms[cur.i()][cur.j()].next(next))
	  if(is_valid(next)&& !in_path(next)) return true;

	next = _invalid;
	return false;
}

template<typename Maze>
bool maze_path(Maze & maze)
{
	typedef typename Maze::room_type room;
	int rows, cols, loop = 0;
	room start, end, cur, next, top;

	/** check start and end*/
	start = maze.start();
	end = maze.end();
	if(!start.is_room() || !end.is_room())
	{
		std::cout << "invalid start or end\n";
		return false;
	}

	/** init stack*/
	rows = maze.rows();
	cols = maze.cols();
	sqstack<room> path(rows * cols);

	cur = start;
	do
	{
		++loop;
		if(maze.is_room(cur))/** room*/
		{
			if(!path.push(cur))
			{
				std::cout << "path is full\n";
				return false;
			}
			maze.in_path(cur, true);/** marked*/
			if(cur == end)
			{
				std::cout << "got a path : ";
				path.show();
				return true;
			}
			std::cout << cur << " is room\n";
			maze.get_next(cur, next);
			cur = next;
			std::cout << next << " is next\n";
		}
		else
		{
			std::cout << cur << " is not room\n";
			path.get_top(top);
			if(maze.has_other(top))/** there are other direction to explore*/
			{
				std::cout << "there are other direction in top : "<< top << "\n";
				maze.get_next(top, next);
				cur =next;
				std::cout << next << " is next\n";
			}
			else
			{/** there are not other direction to explore in top */
				path.get_top(top);
				while(!maze.has_other(top))
				{
					maze.reset_status(top);
					path.pop(top);
					std::cout << "no other, pop : " << top << std::endl;
					path.get_top(top);
				}
				if(!path.is_empty()) 
				{/** found one that has other direction to explore*/
					path.get_top(top);
					std::cout << "found one in stack"<< top <<"\n";
					maze.get_next(top, next);
					cur =next;
					std::cout << next << " is next\n";
				}
			}
		}
		std::cout << "current path : ";
		path.show();
		std::cout << "current maze : \n";
		maze.show();
		std::cout << "\n";
	}while(!path.is_empty());
	std::cout << "no path found : " << loop <<"\n";
	return false;
}

template<typename Array>
void 
show(const Array & a)
{
	int i, j, rows, cols;
	rows = a.rows();
	cols = a.cols();
	for(i = 0; i < rows; ++i)
	{
		for(j = 0; j < cols; ++j)
		  std::cout << a[i][j] << " ";
		std::cout << std::endl;
	}
}

static array_2d<int> values = 
{
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1},
	{0,0,0,0,0,1,0}
};

int main()
{
	using namespace std;

	maze<> mz(values);

	maze_path(mz);
	mz.show();
	return 0;
}
