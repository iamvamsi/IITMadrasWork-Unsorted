#include<iostream>
#include<cmath>

using namespace std;

class ordered_pair
{
	private:
		float a,b;
	public:
		ordered_pair()
		{
			a=0;
			b=0;
		}
		ordered_pair(float x,float y)
		{
			a=x;
			b=y;
		}
		float first_element()
		{
			return a;
		}
		float  second_element() 
		{
			return b;	
		}
		void output()
		{
			cout<<"("<<a<<","<<b<<")"<<endl;
		}
				
		
};

class point:public ordered_pair
{
	
	public:	
		point():ordered_pair(0,0)
		{
		}
		point(float x,float y):ordered_pair(x,y)
		{
		}
		float return_x()
		{
			return first_element();
		}
		float return_y()
		{
			return second_element();
		}
		float dist_origin()
		{
			return sqrt(first_element()*first_element()+second_element()*second_element());
		}
		float dist_point(point pt)
		{
			float x1,y1;
			x1=pt.return_x();
			y1=pt.return_y();
			return sqrt((first_element()-x1)*(first_element()-x1)+(second_element()-y1)*(second_element()-y1));
		}
		void print_point()
		{
			cout<<"("<<first_element()<<","<<second_element()<<","<<endl;	
		}

};


class complex_num:public ordered_pair
{
	public:
		complex_num(void):ordered_pair(0,0)
		{
		}
		complex_num(float x,float y):ordered_pair(x,y)
		{
		}
		float return_x()
		{
			return first_element();
		}
		float return_y()
		{
			return second_element();
		}
		complex_num conjugate()
		{
			return complex_num(first_element(),0-second_element());
		}
		complex_num operator+(complex_num add)
		{
			return complex_num(first_element()+add.return_x(),second_element()+add.return_y());
		}
		complex_num operator-(complex_num add)
		{
			return complex_num(first_element()-add.return_x(),second_element()-add.return_y());
		}
		
		void print_complex()
		{
			if(second_element()>0)	
				cout<<first_element()<<"+"<<"j"<<second_element()<<endl;
			else if(second_element()<0)
				cout<<first_element()<<"-"<<"j"<<0-second_element()<<endl;
			else
				cout<<first_element()<<endl;
		}		
};


int main()
{
	point p1(3,4);
	point p2(8,16);
	cout<<p1.dist_origin()<<endl;
	cout<<p1.dist_point(p2)<<endl;
	cout<<p2.dist_point(p1)<<endl;
	complex_num comp1(2,3);
	complex_num comp2(3,5);
	complex_num comp3(0,0);
	comp3=comp1.conjugate();
	comp3.print_complex();
	comp3=comp1+comp2;
	comp3.print_complex();
	comp3=comp1-comp2;
	comp3.print_complex();	
	
}
	


	
