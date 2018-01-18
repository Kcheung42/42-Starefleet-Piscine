
struct s_node
{
	int		value;
	struct s_node *left;
	struct s_node *right;
};

int recur(struct s_node *node, int *max_value)
{
	int lc;
	int rc;
	int	ret;
	
	lc = 0;
	rc = 0;
	ret = 0;
	if(!node)
		return(0);
	lc = recur(node->left, max_value);
	rc = recur(node->right, max_value);
	if (node->left->value == node->value + 1)
		lc += 1;
	if (node->right->value == node->value + 1)
		rc += 1;
	ret += (lc > rc) ? lc : rc;
	if (ret > *max_value)
		*max_value = ret;
	return (ret);
}

int	longuest_sequence(struct s_node *node)
{
	int max_val;
	if(!node)
		return (0);
	max_val = 0;
	recur(node, &max_val);
	return (max_val + 1);
}
