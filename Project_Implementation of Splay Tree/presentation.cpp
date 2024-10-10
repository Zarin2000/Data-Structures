#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct node
{
   int data;
   node* left;
   node* right;
};

class SplayTree
{
   public:
   node* RR_Rotate(node* k2)
   {
      node* k1 = k2->left;
      k2->left = k1->right;
      k1->right = k2;
      return k1;
   }
   node* LL_Rotate(node* k2)
   {
      node* k1 = k2->right;
      k2->right = k1->left;
      k1->left = k2;
      return k1;
   }
   node* Splay(int key, node* root)
   {
      if (!root)
      return NULL;
      node header;
      header.left= header.right = NULL;
      node* LeftTree = &header;
      node* RightTree = &header;
      while (1)
      {
         if (key < root->data)
         {
            if (!root->left)
            break;
            if (key< root->left->data)
            {
               root = RR_Rotate(root);
               if (!root->left)
               break;
            }
            RightTree->left= root;
            RightTree = RightTree->left;
            root = root->left;
            RightTree->left = NULL;
         }
         else if (key> root->data)
         {
            if (!root->right)
            break;
            if (key > root->right->data)
            {
               root = LL_Rotate(root);
               if (!root->right)
               break;
            }
            LeftTree->right= root;
            LeftTree = LeftTree->right;
            root = root->right;
            LeftTree->right = NULL;
         }
         else
         break;
      }
      LeftTree->right = root->left;
      RightTree->left = root->right;
      root->left = header.right;
      root->right = header.left;
      return root;
   }
   node* New_Node(int key)
   {
      node* p_node = new node;
      if (!p_node)
      {
         fprintf(stderr, "Out of memory!\n");
         exit(1);
      }
      p_node->data = key;
      p_node->left = p_node->right = NULL;
      return p_node;
   }
   node* Insert(int key, node* root)
   {
      static node* p_node = NULL;
      if (!p_node)
      p_node = New_Node(key);
      else
      p_node->data = key;
      if (!root)
      {
         root = p_node;
         p_node = NULL;
         return root;
      }
      root = Splay(key, root);
      if (key < root->data)
      {
         p_node->left= root->left;
         p_node->right = root;
         root->left = NULL;
         root = p_node;
      }
      else if (key > root->data)
      {
         p_node->right = root->right;
         p_node->left = root;
         root->right = NULL;
         root = p_node;
      }
      else
      return root;
      p_node = NULL;
      return root;
   }
   node* Delete(int key, node* root)
   {
      node* temp;
      if (!root)
      return NULL;
      root = Splay(key, root);
      if (key != root->data)
      return root;
      else
      {
         if (!root->left)
         {
            temp = root;
            root = root->right;
         }
         else
         {
            temp = root;
            root = Splay(key, root->left);
            root->right = temp->right;
         }
         free(temp);
         return root;
      }
   }
   node* Search(int key, node* root)
   {
      return Splay(key, root);
   }
   void InOrder(node* root)
   {
      if (root)
      {
         InOrder(root->left);
         cout<< "key: " <<root->data;
         if(root->left)
         cout<< " | left child: "<< root->left->data;
         if(root->right)
         cout << " | right child: " << root->right->data;
         cout<< "\n";
         InOrder(root->right);
      }
   }
};
int main()
{
   SplayTree st;
   node *root;
   root = NULL;
   st.InOrder(root);
   int i, choice;
   while(1)
   {
      cout<<"1. Insert "<<endl;
      cout<<"2. Delete"<<endl;
      cout<<"3. Search"<<endl;
      cout<<"4. Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>choice;
      switch(choice)
      {
         case 1:
            cout<<"Enter value to be inserted: ";
            cin>>i;
            root = st.Insert(i, root);
            cout<<"\nAfter Insert: "<<i<<endl;
            st.InOrder(root);
            break;
         case 2:
            cout<<"Enter value to be deleted: ";
            cin>>i;
            root = st.Delete(i, root);
            cout<<"\nAfter Delete: "<<i<<endl;
            st.InOrder(root);
            break;
         case 3:
            cout<<"Enter value to be searched: ";
            cin>>i;
            root = st.Search(i, root);
            cout<<"\nAfter Search "<<i<<endl;
            st.InOrder(root);
            break;
         case 4:
            exit(1);
         default:
            cout<<"\nInvalid type! \n";
      }
   }
   cout<<"\n";
   return 0;
}
