
// heap-Huffman2.cpp�Ļ��������ӵĹ��ܣ�

// �ڽ����Ĺ��������л�ȡ�����ַ��ı����Լ����������ִ����ж����Ʊ��롣
// �ó������޽��빦�ܣ��벹�����ơ�



// ԭheap-Huffman2.cpp����Ʒ�����
// ������������ ���� �洢�ṹΪ ������ʽ�ṹ
// ���д�Ź��������Ľ���ַ�����Ҫ�����µĴ���
// �ڳ�ʼ����ʱ���Ҫ���������ݶ�Ӧ�Ľ��ֱ�Ӵ�����У�
// �������˫�׽��ʱ����Ϊ˫������ռ䣬�����Ѱ�˫�׽��ĵ�ַҲ������С�

// ����û��ʹ�öѵĹ�ϵ�Ƚ����أ���˲���ֱ�Ӹ���ԭ���ѵıȽ�ʽ����ʵ��Ԫ��ֵ�ıȽϵġ�
// ���ԶѵĲ����Լ����������е�<= �Լ� >  �Ĺ�ϵ�Ƚ�ʽ���ж������ ->data 



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
     float data;  // �����ַ���Ȩֵ
	 char info;   // ������ַ���Ϣ
     HuffmanNode *address; // ������ַ��ڹ��������еĽ���ַ
     char code[20];   // ������ַ���Ӧ�Ķ����Ʊ���
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
         if ( j < EndOfHeap && heap[j]->data >
            heap[j+1]->data)  j++;    //����Ů��ѡС��
         if ( temp->data <= heap[j]->data ) break;
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
        if ( heap[i]->data <= temp->data ) break;
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
   void mergeTree(HuffmanNode *ht1, HuffmanNode *ht2, HuffmanNode *&parent);
   // �ϲ�����
   void preorder(HuffmanNode  *t)  // ǰ�������һ�����Ժ���
   {
	   if ( t )
	   {
		   cout<<t->data<<" ";
		   preorder(t->leftchild);
		   preorder(t->rightchild);
	   }
   }
 public:
     HuffmanTree(infoNode w[ ], int n );  //  ������������
	 void GetCode (infoNode w[ ] , int n );  // ��ȡÿ�����ŵı���
	 void Coding(infoNode w[],int n );   // ���������ִ����ж����Ʊ���
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
	   w[i].address=work;  // �������������ַ
    }      //���ͳ�ʼȨֵ
	for ( i = 0; i < n-1; i++ ) 
    {
         //�������������Ĺ��̣���n-1��
		hp.RemoveMin ( first );       //ѡ��Ȩֵ��С����
        hp.RemoveMin ( second );  //ѡ��Ȩֵ��С����

        mergeTree( first, second,parent ); //�ϲ�
        hp.Insert ( parent );	     //���²��뵽С������
    }
	root=parent;    //���Ľ��Ϊ����� 
  
	root->parent=0;  
   //preorder(root);
}



void HuffmanTree::GetCode (infoNode w[ ] , int n )
{
   int i;
   HuffmanNode *p;

  for (i=0;i<n;i++)    //   �����￪ʼ������forѭ������������Ż�����Ч�ʸ��ߣ����������
   {
       strcpy(w[i].code,"");   
	   p=w[i].address;
	   while(p->parent)     // ��ȡ���ŵı���
	   {
		   if (p->parent->leftchild==p)
		       strcat(w[i].code,"0");
		   else 
			   strcat(w[i].code,"1");

		   p=p->parent;
	   }
   }
   for (i=0;i<n;i++)  //  �ַ���������
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


   for (i=0;i<n;i++)  // �������
   {
	   cout<<w[i].info<<":";
       cout<<w[i].code<<endl;
   }
}


void HuffmanTree::Coding (infoNode w[ ] , int n )
{
	char str[255]; 
	int i,j;

	cout<<"����Ҫ��������ִ�:";
	cin>>str;
    
	i=0;
	cout<<"���ִ���Ӧ�Ķ����Ʊ���:";
	while(str[i]!='\0')
	{
   	   for(j=0;j<n;j++)  //  �����������Ż�����Ч�ʸ��ߣ����������
	   {
          if(w[j].info==str[i])
		  {	 cout<<w[j].code; break; }
	   }
	   if(j==n) { cout<<endl<<"���ִ����зǷ��ַ�:"<<str[i]<<endl; return ; }
	  i++;
	  
	}
	cout<<endl;
}


void main( )
{
   int i,n;
   infoNode mydata[100];

   cout<<"�ַ�����:";
   cin>>n;
   for(i=0;i<n;i++)
   {
	   cout<<endl<<"�ַ�:";  cin>>mydata[i].info;
	   cout<<"Ȩֵ:";  cin>>mydata[i].data;
   }
 
   HuffmanTree MyTree(mydata,n);  // ������������

   cout<<endl<<"����������ǰ����������";
   MyTree.preorder(); // ���Թ������������Ƿ���ȷ
   cout<<endl;

   MyTree.GetCode ( mydata,n );  // ��ȡ��Ӧ���ŵı���

   MyTree.Coding(mydata,n);  // ����������ִ����ж����Ʊ���

   cin>>n;
}


