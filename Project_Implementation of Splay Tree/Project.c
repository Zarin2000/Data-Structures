#include <stdio.h>
#include <stdlib.h>

typedef struct node {
int data;
struct node *left;
struct node *right;
struct node *parent;
}node;

typedef struct splay_tree {
struct node *root;
}splay_tree;

node* new_node(int data) {
node *n = malloc(sizeof(node));
n->data = data;
n->parent = NULL;
n->right = NULL;
n->left = NULL;

return n;
}

splay_tree* new_splay_tree() {
splay_tree *t = malloc(sizeof(splay_tree));
t->root = NULL;

return t;
}

node* maximum(splay_tree *t, node *x) {
while(x->right != NULL)
  x = x->right;
return x;
}

void left_rotate(splay_tree *t, node *x) {
node *y = x->right;
x->right = y->left;
if(y->left != NULL) {
  y->left->parent = x;
}
y->parent = x->parent;
if(x->parent == NULL) {
  t->root = y;
}
else if(x == x->parent->left) {
  x->parent->left = y;
}
else {
  x->parent->right = y;
}
y->left = x;
x->parent = y;
}

void right_rotate(splay_tree *t, node *x) {
node *y = x->left;
x->left = y->right;
if(y->right != NULL) {
  y->right->parent = x;
}
y->parent = x->parent;
if(x->parent == NULL) {
  t->root = y;
}
else if(x == x->parent->right) {
  x->parent->right = y;
}
else {
  x->parent->left = y;
}
y->right = x;
x->parent = y;
}

void splay(splay_tree *t, node *n) {
while(n->parent != NULL) {
  if(n->parent == t->root) {
    if(n == n->parent->left) {
      right_rotate(t, n->parent);
    }
    else {
      left_rotate(t, n->parent);
    }
  }
  else {
    node *p = n->parent;
    node *g = p->parent;

    if(n->parent->left == n && p->parent->left == p) {
      right_rotate(t, g);
      right_rotate(t, p);
    }
    else if(n->parent->right == n && p->parent->right == p) {
      left_rotate(t, p);
    }
    else if(n->parent->right == n && p->parent->left == p) {
      left_rotate(t, p);
      right_rotate(t, g);
    }
    else if(n->parent->left == n && p->parent->right == p) {
      right_rotate(t, p);
      left_rotate(t, g);
    }
  }
}
}

void insert(splay_tree *t, node *n) {
node *y = NULL;
node *temp = t->root;
while(temp != NULL) {
  y = temp;
  if(n->data < temp->data)
    temp = temp->left;
  else
    temp = temp->right;
}
n->parent = y;

if(y == NULL)
  t->root = n;
else if(n->data < y->data)
  y->left = n;
else
  y->right = n;

splay(t, n);
}

node* search(splay_tree *t, node *n, int x) {
if(x == n->data) {
  splay(t, n);
  return n;
}
else if(x < n->data)
  return search(t, n->left, x);
else if(x > n->data)
  return search(t, n->right, x);
else
  return NULL;
}

void delete(splay_tree *t, node *n) {
splay(t, n);

splay_tree *left_subtree = new_splay_tree();
left_subtree->root = t->root->left;
if(left_subtree->root != NULL)
  left_subtree->root->parent = NULL;

splay_tree *right_subtree = new_splay_tree();
right_subtree->root = t->root->right;
if(right_subtree->root != NULL)
  right_subtree->root->parent = NULL;

free(n);

if(left_subtree->root != NULL) {
  node *m = maximum(left_subtree, left_subtree->root);
  splay(left_subtree, m);
  left_subtree->root->right = right_subtree->root;
  t->root = left_subtree->root;
}
else {
  t->root = right_subtree->root;
}
}

void inorder(splay_tree *t, node *n) {
if(n != NULL) {
  if(n){
  inorder(t, n->left);
  printf("key: %d", n->data);
  if(n->left)
  printf(" | left child: %d", n->left->data);
    if(n->right)
    printf(" | right child: %d", n->right->data);
    printf("\n");
  inorder(t, n->right);

  }
}
}

int main() {
splay_tree *t = new_splay_tree();

node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
a = new_node(1);
b = new_node(2);
c = new_node(3);
d = new_node(10);
e = new_node(9);
f = new_node(4);
g = new_node(5);
h = new_node(6);
i = new_node(7);
j = new_node(8);
k = new_node(15);
l = new_node(11);
m = new_node(12);

insert(t, a);
insert(t, b);
insert(t, c);
insert(t, d);
insert(t, e);
insert(t, f);
insert(t, g);
insert(t, h);
insert(t, i);
insert(t, j);
insert(t, k);
insert(t, l);
insert(t, m);

//delete(t, a);
//delete(t, m);//
search(t,e,9);
inorder(t, t->root);

return 0;
}
