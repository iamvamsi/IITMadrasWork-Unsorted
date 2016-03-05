node::node(){
	prev=NULL;
	next=NULL;
};
node::node(int a){
	data=a;
};
void node::set_prev(node *Node){
	prev=Node;
	};
void node::set_next(node *Node){
	next=Node;
};
node *node::next_node(){
	return next;
}
node *node::prev_node(){
	return prev;
}
int node::value(){
	return data;
}
void node::print(){
	cout<<data<<endl;
};
dll::dll(){
	Head=NULL;
	Tail=NULL;
};
void dll::insert_tail(node *Node){
	if(Tail!=NULL){
		Tail->set_next(Node);
		Node->set_prev(Tail);
		Node->set_next(NULL);
		Tail=Node;
	}
	else{
		Head=Node;
		Tail=Node;
	}
		
};
void dll:: print(){
		node *curr=Head;
		while(curr!=NULL){
			curr->print();
			curr=curr->next_node();
		}
};
