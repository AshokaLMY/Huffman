// ������������ ���� �洢�ṹΪ ������ʽ�ṹ
// ���д�Ź��������Ľ���ַ�����Ҫ�����µĴ���
// �ڳ�ʼ����ʱ���Ҫ���������ݶ�Ӧ�Ľ��ֱ�Ӵ�����У�
// �������˫�׽��ʱ����Ϊ˫������ռ䣬�����Ѱ�˫�׽��ĵ�ַҲ������С�
// ʹ���˶ѵĹ�ϵ�Ƚ����صķ�����ʵ�֣������ø���ԭ���ѵıȽ�ʽ��
// heap-huffman2.cpp������ø���ԭ���ѵıȽ�ʽ����ʵ��Ԫ��ֵ�ıȽϵġ�


#include<iostream>

using namespace std;

#define DefaultSize 100



struct  HuffmanNode 
{
     float data;
     HuffmanNode *leftchild, *rightchild;
     HuffmanNode *parent;
        
};

struct node
{
   float data;
   HuffmanNode *link;
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


bool operator<=( node &a, node &b)
{	if(a.data<=b.data ) return true;  else   return false;	}

bool operator>( node &a, node &b)
{	if(a.data>b.data ) return true;  else   return false;	}



template <class Type> 
MinHeap <Type> ::MinHeap ( int maxSize )
 {
//���ݸ�����СmaxSize,�����Ѷ���
    MaxHeapSize = DefaultSize < maxSize ? 
            maxSize : DefaultSize;	       //ȷ���Ѵ�С
    heap = new Type [MaxHeapSize]; //�����ѿռ�
    CurrentSize = 0;                              //��ʼ��
}

template <class Type>
 MinHeap <Type> :: MinHeap ( Type arr[ ], int n )
 {
//���ݸ��������е����ݺʹ�С,�����Ѷ���    
MaxHeapSize = DefaultSize < n ? n : DefaultSize;
    heap = new Type [MaxHeapSize]; 
    heap = arr;               //���鴫��
    CurrentSize = n;       //��ǰ�Ѵ�С
    int currentPos = (CurrentSize-2)/2;   //����Ҷ
    while ( currentPos >= 0 ) {       
    //���µ���������,�γɶ�
        FilterDown ( currentPos, CurrentSize-1 );
        //��currentPos��ʼ,��CurrentSizeΪֹ, ����
        currentPos--;				
    }
}


template <class Type> 
void MinHeap<Type> :: FilterDown ( int start, int EndOfHeap ) 
{
    int i = start,   j = 2*i+1;        // j �� i ������Ů
    Type temp = heap[i];
    while ( j <= EndOfHeap ) {
         if ( j < EndOfHeap && heap[j]> heap[j+1])  j++;    //����Ů��ѡС��
         if ( temp <= heap[j] ) break;
         else { heap[i] = heap[j];  i = j;   j = 2*j+1; }
    }
    heap[i] = temp;				
}

template <class Type> 
int MinHeap<Type> ::Insert ( const Type &x )
 {
//�ڶ��в�����Ԫ�� x
    if ( CurrentSize == MaxHeapSize )     //����
       { cout << "������" << endl;  return 0; }	
    heap[CurrentSize] = x;           //���ڱ�β  
    FilterUp (CurrentSize);          //���ϵ���Ϊ��
    CurrentSize++;                       //��Ԫ����һ
    return 1;
}

//��С�ѵ����ϵ����㷨

template <class Type> 
void MinHeap<Type> ::FilterUp ( int start ) 
{
//�� start ��ʼ,����ֱ��0,������
    int j = start,  i = (j-1)/2;    // i �� j ��˫��
    Type temp = heap[j];
    while ( j > 0 ) {      
        if ( heap[i] <= temp ) break;
        else {  heap[j] = heap[i];  j = i;  i = (i -1)/2; }
    }
    heap[j] = temp;
}


template <class Type> 
int MinHeap <Type> ::RemoveMin ( Type &x )
 {
    if ( !CurrentSize )
      { cout <<"���ѿ�" << endl;  return 0; }
    x = heap[0];             //��СԪ�س�����
    heap[0] = heap[CurrentSize-1];	    
    CurrentSize--;        //����СԪ���
    FilterDown ( 0, CurrentSize-1 );
    //��0��λ�ÿ�ʼ�Զ����µ���Ϊ��
    return 1;
}



class   HuffmanTree
{
protected:
   HuffmanNode  *root;
   void mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, node &node1);
   // �ϲ�����
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
     HuffmanTree(float w[ ], int n );  //  ������������
     ~HuffmanTree( ){ };

	 void preorder(){preorder(root);}

};



void HuffmanTree::mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, node &node1)
{    HuffmanNode *parent;

     parent=new HuffmanNode;
     parent->leftchild=ht1;
     parent->rightchild=ht2;
     parent->data = ht1->data+ht2->data;
     ht1->parent= ht2->parent=parent;

	 node1.data=parent->data;
	 node1.link=parent;


}


HuffmanTree::HuffmanTree (float w[ ] , int n )
{ 
	 MinHeap<node>  hp;
	 int i ;

     HuffmanNode  *first, *second,*work; 
     node node1;

    for ( i = 0; i < n; i++ ) 
    {
       work=new HuffmanNode;
	   work->data=w[i];
       work->leftchild =work->rightchild = work->parent=0; 
	   node1.data=w[i];
	   node1.link=work;
       hp.Insert(node1);  
    }      //���ͳ�ʼȨֵ
	for ( i = 0; i < n-1; i++ ) 
    {
         //�������������Ĺ��̣���n-1��
		hp.RemoveMin ( node1 );       //ѡ��Ȩֵ��С����
		first=node1.link;
        hp.RemoveMin ( node1 );  //ѡ��Ȩֵ��С����
		second=node1.link ;

        mergeTree( first, second,node1 ); //�ϲ�
        hp.Insert ( node1 );	     //���²��뵽С������
    }
	root=node1.link;    //���Ľ��Ϊ����� 

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


