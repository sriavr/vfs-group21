bool NaryTree::IsEmpty() const
{
	return key=0;
}
Object& NaryTree::Key() const
{
	if(IsEmpty())
		throw domain_error("invalid operation");
	return *key;
}

void NaryTree::AttachKey(Object& object)
{
	if(!IsEmpty())
		throw domain_error("invalid operation");
	key=&object;
	subtree.SetLength(degree);
	for(unsigned int i=0;i<degree;++i)
		subtree[i]=new NaryTree(degree);
}

Object& NaryTree::DetachKey()
{
	if(!IsLeaf())
		throw domain_error("invalid operation");
	Object& result=*key;
	key=0;
	for(unsigned int i=0;i<degree;++i)
		delete subtree[i];
	subtree.SetLength(0);
	return result;
}
