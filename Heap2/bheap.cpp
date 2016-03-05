#include"bheap.h"
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<time.h>
#include<string>
#include<stdio.h>
#include<sys/time.h>


vector<Node*> DECARR;
Node * gar=new Node(-99999);


using namespace std;

//void swap(Node **A,Node **B)
//{
//     Node **temp;
//     temp=B;
//     B=A;
//    A=temp;
//}

void swap(Node *a,Node *b)
{
	int temp;
	temp=a->data;
	a->data=b->data;
	b->data=temp;
}


void bheap::assign(Node *t)
{
        head=t;
}


Node* bheap::return_head()
{
        return head;
}


Node* mer(Node *n1,Node *n2)
{
    vector<Node*> b1,b2,b;
    Node *temp;
    temp=n1;
    while(temp!=NULL)
    {
        b1.push_back(temp);
        temp=temp->rsib;
    }
    temp=n2;
    while(temp!=NULL)
    {
        b2.push_back(temp);
        temp=temp->rsib;
    }
    int i=0;
    vector<Node*>::iterator it1,it2,temp_it;
    it1=b1.begin();
    it2=b2.begin();
    while(it1<b1.end()&&it2<b2.end())
    {
        if((*it1)->deg<=(*it2)->deg)
        {
            b.push_back(*it1);
            it1++;
        }
        else
        {
            b.push_back(*it2);
            it2++;
        }
    }
    if(it1==b1.end())
    {
        while(it2<b2.end())
        {
            b.push_back(*it2);
            it2++;
        }
    }
    else if(it2==b2.end())
    {
        while(it1<b1.end())
        {
            b.push_back(*it1);
            it1++;
        }
    }
    
    /*it1=b.begin();
    i=0;
    //cout<<b.size()<<endl;
    while(i<(b1.size()+b2.size()))
    {
        (*it1)->rsib=*(it1+1);
        it1++;
        i++;
    }
    //(*it1)->rsib=NULL;*/
      it1=b.begin();
      //vector<Node *> temp_it;
      //cout<<b.size()<<endl;
      i=1;
      while(i<b.size())
      {
          it1++;
          temp_it=it1;
          it1--;
          (*it1)->rsib=*(temp_it);
          i++;
          it1++;
      }
      (*it1)->rsib=NULL;

    return b.front();
 
}


Node* link(Node *n1,Node *n2)
{
        if(n1==NULL)
            return n2;
        if(n2==NULL)
            return n1;
        if(n2->child==NULL)
        {
                n1->par=n2;
		n1->rsib=NULL;
                n2->child=n1;
                n2->deg+=1;
        }
        else
        {
                n1->par=n2;
                n1->rsib=n2->child;
                n2->child=n1;
                n2->deg+=1;
        }
    return n2;

}



Node *uni(Node *n1, Node *n2)
{

	if(n1==NULL)
		return n2;
	if(n2==NULL)
		return n1;	
	bheap b;
        Nodeuni z;
        Node *head;
        head=mer(n1,n2);
	        


	z.curr=head;
	z.prev=NULL;
	z.next=z.curr->rsib;      
        
        if(head==NULL)
            return head;
        while(z.next!=NULL)
        {
		//cout<<"while"<<endl;
                if((z.curr->deg!=z.next->deg)||(z.next->rsib!=NULL&&(z.curr->deg)==(z.next->rsib->deg)))
                {
			//cout<<"if"<<endl;
                        z.prev=z.curr;
                        z.curr=z.next;
                }
                                                    
                else if(z.curr->data<=z.next->data)
                {
                        //cout<<"here"<<endl;
                        z.curr->rsib=z.next->rsib;
                        link(z.next,z.curr);
                }
                else
                {
                        if(z.prev==NULL)
                        { 
                               // cout<<"here1"<<endl;
                                head=z.next;
                        }
                        else 
                        {	
				//cout<<"wth"<<endl;
                                z.prev->rsib=z.next;
                        }
                        link(z.curr,z.next);
                        z.curr=z.next;

                }
		z.next=z.curr->rsib;
         }
         return head;

}

Node* bheap::heap_min()
{
    Node *y,*x;
    x=head;
    y=NULL;
    int min;
    min=9999999;
    while(x!=NULL)
    {
        if(x->data<min)
        {
            min=x->data;
            y=x;
        }
        x=x->rsib;
            
    }
    return y;
}


void bheap::insert(int num)
{
        Node *temp=new Node(num);
	DECARR.push_back(temp);
        bheap b(temp);
        assign(uni(head,b.return_head()));
    
}






int bheap::extract_min()
{
	int minimum=0;
	Node *ch,*min,*temp,*t;
	vector<Node*> vec;
	min=heap_min();
	minimum=min->data;
	temp=return_head();
	if(head==min)
	{
		cout<<"if"<<endl;
		head=head->rsib;
	}
	
	else
	{
		
		while(temp->rsib!=min)
		{
			cout<<"else1"<<endl;
			temp=temp->rsib;
		}
		temp->rsib=min->rsib;
	}		
	t=min->child;
	if(t==NULL)
	{
		return min->data;
	}
	else
	{
		while(t!=NULL&&t->data>min->data)
		{
			//cout<<t->data<<endl;
			cout<<"whule"<<endl;
			vec.push_back(t);
			t=t->rsib;
		}
		int len=0,i=0;
		len=vec.size();
		ch=vec.back();
		vec.pop_back();
		temp=ch;
		while(i<len-1)
		{	
			cout<<"wh"<<endl;
			temp->rsib=vec.back();
			vec.pop_back();
			temp=temp->rsib;
			i++;
		}
		temp->rsib=NULL;
	}
	cout<<"err"<<endl;
	head=uni(ch,head);
	cout<<"exit"<<endl;
	temp=head;
	while(temp!=NULL)
	{
		temp->par=NULL;
		temp=temp->rsib;
	}
	min->data=-99999;
	return minimum;
}
	

void bheap::dec_key(Node* x,int num)
{
    Node *z;
    if(x->data<num)
    {
        cout<<"error";
    }
    x->data=num;
    z=x->par;
    
    while(z!=NULL&&x->data<z->data)
    {
	//cout<<"x:"<<x->data<<endl;
	//cout<<"z:"<<z->data<<endl;
        swap(x,z);
	//cout<<"x:"<<x->data<<endl;
	//cout<<"z:"<<z->data<<endl;
        x=z;
        z=x->par;

    }
    
}


void bheap::del(int num)
{	
	Node* x;
	int i;
	for(i=0;i<DECARR.size();i++)
	{
		if(DECARR[i]!=NULL)
		{
			if(DECARR[i]->data==num)
				break;
		}
	}
	cout<<"i"<<i<<endl;
	if(i<DECARR.size())
	{
		x=DECARR[i];
    		dec_key(x,-99999);
    		i=extract_min();
	}
}


void post_order(Node *t,ofstream &fout)
{
	if(t->child!=NULL)
		post_order(t->child,fout);
	if(t->rsib!=NULL)
		post_order(t->rsib,fout);
	fout<<(t->data)<<endl;
}



int main(int argc,char *argv[])
{
	int in_arr1[200000],k;
	int in_arr2[200000],temp[200000];
	bheap bh1,bh2;
	ifstream in1(argv[2]);
	ifstream in2(argv[3]);
	ofstream out1("outputfile");
	ofstream out2("treewalk");
	vector <double> time_taken;
        double cumulative=0;
        struct timeval before,after;
        float timetaken;
	if(!in1&&!in2)
	{
		cout<<"error in opening the file"<<endl;
		return -1;
	}
	int i=1;
	string we;
        
	while(!in1.eof())                      //READING INPUT_1 INTO......................
	{
		getline(in1,we);
		istringstream x(we);
		x >> in_arr1[i];
		i++;
	}
	in_arr1[i]='\0';
	int j=1;
	for(j=1;in_arr1[j]!='\0';j++)
	{
		
		bh1.insert(in_arr1[j]);
	}
	if (argv[1][0]=='2')                   // IF ARG IS 2.........
	{
		
		i=1;
		while(!in2.eof())
		{
			getline(in2,we);       //READING INPUT_2 IN HEAP2
			istringstream x(we);
			x >> in_arr2[i];
			i++;
		}
		in_arr2[i]='\0';
		for(j=1;in_arr2[j]!='\0';j++)
	        {
        	        bh2.insert(in_arr2[j]);
        	}
                gettimeofday(&before, NULL);
		bh1.assign(uni(bh2.return_head(),bh1.return_head()));
                gettimeofday(&after, NULL);
                timetaken=((after.tv_sec-before.tv_sec)*1000.0) + (0.001 * (after.tv_usec - before.tv_usec));
                

                k=0;
		
                post_order(bh1.return_head(),out2);
		out2<<endl;
                //out2<<endl;
		out2<<"time for meld : "<<endl; //PRITING TIME TAKEN IN MilliSeconds  
		out2<<timetaken;
                //out1<<"ms"<<endl;
                
	}
	if(argv[1][0]=='1')                       //IF ARG IS 1.................
	{	
		string s;
		char sp[200];
		int num,i=1,j;
		getline(in2,s);
    //            gettimeofday(&before, NULL);
                timetaken=0;
                int count=1;
		while(!in2.eof()&&(s[0]=='+'||s[0]=='-'))     //READING LINE BY LINE AND DOING CORREPONDING OPRATION
		{
			cout<<"insert"<<endl;
			if(s[0]=='+')
			{
				getline(in2,s);
				j=0;
				int len_s=s.size();
				while(j<len_s)
				{
					sp[j]=s[j];
					j++;
				}	
				sp[j]='\0';	
                                gettimeofday(&before,NULL);
				num=atoi(sp);
				bh1.insert(num);
                                gettimeofday(&after, NULL);
                                timetaken+=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));

				
			}
			
			else if(s[0]=='-')
			{
				out1<<i<<")"<<endl;
				i++;
                                gettimeofday(&before,NULL);
				out1<<bh1.extract_min()<<endl;
                                gettimeofday(&after, NULL);
                                timetaken+=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));

			}	
			getline(in2,s);		

		}
  //              gettimeofday(&after, NULL);
  //             timetaken=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));

		out1<<"time for all operations : "<<endl;
		out1<<timetaken;//<<"sec"<<endl;
		post_order(bh1.return_head(),out2);
     
	}
	return -1;
}


/*
int main()
{
        bheap bh1,bh2;
        Node *temp;
        bh1.insert(5);
        bh1.insert(10);
        bh1.insert(6);
        bh1.insert(9);
        bh2.insert(2);
        bh2.insert(4);
        bh2.insert(7);
	
	//cout<<bh2.return_head()->deg<<endl;
        //bh2.insert(3);
        bh1.assign(uni(bh2.return_head(),bh1.return_head()));
	/*cout<<bh1.return_head()->deg<<endl;
        if(bh1.return_head()==NULL)
		cout<<"err"<<endl;
        //cout<<temp->deg<<endl;
        //cout<<temp->child->deg<<endl;
        cout<<"height"<<bh1.return_head()->deg<<endl;
	cout<<"extract"<<endl;
        cout<<"extract1 "<<bh1.extract_min()<<endl;
	cout<<"min"<<bh1.heap_min()->data<<endl;
	cout<<"extract2"<<bh1.extract_min()<<endl;
      //  cout<<bh1.extract_min()<<endl;
        cout<<"min"<<bh1.heap_min()->data<<endl;
        cout<<bh1.extract_min()<<endl;
	//cout<<bh1.extract_min()<<endl;
	//cout<<"min"<<bh1.heap_min()->data<<endl;
	temp=bh1.return_head();
	while(temp!=NULL)
        {
                cout<<"temp"<<temp->deg<<endl;
                temp=temp->rsib;
        }
        
        if(bh1.return_head()==NULL)
                cout<<"it is null"<<endl;
        //cout<<bh1.return_head()->data<<endl;
//        cout<<"min:"<<bh1.heap_min()->data<<endl;
	
	//cout<<"asdf"<<bh1.return_head()->rsib->child->rsib->data<<endl;
	//cout<<"extract1 "<<bh1.extract_min()<<endl;
	//cout<<"extract1 "<<bh1.extract_min()<<endl;
	//cout<<"extract1 "<<bh1.extract_min()<<endl;
	cout<<"extract1 "<<bh1.extract_min()<<endl;
	//cout<<bh1.return_head()->child->data<<endl;
	bh1.del(2);
	//bh1.del(5);
	post_order(bh1.return_head());
        return -1;
}
*/
