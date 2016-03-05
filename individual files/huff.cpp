node huffman(vector<node> Q)
{
	node n1,n2;
	int size=Q.size(),i;
	for(i==0;i<size;i++)
	{
		n1=Q[Q.size()-1];
		Q.pop();
		n2=Q[Q.size()-1];
		Q.pop();
		node temp();
		temp.prob=n1.prob+n2.prob;
		temp.lc=&n1;
		temp.rc=&n2;
		modify(n1,0);
		modify(n2,1);
		Insert(Q,temp);
	}
	return Q[0];
	
		


}
