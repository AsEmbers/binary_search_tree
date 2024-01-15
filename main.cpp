#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 二叉搜索树：
 * 读取10个元素 87  7 60 80 59 34 86 99 21  3，
 * 然后建立二叉查找树，中序遍历输出3  7 21 34 59 60 80 86 87 99，
 * 针对有序后的元素，存入一个长度为10的数组中，通过折半查找找到21的下标（下标为2），然后输出2
 */

//树结点定义
typedef int BiElemType;
typedef struct BiTreeNode
{
    BiElemType data;
    struct BiTreeNode *left_node;
    struct BiTreeNode *right_node;
}BiTreeNode,*BiTree;

//二叉查找树
bool binary_search_tree(BiTree &tree,BiElemType element)
{
    if(NULL==tree)//tree会在后续插入元素过程中不断改变为新结点
    {
        tree=(BiTreeNode*)malloc(sizeof(BiTreeNode));
        tree->data=element;
        tree->left_node=tree->right_node=NULL;//每次新结点的左右结点会成为下一次待插入元素的新结点，因此赋值为NULL
        return true;
    }
    if(element==tree->data)
    {
        return false;
    }
    else if(element<tree->data)
    {
        return binary_search_tree(tree->left_node,element);
    }
    if(element>tree->data)
    {
        return binary_search_tree(tree->right_node,element);
    }
}

//创建二叉树
void create_binary_tree(BiTree &tree,BiElemType &element,int len)
{
    for(int i=0;i<len;i++)
    {
        scanf("%d",&element);
        binary_search_tree(tree,element);
    }
}

//随机数生成创建二叉树
void create_binary_tree_by_rand(BiTree &tree,BiElemType &element,int len)
{
    srand(time(NULL));
    int i=0;
    bool flag;
    while(i<len)
    {
        element=rand()%100;
        flag=binary_search_tree(tree,element);
        if(flag) i++;
    }
}

//查找元素
BiTreeNode* search_tree_node(BiTree tree,BiElemType element,BiTree &parent)
{
    if(NULL!=tree)
    {
        if(element==tree->data)
        {
            return tree;
        }
        parent=tree;
        if(element<tree->data)
        {
            search_tree_node(tree->left_node,element,parent);
        }
        else if(element>tree->data)
        {
            search_tree_node(tree->right_node,element,parent);
        }else{
            return NULL;
        }
    }
}

//中序遍历二叉树
void InOrder(BiTree tree)
{
    if(NULL!=tree)
    {
        InOrder(tree->left_node);
        printf("%3d",tree->data);
        InOrder(tree->right_node);
    }
}

//放入数组中
void move(BiTree tree,BiElemType *arr)
{
    static int i=0;
    if(NULL!=tree)
    {
        move(tree->left_node,arr);
        arr[i++]=tree->data;
        move(tree->right_node,arr);
    }
}

//打印数组
void printf_arr(BiElemType *arr,int len)
{
    printf("arr{");
    for (int i=0;i<len;i++) {
        printf("%-3d",arr[i]);
    }
    printf("}\n");
}

//折半查找，或二分查找
int binary_search(BiElemType *arr,int len,BiElemType element)
{
    int low=0,high=len-1,mid;
    while (low<high)
    {
        mid=(low+high)/2;
        if(element==arr[mid])
        {
            return mid;
        }
        else if(element>arr[mid])
        {
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}

bool delete_node(BiTree &root,BiElemType element)
{
    if(NULL==root)
    {
        return false;
    }
    if(element<root->data)
    {
        delete_node(root->left_node,element);
    }
    else if(element>root->data)
    {
        delete_node(root->right_node,element);
    }
    else if(element==root->data)
    {
        if(NULL==root->left_node)
        {
            BiTreeNode *temp_node=root;
            root=root->right_node;
            free(temp_node);
        }
        else if(NULL==root->right_node)
        {
            BiTreeNode *temp_node=root;
            root=root->left_node;
            free(temp_node);
        }
        else
        {
            BiTreeNode *temp_node=root->left_node;
            while (NULL!=temp_node->right_node)
            {
                temp_node=temp_node->right_node;
            }
            root->data=temp_node->data;
            delete_node(root->left_node,temp_node->data);
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main() {
    int len=10;
    BiElemType element;
    BiTree tree=NULL;//初始化树，即树根结点
    bool flag=false;
    create_binary_tree(tree,element,len);//创建二叉树 87  7 60 80 59 34 86 99 21  3
//    create_binary_tree_by_rand(tree,element,len);//随机数生成创建二叉树
    InOrder(tree);//中序遍历
    printf("\n");
    BiTreeNode *search_result=NULL,*parent=NULL;//根节点没有父节点，因此初始化为NULL
    search_result=search_tree_node(tree,21,parent);//递归查找元素
    if(NULL!=search_result)
    {
        printf("search_result node data=%d\n",search_result->data);
    }
    if(NULL!=parent)
    {
        printf("parent node data=%d\n",parent->data);
    }
    BiElemType arr[10]={0};
    move(tree,arr);//移动元素进入数组
    printf_arr(arr,len);
    int index=-1;
    index=binary_search(arr,10,21);//折半查找
    if(0<=index)
    {
        printf("%d\n",index);
    }
    flag=delete_node(tree,60);
    if(flag)
    {
        InOrder(tree);
    }
    fflush(stdout);
    return 0;
}
