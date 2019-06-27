
// heap-Huffman2.cpp的基础上增加的功能：

// 在建立的哈夫曼树中获取各个字符的编码以及对输入文字串进行二进制编码。
// 该程序暂无解码功能，请补充完善。



// 原heap-Huffman2.cpp的设计方案：
// 哈夫曼建立树 —— 存储结构为 三叉链式结构
// 堆中存放哈夫曼树的结点地址，因此要做如下的处理。
// 在初始化的时候就要把所有数据对应的结点直接存入堆中，
// 当计算出双亲结点时，就为双亲申请空间，并最后把把双亲结点的地址也填入堆中。

// 由于没有使用堆的关系比较重载，因此采用直接更改原来堆的比较式子来实现元素值的比较的。
// 所以堆的插入以及操作操作中的<= 以及 >  的关系比较式子中都多加了 ->data 



#include<iostream>
#include<string.h>

using namespace std;


#define DefaultSize 100

struct  HuffmanNode 
{
     float data;
     HuffmanNode *leftchild, *rightchild;
     HuffmanNode *parent;
        
};

struct  infoNode 
{
     float data;  // 保存字符的权值
	 char info;   // 保存该字符信息
     HuffmanNode *address; // 保存该字符在哈夫曼树中的结点地址
     char code[20];   // 保存该字符对应的二进制编码
};


template <class Type>
class MinHeap
{		
public: 
     MinHeap ( int maxSize=DefaultSize );
     MinHeap ( Type arr[ ], int n );
     ~MinHeap ( ) { delete [ ] heap; }
     const MinHeap<Type> & operator = 
          ( const MinHeap &R );	
     int Insert ( const Type &x );
     int RemoveMin ( Type &x );     
     int IsEmpty ( ) const 
            { return CurrentSize == 0; }
     int IsFull ( ) const
            { return CurrentSize == MaxHeapSize; }
     void MakeEmpty ( ) { CurrentSize = 0; }
private: 
    Type *heap;                 			
    int CurrentSize;				
    int MaxHeapSize;
    void FilterDown ( int i, int m );
    void FilterUp ( int i );
}; 	

template <class Type> 
MinHeap <Type> ::MinHeap ( int maxSize )
 {
//根据给定大小maxSize,建立堆对象
    MaxHeapSize = DefaultSize < maxSize ? 
            maxSize : DefaultSize;	       //确定堆大小
    heap = new Type [MaxHeapSize]; //创建堆空间
    CurrentSize = 0;                              //初始化
}

template <class Type>
 MinHeap <Type> :: MinHeap ( Type arr[ ], int n )
 {
//根据给定数组中的数据和大小,建立堆对象    
MaxHeapSize = DefaultSize < n ? n : DefaultSize;
    heap = new Type [MaxHeapSize]; 
    heap = arr;               //数组传送
    CurrentSize = n;       //当前堆大小
    int currentPos = (CurrentSize-2)/2;   //最后非叶
    while ( currentPos >= 0 ) {       
    //从下到上逐步扩大,形成堆
        FilterDown ( currentPos, CurrentSize-1 );
        //从currentPos开始,到CurrentSize为止, 调整
        currentPos--;				
    }
}


template <class Type> 
void MinHeap<Type> :: FilterDown ( int start, int EndOfHeap ) 
{
    int i = start,   j = 2*i+1;        // j 是 i 的左子女
    Type temp = heap[i];
    while ( j <= EndOfHeap ) {
         if ( j < EndOfHeap && heap[j]->data >
            heap[j+1]->data)  j++;    //两子女中选小者
         if ( temp->data <= heap[j]->data ) break;
         else { heap[i] = heap[j];  i = j;   j = 2*j+1; }
    }
    heap[i] = temp;				
}

template <class Type> 
int MinHeap<Type> ::Insert ( const Type &x )
 {
//在堆中插入新元素 x
    if ( CurrentSize == MaxHeapSize )     //堆满
       { cout << "堆已满" << endl;  return 0; }	
    heap[CurrentSize] = x;           //插在表尾  
    FilterUp (CurrentSize);          //向上调整为堆
    CurrentSize++;                       //堆元素增一
    return 1;
}

//最小堆的向上调整算法

template <class Type> 
void MinHeap<Type> ::FilterUp ( int start ) 
{
//从 start 开始,向上直到0,调整堆
    int j = start,  i = (j-1)/2;    // i 是 j 的双亲
    Type temp = heap[j];
    while ( j > 0 ) {      
        if ( heap[i]->data <= temp->data ) break;
        else {  heap[j] = heap[i];  j = i;  i = (i -1)/2; }
    }
    heap[j] = temp;
}


template <class Type> 
int MinHeap <Type> ::RemoveMin ( Type &x )
 {
    if ( !CurrentSize )
      { cout <<"堆已空" << endl;  return 0; }
    x = heap[0];             //最小元素出队列
    heap[0] = heap[CurrentSize-1];	    
    CurrentSize--;        //用最小元素填补
    FilterDown ( 0, CurrentSize-1 );
    //从0号位置开始自顶向下调整为堆
    return 1;
}



class   HuffmanTree
{
protected:
   HuffmanNode  *root;
   void mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, HuffmanNode *&parent);
   // 合并操作
   void preorder(HuffmanNode  *t)  // 前序遍历，一个测试函数
   {
	   if ( t )
	   {
		   cout<<t->data<<" ";
		   preorder(t->leftchild);
		   preorder(t->rightchild);
	   }
   }
 public:
     HuffmanTree(infoNode w[ ], int n );  //  建立哈夫曼树
	 void GetCode (infoNode w[ ] , int n );  // 获取每个符号的编码
	 void Coding(infoNode w[],int n );   // 对输入文字串进行二进制编码
     ~HuffmanTree( ){ };

	 void preorder(){preorder(root);}

};



void HuffmanTree::mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, HuffmanNode *&parent)
{
     parent=new HuffmanNode;
     parent->leftchild=ht1;
     parent->rightchild=ht2;
     parent->data = ht1->data+ht2->data;
     ht1->parent= ht2->parent=parent;

}


HuffmanTree::HuffmanTree (infoNode w[ ] , int n )
{ 
	 MinHeap<HuffmanNode*>  hp;
	 int i ;

     HuffmanNode *parent , *first, *second,*work; 
     
    for ( i = 0; i < n; i++ ) 
    {
       work=new HuffmanNode;
       work->data=w[i].data;
	   work->leftchild =work->rightchild = work->parent=0; 
       hp.Insert(work);  
	   w[i].address=work;  // 保存哈夫曼结点地址
    }      //传送初始权值
	for ( i = 0; i < n-1; i++ ) 
    {
         //建立哈夫曼树的过程，做n-1趟
		hp.RemoveMin ( first );       //选根权值最小的树
        hp.RemoveMin ( second );  //选根权值次小的树

        mergeTree( first, second,parent ); //合并
        hp.Insert ( parent );	     //重新插入到小根堆中
    }
	root=parent;    //最后的结点为根结点 
  
	root->parent=0;  
   //preorder(root);
}



void HuffmanTree::GetCode (infoNode w[ ] , int n )
{
   int i;
   HuffmanNode *p;

  for (i=0;i<n;i++)    //   从这里开始的两个for循环语句代码可以优化，让效率更高，请自行完成
   {
       strcpy(w[i].code,"");   
	   p=w[i].address;
	   while(p->parent)     // 获取符号的编码
	   {
		   if (p->parent->leftchild==p)
		       strcat(w[i].code,"0");
		   else 
			   strcat(w[i].code,"1");

		   p=p->parent;
	   }
   }
   for (i=0;i<n;i++)  //  字符编码逆置
   {  
	  char temp;
	  int len=strlen(w[i].code);
	  for(int j=0;j<len/2;j++)
	  {
         temp=w[i].code[j];
		 w[i].code[j]=w[i].code[len-j-1];
         w[i].code[len-j-1]=temp;
	  }      
   }


   for (i=0;i<n;i++)  // 输出编码
   {
	   cout<<w[i].info<<":";
       cout<<w[i].code<<endl;
   }
}


void HuffmanTree::Coding (infoNode w[ ] , int n )
{
	char str[255]; 
	int i,j;

	cout<<"输入要编码的文字串:";
	cin>>str;
    
	i=0;
	cout<<"文字串对应的二进制编码:";
	while(str[i]!='\0')
	{
   	   for(j=0;j<n;j++)  //  这个代码可以优化，让效率更高，请自行完成
	   {
          if(w[j].info==str[i])
		  {	 cout<<w[j].code; break; }
	   }
	   if(j==n) { cout<<endl<<"文字串中有非法字符:"<<str[i]<<endl; return ; }
	  i++;
	  
	}
	cout<<endl;
}


void main( )
{
   int i,n;
   infoNode mydata[100];

   cout<<"字符总数:";
   cin>>n;
   for(i=0;i<n;i++)
   {
	   cout<<endl<<"字符:";  cin>>mydata[i].info;
	   cout<<"权值:";  cin>>mydata[i].data;
   }
 
   HuffmanTree MyTree(mydata,n);  // 建立哈夫曼树

   cout<<endl<<"哈夫曼树的前序遍历结果：";
   MyTree.preorder(); // 测试哈夫曼树建立是否正确
   cout<<endl;

   MyTree.GetCode ( mydata,n );  // 获取对应符号的编码

   MyTree.Coding(mydata,n);  // 对输入的文字串进行二进制编码

   cin>>n;
}


