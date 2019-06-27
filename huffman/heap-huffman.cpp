// 哈夫曼建立树 —— 存储结构为 三叉链式结构
// 堆中只存放数据，因此要做如下的处理。
// 要做结点空间的申请，然后才从堆中取出最小以及次小值之后，并放入结点空间中。
// 当计算出双亲结点时，也只是把双亲结点的值填入堆中。


#include<iostream>

using namespace std;


#define DefaultSize 100

struct  HuffmanNode 
{
     float data;
     HuffmanNode *leftchild, *rightchild;
     HuffmanNode *parent;
        
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
         if ( j < EndOfHeap && heap[j].data >
            heap[j+1].data)  j++;    //两子女中选小者
         if ( temp.data <= heap[j].data ) break;
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
        if ( heap[i].data <= temp.data ) break;
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
   void mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, HuffmanNode &parent);
   // 合并操作
   void preorder(HuffmanNode  *t)
   {
	   if ( t )
	   {
		   cout<<t->data<<"   ";
		   preorder(t->leftchild);
		   preorder(t->rightchild);
	   }
   }
 public:
     HuffmanTree(float w[ ], int n );  //  建立哈夫曼树
     ~HuffmanTree( ){ };

	 void preorder(){preorder(root);}

};



void HuffmanTree::mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, HuffmanNode &parent)
{
//     parent=new HuffmanNode;
     parent.leftchild=ht1;
     parent.rightchild=ht2;
     parent.data = ht1->data+ht2->data;
//     ht1.parent= ht2.parent=parent;

}


HuffmanTree::HuffmanTree (float w[ ] , int n )
{ 
	 MinHeap<HuffmanNode>  hp;
	 int i ;

     HuffmanNode parent , *first, *second,work; 
     
    for ( i = 0; i < n; i++ ) 
    {
       work.data=w[i];
       work.leftchild =work.rightchild = work.parent=0; 
       hp.Insert(work);  
    }      //传送初始权值
	for ( i = 0; i < n-1; i++ ) 
    {
         //建立哈夫曼树的过程，做n-1趟
		first=new HuffmanNode;
		second=new HuffmanNode;
		hp.RemoveMin ( *first );       //选根权值最小的树
        hp.RemoveMin ( *second );  //选根权值次小的树

		if (first->leftchild)  first->leftchild ->parent =first;
		if (second->leftchild) second->leftchild ->parent =second;
        mergeTree( first, second,parent ); //合并
        hp.Insert ( parent );	     //重新插入到小根堆中
    }
    root=new HuffmanNode;
	*root=parent;    //最后的结点为根结点 

   //preorder(root);
}


void main( )
{
   int i,n;
   float mydata[100];

   cin>>n;
   for(i=0;i<n;i++)
	   cin>>mydata[i];
 
   HuffmanTree MyTree(mydata,n); 

   MyTree.preorder(); 

}


