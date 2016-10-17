/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>**<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*
>>>>>>>>>> Advanced Data Structure And Algorithms <<<<<<<<<<<<<<<
>>>>>>>>>>                                        <<<<<<<<<<<<<<<
>>>>>>>>>>                                        <<<<<<<<<<<<<<<
>>>>>>>>>> 	             

*/
/* File -> employee2.txt */
        /* Linear Probing , Chaining , Double hashing, Binary Search Tree, AVL tree */

#include<iostream>                                                        // Header files
#include<string.h>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<iomanip>
using namespace std;

class Employee_record                                                     // Class declaration for Employee Record
{

friend class Chain;                                                       // Friend classes 
friend class hashtable;                                                   
friend class LinearList;
friend class double_hash;
friend class bst;
friend class avl;
  
	private:
		  int salary;	
		  long int mobile_num;
		  std::string  employee_ID;                                     // String type employee ID
		  char Name[30],Email[30],Position[20],Address[50];
	public:
		  std::string get_employee_ID()
		  {
		    return employee_ID;
		  }


  void print_record()                                    // Print record of file
  {
    std::cout<<"Employee_ID  :->"<<employee_ID<<'\n';
    std::cout<<"Name         :->"<<Name<<'\n';
    std::cout<<"Address      :->"<<Address<<'\n';
    std::cout<<"Email        :->"<<Email<<'\n';
    std::cout<<"Position     :->"<<Position<<'\n';
    std::cout<<"Salary       :->"<<salary<<'\n';
    std::cout<<"Mobile_num   :->"<<mobile_num<<'\n';
  }
  void insert(std::string id,char name[],char email[],char position[],char address[],int Salary,long int Mobile_num) // INsert data 
  {
    employee_ID.assign(id);
    strcpy(Name,name);
    strcpy(Email,email);
    strcpy(Position,position);
    strcpy(Address,address);
    salary=Salary;
    mobile_num=Mobile_num;
  }
  
};

/***********************************  Chaining Technique ****************************************/


class ChainNode{               // Chain node declaration
		friend class  Chain;
		private:
			 ChainNode  *link;
			 Employee_record data ;
};


class Chain{                    // Chain Class 
	private:
  		ChainNode  *first;
  		ChainNode  *last;
  		int len;
 
	public: 

/*>>>>> .......................  Definition of Chain class Functions ....................<<<<<*/
 
Chain(void)
{ // Constructor for the linked linear list
	 first = NULL;
	 last=NULL;
}

Chain(const Chain& temp)  // copy constructor 
{
  if(temp.last==0) first=last=0;
  ChainNode *p1=0,*p2=0;
  first=new ChainNode;
  memcpy(&(first->data),&(temp.first->data),sizeof(Employee_record)); // copying the values using memcpy
  len=0;                                                                  
  p1=first;
  p2=temp.first->link;

  while(p2)
    {
      p1->link=new ChainNode;
      p1=p1->link;
      p1->data=p2->data;
      p2=p2->link;
    }
  last=p1;
  p1->link=0;
  len=temp.len;
}


~Chain(void)
{ // Distructor for the linked linear list, which Delete all the nodes in chain
	 ChainNode *next;  // Next node to ChainNode
	 while(first){
			next = first -> link;
			delete  first;
			first = next;
	}
}


void insert(Employee_record &a)
{ // Insert data after element

   ChainNode *p =new ChainNode;
  
   p->data.insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
   len++;
  
  if(last==NULL) 
    {
      p->link=last;
      last=p;
      first=p;
     
      return;
     
    }
  
  last->link=p;
  last=last->link;
  p->link=NULL;
  
}


void delete_element(int k,Employee_record &a)
{// DElete element 
  ChainNode  *current = first;
  for (int  i=1;  i < k-1;  i++)
    {
      current = current -> link;
    }
  ChainNode  *p =current;
 
  if(k==1)
    {
      cout<<"here"<<'\n';
      first=current->link;
      a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);
      delete current;
      cout<<"next to here"<<'\n';
      return;
    }
  p = current->link ;
  a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);
  current->link=p->link;
  delete p;
 
  len--;
  
}


void print()
{ // Display the record
  ChainNode *current=first;
  int i=1;
  while(current)
    {
      cout<<"Employee "<<i<<'\n';
      current->data.print_record(); 
      current=current->link;
      i++;
    }
 
}

void append(Chain* x)
{
  if(x->first)
    {
   last->link=x->first;
   last=x->last;}
}

bool empty()
{// check for empty 
  if(first)
    return false;
  else
    return true;

}

int  length()
{//return length 
   return len;
  
}

  
int  search(std::string  id)
{ // searching Employee id in linked list
  ChainNode  *current = first; 
  int  index = 1;
  while  (current  && id.compare(current->data.employee_ID)!=0)
    {
      current = current -> link;
      index++;
    }
  if  (current)
    {
      
      return   index;
    }
  return  -1;
  }


void find(int k,Employee_record &a)
{ // find the id in file for k element
  ChainNode  *p = first; 
  int  i = 1;
  while  (p  && i<k)
    {
      p = p -> link;
      i++;
    }
  if  (p)
    {	
      a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);
    }  
}


void update_file(int i)
{ // update file 
	ChainNode *node=first;
 
	if(i==0) 
	{
	std::ofstream fp("employee2.txt",ios::trunc); //If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one
	
	while(node)
    	{
      fp<<node->data.employee_ID;
      fp<<'\n';
      fp<<node->data.Name;
       fp<<'\n';
      fp<<node->data.Email;
       fp<<'\n';
      fp<<node->data.Address;
       fp<<'\n';
      fp<<node->data.Position;
       fp<<'\n';
      fp<<node->data.salary;
       fp<<'\n';
      fp<<node->data.mobile_num;
      fp<<'\n';
      fp<<'\n';
	node=node->link;
	}		
	fp.close();
	}

	else 
	{
	std::ofstream fp("employee2.txt",ios::app); //All output operations are performed at the end of the file, appending the content to the current content of the file.
		while(node)
    	{
      fp<<node->data.employee_ID;
      fp<<'\n';
      fp<<node->data.Name;
       fp<<'\n';
      fp<<node->data.Email;
       fp<<'\n';
      fp<<node->data.Address;
       fp<<'\n';
      fp<<node->data.Position;
       fp<<'\n';
      fp<<node->data.salary;
       fp<<'\n';
      fp<<node->data.mobile_num;
      fp<<'\n';
      fp<<'\n';
	node=node->link;
	}		
	fp.close();
	}
}

};





/**************************************** Hash table ******************************************************/


class hashtable                                                     // Hash table class declaration             
{
	private:
  		Chain *bucket;
  		bool collision;
  		int load_factor;
  		int table_size;
	public:
 		hashtable(int size);
  		~hashtable();
  		hashtable(const hashtable &temp);
  		void insert(Employee_record &a);
  		void delete_element(std::string id,Employee_record &a);
  		int search(std::string id);
  		int isempty();
  		int length();
  		void print();
		void update_file();
		void rehash();
};

/*.................. Hash class - function defination ...........................*/

int hash_code(std::string a)   
{// hash code to get value of string employee ID
  int x=37,i=0,len=0,c=0;
  
  while(a[i]) {len++;i++;}
  
  int b[len];
  for(i=0;i<len;i++)
    {
      b[i]=(int)a[i];
    }
  for(i=0;i<len;i++)
    {
      c=c*x+b[i];
    }
  
  return c;
}


int compression_map(int k,int m)
{// To find the position of id
  return k%m;
}


int doublehash_offset(int k,int m)
{ // in double hashing -> second hash function
  int subsize;
  if(m%2==0) subsize=m/2;
  subsize=(m+1)/2;
  int offset=subsize-k%subsize;
  return offset;
}


hashtable::hashtable(int size)
{ // define hash table 
  bucket = (Chain *)malloc(size*sizeof(Chain));
  for(int i=0;i<size;i++)
    {
      Chain bucket[i];
    }
  table_size=size;
  collision=false;
  load_factor=0;
}


hashtable::~hashtable()
{// destructor for hashtable
  ChainNode *next,*p;
  for(int i=0;i<table_size;i++)
    {
      
      bucket[i].~Chain();
     
    }
}



void hashtable::rehash()
{ // rehashing by resizing the table
  cout<<'\t'<<"REHASH"<<'\n';
  int len=0,key,index;Employee_record a;
  Chain *re_bucket=new Chain[2*table_size];
  for(int i=0;i<table_size;i++)
    {
      cout<<"before length"<<'\n';
      len=bucket[i].length();
      cout<<"after length"<<'\n';
      if(bucket[i].empty()==0) continue;
      
      for(int j=0;j<len;j++)
	{
	  cout<<"2nd for start"<<'\n';
	  bucket[i].find(1,a);
	  cout<<"2nd for middle"<<'\n';
	  key= hash_code(a.get_employee_ID());
	  index=compression_map(key,2*table_size); 
	  cout<<"2nd for end before"<<'\n';
	  re_bucket[index].insert(a);
	  cout<<"2nd for end"<<'\n';
	}
    }
  bucket=re_bucket;
  table_size=2*table_size;
  cout<<'\t'<<"REHASH END"<<'\n';
}




void hashtable::insert(Employee_record &a)
{ // insert the record in hash tabel
  
  std::string id=a.get_employee_ID(); // get employee id
 
  int key= hash_code(id);             // get the key
  
  int index=compression_map(key,table_size);  // find the position
  
  int len=bucket[index].length();             // put data to the bucket
  if(len/table_size>=0.5) rehash();
  bucket[index].insert(a);
}

int hashtable::search(std::string id)
{// search in hash table
   int key= hash_code(id);              // get key
   int index=compression_map(key,table_size);// get position
   int c= bucket[index].search(id); // search in bucket
   return c;
}

void hashtable::delete_element(std::string id,Employee_record &a)
{// delete data from hash table
  int key= hash_code(id);
  int index=compression_map(key,table_size);
  int c= bucket[index].search(id);
  if(c==0) 
    {
      std::cout<<"\n\t\t\t\t\tEmployee_id Not Found\n";
      return;
    }
  
  bucket[index].delete_element(c,a); // delete data
	update_file();               // update file after deleting
}

void hashtable::print()
{// print the data from table
  for(int i=0;i<table_size;i++)
    {
      bucket[i].print();
    }
}

void hashtable::update_file()
{// update the file
	for(int i=0;i<table_size;i++)
    {
      bucket[i].update_file(i);
    }
}


/************************************ Linear probing ***************************************/

class LinearList{                                                    // linear list class 
private: 
  Employee_record *element;    // 1D dynamic array
  int len;
  int table_size;
public:
  LinearList(int  MaxSize);
  LinearList(const LinearList& temp);
  ~LinearList();
  bool  isEmpty();
  int  length();
  int  search(std::string id);
  void  delete_element(std::string id,Employee_record &a);
  void  insert(Employee_record  &a);
  void print();
  void rehash();
	void update_file();
};


int hash_code1(std::string a)
{// hash code for linear probing
  int x=37,i=0,len=0,c=0;
  
  while(a[i]) {len++;i++;}
  
  int b[len];
  for(i=0;i<len;i++)
    {
      b[i]=(int)a[i];
    }
  for(i=0;i<len;i++)
    {
      c=c*x+b[i];
    }
  
  return c;
}


int compression_map1(int k,int m)
{// compression map for linear probing
  return k%m;
}


int doublehash_offset1(int k,int m)
{// double hash offset
  int subsize;
  if(m%2==0) subsize=m/2;
  subsize=(m+1)/2;
  int offset=subsize-k%subsize;
  return offset;
}

void LinearList::update_file()
{ // update file 
	int index=0;std::string check="Unenrolled",check1="deleted";
	  std::ofstream fp("employee2.txt",ios::trunc); ////If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one
	for( index=0;index<table_size;index++)
    {
      if((element[index].employee_ID).compare(check)!=0&&(element[index].employee_ID).compare(check1)!=0)
		{
			   
    	  fp<<element[index].employee_ID;
      	fp<<'\n';
      	fp<<element[index].Name;
      	 fp<<'\n';
      fp<<element[index].Email;
       fp<<'\n';
      fp<<element[index].Address;
       fp<<'\n';
      fp<<element[index].Position;
       fp<<'\n';
      fp<<element[index].salary;
       fp<<'\n';
      fp<<element[index].mobile_num;
      fp<<'\n';
      fp<<'\n';
     
		}
}
	 fp.close();
}
/*.................. Linear list class - function declaration ......................*/

LinearList::LinearList(int MaxSize)
{ // Constructor for the sequential linear list
  element = new  Employee_record[MaxSize];  
  table_size=MaxSize;
  len = 0;
  string a ="Unenrolled";
  for(int i=0 ;i<MaxSize;i++)
    {
      element[i].employee_ID.assign(a);
    }
}


LinearList::LinearList(const LinearList& temp) 
{ // Copy constructor for linear list
	table_size=temp.table_size;
	element=new Employee_record[table_size];
	len=temp.len;
	memcpy(element, temp.element, table_size); 
}


 LinearList::~LinearList()
{ // Distructor for the sequential linear list
	 delete [] element;
}

bool  LinearList::isEmpty()
{ // Function that checks whether the list is empty
	 return   len == 0;}

int  LinearList::length()
{ // Function that returns the length of the list
	 return   len;
}




int  LinearList::search(string id)
{ // Search for x and return the position if found, else return 0.
  int k=hash_code1(id);
  int index=compression_map1(k,table_size);
  string check="Unenrolled",check1="deleted";
  int count=0;
  while((element[index].employee_ID).compare(id)!=0&&(element[index].employee_ID).compare(check)!=0)
    {
      index++;
      count++;
      index=index%table_size;
    }
  if(index==table_size||element[index].employee_ID.compare(check)==0||element[index].employee_ID.compare(check1)==0) return -1;
  return index;
}

void  LinearList::delete_element (string id,Employee_record &a)
{// delete data from list
  int k=hash_code1(id);
  int index=compression_map1(k,table_size);
  string check="Unenrolled";
  int count=0;
  while((element[index].employee_ID).compare(id)!=0&&count<table_size&&element[index].employee_ID.compare(check)!=0)
    {
      count++;
      index++;
      index=index%table_size;
    }
  if(count==table_size||element[index].employee_ID.compare(check)==0) 
    {
      cout<<"\n\t\t\tUnenrolled employee.Check id once\n" ;
      return;
    }
  a.insert(element[index].employee_ID,element[index].Name,element[index].Email,element[index].Address,element[index].Position,element[index].salary,element[index].mobile_num);
  check="deleted";
  
  element[index].employee_ID.assign(check);
  len = len-1; 

  update_file();
}


void LinearList::rehash()
{
 // rehashing 
  const int size=2*table_size;
  Employee_record *re_element=new Employee_record[size];
  string id,check="Unenrolled",check1="deleted";
  
  print();
  cout<<'\t'<<"REHASH"<<'\n';
  for(int i=0;i<size;i++)
    {
      re_element[i].employee_ID.assign(check);
    }
  for(int i=0;i<table_size;i++)
    {
     
      id.assign( element[i].get_employee_ID());
      
      if(id.compare(check)==0||id.compare(check1)==0) continue;
      
      int k=hash_code1(id);  
      
      int index=compression_map1(k,size);
     
      if((re_element[index].employee_ID).compare(check)==0) 
	{
	  re_element[index].insert(element[i].employee_ID,element[i].Name,element[i].Email,element[i].Address,element[i].Position,element[i].salary,element[i].mobile_num);
	 
	  re_element[index].print_record();
	}
      else
	{
	  int count=0;
	  while((re_element[index].employee_ID).compare(check)!=0&&count<size)
	    {
	      count++;
	      index++;
	      index=index%size;
	    }
	  re_element[index].insert(element[i].employee_ID,element[i].Name,element[i].Email,element[i].Address,element[i].Position,element[i].salary,element[i].mobile_num);
	  
	  re_element[index].print_record();
	}
    }
  
  element=re_element;
 
  table_size=2*table_size;
  print();
}


void  LinearList::insert(Employee_record &a)
{ // Insert x after kth element. 
  if(len>=table_size) rehash();

  int k=hash_code1(a.get_employee_ID());  
  int index=compression_map1(k,table_size);
  
  string check="Unenrolled",check1="deleted";

  if((element[index].employee_ID).compare(check)==0||(element[index].employee_ID).compare(check1)==0) 
    {
      element[index].insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
     
      len++; 
     
          }
  else
    {
      int count=0;
      while((element[index].employee_ID).compare(check)!=0&&count<table_size)
	{
	  count++;
	  index++;
	  index=index%table_size;
	}
      element[index].insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
      len++;
    
    }
  
}





void LinearList::print()
{// print the linear list
  int i=0;
  string check="Unenrolled",check1="deleted";
  for( i=0;i<table_size;i++)
    {
      if((element[i].employee_ID).compare(check)!=0&&(element[i].employee_ID).compare(check1)!=0)
	{
	  cout<<"Employee "<<i<<'\n';
	  element[i].print_record() ;
	  // cout<<'\n';
	}
    }
  cout<<"length of list"<<i<<'\n';
}

//******************************************** Double Hashing *******************************************************************

class double_hash                                                               // class declaration
{

	private: 
		 Employee_record *element;    // 1D dynamic array
		  int len;
		  int table_size;
  
	public:
		double_hash(int  MaxSize);
		double_hash(const double_hash& temp);
		~double_hash();
		bool  isEmpty();
  		int  length();
  		int  search(string id);
  		void  delete_element(string id,Employee_record &a);
  		void  insert(Employee_record  &a);
  		void print();
  		void rehash();
		void update_file();

};

int hash_code2(std::string a)
{// hash code for double hashing
  int x=37,i=0,len=0,c=0;
  
  while(a[i]) {len++;i++;}
  
  int b[len];
  for(i=0;i<len;i++)
    {
      b[i]=(int)a[i];
    }
  for(i=0;i<len;i++)
    {
      c=c*x+b[i];
    }
  
  return c;
}


int compression_map2(int k,int m)
{// compression map for double hashing
  return k%m;
}


int doublehash_offset2(int k,int m)
{ // double hashing offset
  int subsize;
  if(m%2==0) subsize=m/2;
  subsize=(m+1)/2;
  int offset=subsize-k%subsize;
  return offset;
}



void double_hash::update_file()
{// double hashing update the existing file
	int index=0;std::string check="Unenrolled",check1="deleted";
	  std::ofstream fp("employee2.txt",ios::trunc); //If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one
	for( index=0;index<table_size;index++)
    {
      if((element[index].employee_ID).compare(check)!=0&&(element[index].employee_ID).compare(check1)!=0)
		{
			   
    	  fp<<element[index].employee_ID;
      	fp<<'\n';
      	fp<<element[index].Name;
      	 fp<<'\n';
      fp<<element[index].Email;
       fp<<'\n';
      fp<<element[index].Address;
       fp<<'\n';
      fp<<element[index].Position;
       fp<<'\n';
      fp<<element[index].salary;
       fp<<'\n';
      fp<<element[index].mobile_num;
      fp<<'\n';
      fp<<'\n';
     
		}
}
	 fp.close();
}


/*.................. Double hash - function definition ..........................*/
double_hash::double_hash(int  MaxSize)
{// define hash table 
  element = new  Employee_record[MaxSize];  
  table_size=MaxSize;
  len = 0;
  string a ="Unenrolled";
  for(int i=0 ;i<MaxSize;i++)
    {
      element[i].employee_ID.assign(a);
    }
}

double_hash::double_hash(const double_hash& temp)
{
  // Copy constructor for double hash table
	table_size=temp.table_size;
	element=new Employee_record[table_size];
	len=temp.len;
	
	memcpy(element, temp.element, table_size);
}
double_hash::~double_hash()
{
  delete [] element;
}


bool double_hash::isEmpty()
{ // Function that checks whether the list is empty
	 return   len == 0;}

int  double_hash::length()
{ // Function that returns the length of the list
	 return   len;
}


void double_hash::rehash()
{ // rehash in double hashing technique
   const int size=2*table_size;
  Employee_record *re_element=new Employee_record[size];
  string id,check="Unenrolled",check1="deleted";
  
  print();
  cout<<'\t'<<"REHASH"<<'\n';
  for(int i=0;i<size;i++)
    {
      re_element[i].employee_ID.assign(check);
    }
  for(int i=0;i<table_size;i++)
    {
      id.assign( element[i].get_employee_ID());
      if(id.compare(check)==0||id.compare(check1)==0) continue;
      int k=hash_code2(id);  
      int index=compression_map2(k,size);
      
      if((re_element[index].employee_ID).compare(check)==0) 
	{
	  re_element[index].insert(element[i].employee_ID,element[i].Name,element[i].Email,element[i].Address,element[i].Position,element[i].salary,element[i].mobile_num);
	  
	  re_element[index].print_record();
	}
      else
	{
	  int count=0;
	  while((re_element[index].employee_ID).compare(check)!=0&&count<size)
	    {
	      count++;
	    index+=doublehash_offset2(index,size);
	    index=index%size;
	    }
	  re_element[index].insert(element[i].employee_ID,element[i].Name,element[i].Email,element[i].Address,element[i].Position,element[i].salary,element[i].mobile_num);
	 
	  re_element[index].print_record();
	}
    }
  
  element=re_element;
  
  table_size=2*table_size;
 
}



void double_hash::insert(Employee_record &a)
{ // insert the data to table 
  if(len>=table_size) rehash();
  int k=hash_code2(a.get_employee_ID());
 
  int index=compression_map2(k,table_size);
 
  string check="Unenrolled",check1="deleted";
  if((element[index].employee_ID).compare(check)==0&&(element[index].employee_ID).compare(check1)==0) 
    {
      element[index].insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
     
      len++; 
      
       cout<<index<<'\n';
    }
  else
    {
      int count=0,size=table_size;
      while((element[index].employee_ID).compare(check)!=0&&count<table_size)
	{
	  count++;
	  index+=doublehash_offset2(index,size);
	  index=index%table_size;
	}
      element[index].insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
      len++;
       cout<<index<<"\t"<<count<<'\n';
    }
 
}


int  double_hash::search(string id)
{// search in double hashing technique
   int k=hash_code2(id);
  int index=compression_map2(k,table_size);
  string check="Unenrolled",check1="deleted";
  int count=0,size=table_size;
  while((element[index].employee_ID).compare(id)!=0&&(element[index].employee_ID).compare(check)!=0)
    {
     
      count++;
      index+=doublehash_offset2(index,size);
      index=index%table_size;
    }
  if(index==table_size||element[index].employee_ID.compare(check)==0&&(element[index].employee_ID).compare(check1)==0) return -1;
  return index;
}

void double_hash:: delete_element(string id,Employee_record &a)
{ // delete the element and put a check for further search and insert function
   int k=hash_code2(id);
  int index=compression_map2(k,table_size);
  string check="Unenrolled";
  int count=0,size=table_size;
  while((element[index].employee_ID).compare(id)!=0&&count<table_size&&element[index].employee_ID.compare(check)!=0)
    {
      count++;
      index+=doublehash_offset2(index,size);
      index=index%table_size;
    }
  if(count==table_size||element[index].employee_ID.compare(check)==0) 
    {
      cout<<"\n\t\t\tEmployee Not Found\n" ;
      return;
    }
 a.insert(element[index].employee_ID,element[index].Name,element[index].Email,element[index].Address,element[index].Position,element[index].salary,element[index].mobile_num);
  check="deleted";
  element[index].employee_ID.assign(check);
  len = len-1; 
	update_file();
}


void double_hash::print()
{ // print the data
  int i=0;
  string check="Unenrolled",check1="deleted";
  for( i=0;i<table_size;i++)
    {
      if((element[i].employee_ID).compare(check)!=0&&element[i].employee_ID.compare(check1)!=0)
	{
	  cout<<"Employee "<<i<<'\n';
	  element[i].print_record() ;
	  cout<<'\n';
	}
    }
  cout<<"\nLength of list :->"<<i<<'\n';
}


/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. BINARY SEARCH TREE .<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


class bst_node                         // binary search tree node declaration
{
	friend class avl;
	friend class bst;
	
	protected:
		Employee_record data;	// protected  data
		bst_node *left;
		bst_node *right;
		bst_node *parent;

};

class bst
{
 
 	protected:
 		bst_node *root;
 		int height;


 	public:
 		bst();
 		~bst();
 		bst(const bst &bst);
 		void insert(Employee_record &a);
 		void delete_element(std::string id,Employee_record &a);
 		int search(string id);
 		Employee_record find(string id);
 		void traversal(int a);
 		void preordertraversal(bst_node *node);
 		void inordertraversal(bst_node *node);
 		void postordertraversal(bst_node *node);
 		int height_of_tree();
 		int height_of_node(std::string id);
 		int height_of_subtree(bst_node* node);
 		int no_of_nodes();
 		void successor(bst_node *node);
 		void update_file(bst_node *node);
 
 };
/*....................  Binary search tree - function definition ...................*/
bst::bst()
{// constructor for bst
  root=0;
  height=-1;
}

 bst::~bst()
{// destructor for bst
  delete root;
   root=0;
}

bst::bst(const bst &bst)
{// copy constructor 
  
}


void bst::insert(Employee_record &a)
 {// insert the data to bst
   bst_node *current=root,*current_py,*p;
   p=new bst_node;int count=0;
   p->left=p->right=0;
   p->data.insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
   if(root==0)    
     {
       root=p;height++;root->parent=0;
     }
   else
     {
       while(current)
	 {
	   if(current->data.get_employee_ID().compare(a.get_employee_ID())<0&&current->right)
	     {
	       current=current->right;count++;
	     }
	   else if(current->data.get_employee_ID().compare(a.get_employee_ID())>0&&current->left)
	     { 
	       current=current->left;count++;
	     }
	   else break;
	 }
       if(current->data.get_employee_ID().compare(a.get_employee_ID())<0) 
	 {
	   current->right=p;
	 }
       else 
	 {
	   current->left=p;
	 }
       p->parent=current;
       if(count+1>height) height=count+1;
      
     }
 }


int bst::search(string id)
 {// search for data in bst
   bst_node *current=root;int count=0;
    while(current&&id.compare(current->data.get_employee_ID())!=0)
     {
       if(current->data.get_employee_ID().compare(id)<0&&current->right)
	 {
	   current=current->right;count++;
	 }
       else if(current->data.get_employee_ID().compare(id)>0&&current->left)
	 { 
	   current=current->left;count++;
	 }
       else break;
     }
    if(id.compare(current->data.get_employee_ID())==0) return count;
   else return -1;
 }


 Employee_record bst::find(string id)
{// find the employee id in bst 
bst_node *current=root,*p;int count=0;Employee_record a;
    while(current&&id.compare(current->data.get_employee_ID())!=0)
     {
       if(current->data.get_employee_ID().compare(id)<0&&current->right)
	 {
	   current=current->right;count++;
	 }
       else if(current->data.get_employee_ID().compare(id)>0&&current->left)
	 { 
	   current=current->left;count++;
	 }
       else break;
     }
    if(id.compare(current->data.get_employee_ID())==0) 
	{
		p=current;
		a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);
		return a;
	}
  
}


void bst::delete_element(string id,Employee_record &a)
 {// delete element from bst 1. search 2. delete 3. find the succeccor
   bst_node *current=root,*p;

 //searching node to be deleted
    while(current&&id.compare(current->data.get_employee_ID())!=0)
     {
       if(current->data.get_employee_ID().compare(id)<0&&current->right)
	 {
	   current=current->right;
	 }
       else if(current->data.get_employee_ID().compare(id)>0&&current->left)           
	 { 
	   current=current->left;
	 }
       else break;
     }

   //verifying whether given key exists or not and doing further operation
    if(id.compare(current->data.get_employee_ID())==0)                          
      {
	p=current;
	a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);
	if(!current->left  &&!current->right)
	  {
	    if(current==root) root=0;
	    else
	      {
		if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0)
		  current->parent->right=0;
		else 	current->parent->left =0;   
		p=current->parent;
		delete current;
	      }
	  }
	else if(current->left &&current->right)
	  {
	    int ch=0;
	     //finding successor
	    p=current;
	    p=p->right;
	    while(p&&p->left) {p=p->left;ch=1;}             
	   
	    //successors right child updating as successors parent left child
	    if(ch==1)
	      {
		if(p->right) p->parent->left=p->right;     
		else   p->parent->left=0;
		p->right=current->right;
		p->right->parent=p;
	      }
	   
	    
	    //placing successor in place of node to be deleted
	   
	     p->left=current->left;               // left child of current as p corresponding children
	     p->left->parent=p;

	     p->parent=current->parent;           //p's parent as current's parent

	     //current parent child as p
	     if(current!=root)
	       {
		 if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0) current->parent->right=p;
		 else current->parent->left=p;
	       }
	  
	    if(current==root) root=p;                  //updating root  in case root is to be deleted

	    current->left=current->right=current->parent=0;
	    delete current;
	
	   
	   
	  }
	else
	  {
	      	if(current->right) 
		  {
		   
		    p=current->right;
		    p->parent=current->parent;
		  }
		else if(current->left ) 
		  {
		    p=current->left;
		    p->parent=current->parent;
		  }
		if(current==root)  root=p;
		else
		  {
		    if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0)
		      current->parent->right=p;
		    else 	current->parent->left =p; 
		  }
		delete current;
	  }
	traversal(4);
      }
 }




void bst:: update_file(bst_node *node)
{// update the file 
  if(!node) return;
  if(node==root) 
    {
      std::ofstream fp("employee2.txt",ios::trunc);//If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one  
      fp<<node->data.employee_ID;
      fp<<'\n';
      fp<<node->data.Name;
       fp<<'\n';
      fp<<node->data.Email;
       fp<<'\n';
      fp<<node->data.Address;
       fp<<'\n';
      fp<<node->data.Position;
       fp<<'\n';
      fp<<node->data.salary;
       fp<<'\n';
      fp<<node->data.mobile_num;
      fp<<'\n';
      fp<<'\n';
      fp.close();
     
    }
  else
    {
  std::ofstream fp("employee2.txt",ios::app);
   fp<<node->data.employee_ID;
    fp<<'\n';
   fp<<node->data.Name;
    fp<<'\n';
   fp<<node->data.Email;
    fp<<'\n';
   fp<<node->data.Address;
    fp<<'\n';
   fp<<node->data.Position;
    fp<<'\n';
   fp<<node->data.salary;
    fp<<'\n';
   fp<<node->data.mobile_num;
   fp<<'\n';
   fp<<'\n';
   fp.close();
    }
  update_file(node->left);
  update_file(node->right);
   
}




void bst::preordertraversal(bst_node *node)
{// Preorder Traversal :-> root -> left -> right  
  if(node==0) return;
  node->data.print_record();
  preordertraversal(node->left);
  preordertraversal(node->right);
}


void bst::inordertraversal(bst_node *node)
{// Inorder Traversal :-> left -> root -> right
  if(node==0) return;
  inordertraversal(node->left);
  node->data.print_record();
  inordertraversal(node->right);
}


void bst::postordertraversal(bst_node *node)
{// Post Order Traversal :-> left -> right -> root 
  if(node==0) return;
  postordertraversal(node->left);
  postordertraversal(node->right);
  node->data.print_record();
}


void bst::traversal(int a)
 {
   if(a==1) preordertraversal(root);
   else if(a==2) inordertraversal(root);
   else if(a==3) postordertraversal(root);
   else if(a==4) update_file(root);
 }

int bst::height_of_tree()
{// calculate height of tree 
  return height;
}


int bst::height_of_node(string id)
{// calculate height of  node
  bst_node *current=root;int count=0;
  while(current&&id.compare(current->data.get_employee_ID())!=0)
    {
      if(current->data.get_employee_ID().compare(id)<0&&current->right)
	{
	  current=current->right;count++;
	}
      else if(current->data.get_employee_ID().compare(id)>0&&current->left)
	{ 
	  current=current->left;count++;
	 }
      else break;
    }
  if(id.compare(current->data.get_employee_ID())==0) {cout<<count;return count;}
  else return -1;
}


int bst::height_of_subtree(bst_node* node)
{
  if(!node) return -1;
  int  h_l=0,h_r=0;
  
  h_l=height_of_subtree(node->left)+1;
  h_r=height_of_subtree(node->right)+1;
  if(h_l>h_r) return h_l;
  else return h_r;
}




void bst::successor(bst_node *node)
{
  // find the successor in bst tree
  bst_node *p=node;
  if(p->right)
    {
      p=p->right;
      while(p&&p->left) p=p->left;
    }
  else
    {
      if(p->parent->data.get_employee_ID().compare(p->data.get_employee_ID())>0)  p=p->parent;
      else
	{
	  p=p->parent;
	  while(p->parent->data.get_employee_ID().compare(p->data.get_employee_ID())<0) p=p->parent;
	}
    }
 
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.. AVL .. <<<<<<<<<<<<<<<<<<<<<<<<<<<********************************

class avl:public bst                      // inheritance avl -> BST
{
 
  public:
 	avl();
 	
 	avl(const avl &avl);
 	void insert(Employee_record &a);
 	void delete_element(std::string id,Employee_record &a);
	int balance_factor(bst_node *node);
	void right_rotation(bst_node *node);
	void left_rotation(bst_node *node);
	void traversal(int a);
 	void preordertraversal(bst_node *node);
	void inordertraversal(bst_node *node);
	void postordertraversal(bst_node *node);
	void update_file(bst_node *node);	
 };

avl::avl()   // avl constructor 
  :bst()
{

}



int avl::balance_factor(bst_node *node)
{// calculating the balance factor 
  
  int h_l=0,h_r=0,bf;
  cout<<"\n";
  h_l=height_of_subtree(node->left);
  cout<<"\nHeight of left stree :-> "<<h_l;
  h_r=height_of_subtree(node->right);
  cout<<"\nHeight of right stree  :-> "<<h_r;
  cout<<"\n";
  bf=h_l-h_r;
  return bf;
}



void avl::right_rotation(bst_node *node)
{ // Right Rotation to balance the tree
  bst_node *y,*z=node,*p;
  y=z->left;
  if(z!=root)
    {
      p=z->parent;
      y->parent=p;
      if(p->left==z) p->left=y;
      else p->right=y;
    }
  else
    {
      y->parent=0;
      root=y;
    }
  z->parent=y;
  if(y->right) 
    {
      y->right->parent=z;
     
    }
   z->left=y->right;
  y->right=z;
  node=z;
}


void avl::left_rotation(bst_node *node)
{// left Rotation to balance the tree
   bst_node *y,*z=node,*p;
  y=z->right;
  if(z!=root)
    {
      p=z->parent;
      y->parent=p;
      if(p->left==z) p->left=y;
      else p->right=y;
    }
  else 
    {
      y->parent=0;
      root=y;
    }
  z->parent=y;
  if(y->left)
    {
      y->left->parent=z;
    
    }
  z->right=y->left;
  y->left=z;
 
}


void avl::insert(Employee_record &a)
{ // insert the data
  bst_node *current=root,*current_py,*p;
  p=new bst_node;int count=0;
  p->left=p->right=0;
  p->data.insert(a.employee_ID,a.Name,a.Email,a.Address,a.Position,a.salary,a.mobile_num);
  if(root==0)    
    {
      root=p;height++;
      root->parent=0;
    }
  else
    {
      while(current)
	{
	  if(current->data.get_employee_ID().compare(a.get_employee_ID())<0&&current->right)
	    {
	      current=current->right;count++;
	    }
	  else if(current->data.get_employee_ID().compare(a.get_employee_ID())>0&&current->left)
	    { 
	      current=current->left;count++;
	    }
	  else break;
	}
      if(current->data.get_employee_ID().compare(a.get_employee_ID())<0) 
	{
	  current->right=p;
	 
	}
      else 
	{
	  current->left=p;
	}
      p->parent=current;
      if(count+1>height) height=count+1;
  

  
      int bf=0;
      while(current)
	{
	 
	  
	  bf= balance_factor(current);
    
	  if(bf==2)  
	    {
	      bf=balance_factor(current->left);
	      if(bf==1) 
		{
		  right_rotation(current);
		  break;
		}
	      else if(bf==-1)
		{
		  left_rotation(current->left);
		  right_rotation(current);
		  break;
		}
	  
	    }
      
	  if(bf==-2)
	    {
	      bf=balance_factor(current->right);
	      if(bf==-1) 
		{
		  left_rotation(current);
		  break;
		}
	      else if(bf==1)
		{
		  right_rotation(current->right);
		  left_rotation(current);
		  break;
		}
	    }
	  current=current->parent;
	}
  
    }
}




void avl::delete_element(string id,Employee_record &a)
{ // delete data -> 1. search 2. delete 3. balance
  
     bst_node *current=root,*p;

 //searching node to be deleted
    while(current&&id.compare(current->data.get_employee_ID())!=0)
     {
       if(current->data.get_employee_ID().compare(id)<0&&current->right)
	 {
	   current=current->right;
	 }
       else if(current->data.get_employee_ID().compare(id)>0&&current->left)           
	 { 
	   current=current->left;
	 }
       else break;
     }
    

   //verifying whether given key exists or not and doing further operation
    if(id.compare(current->data.get_employee_ID())==0)                          
      {
	p=current;
	a.insert(p->data.employee_ID,p->data.Name,p->data.Email,p->data.Address,p->data.Position,p->data.salary,p->data.mobile_num);


	//--------------------------------------------------NODE HAS NO CHILD------------------------------------------------
	if(!current->left  &&!current->right)
	  {
	    if(current==root) root=0;
	    else
	      {
		if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0)
		  current->parent->right=0;
		else 	current->parent->left =0; 
		p=current->parent;
		p->data.print_record();
		delete current;
	      }
	  }


	//---------------------------------------------NODE HAS TWO CHILDREN--------------------------------------------------

	else if(current->left &&current->right)
	  {
	    int ch=0;
	     //finding successor
	    p=current;
	    p=p->right;
	    while(p&&p->left) {p=p->left;ch=1;}             
	   
	    //successors right child updating as successors parent left child
	    if(ch==1)
	      {
		if(p->right) p->parent->left=p->right;     
		else   p->parent->left=0;
		p->right=current->right;
		p->right->parent=p;
	      }
	   
	    
	    //placing successor in place of node to be deleted
	   
	     p->left=current->left;               // left child of current as p corresponding children
	     p->left->parent=p;

	     p->parent=current->parent;           //p's parent as current's parent

	     //current parent child as p
	     if(current!=root)
	       {
		 if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0) current->parent->right=p;
		 else current->parent->left=p;
	       }
	  
	    if(current==root) root=p;                  //updating root  in case root is to be deleted

	    current->left=current->right=current->parent=0;
	    delete current;
	
	   
	   
	  }
	else
	  {
	      	if(current->right) 
		  {
		   
		    p=current->right;
		    p->parent=current->parent;
		  }
		else if(current->left ) 
		  {
		    p=current->left;
		    p->parent=current->parent;
		  }
		if(current==root)  root=p;
		else
		  {
		    if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0)
		      current->parent->right=p;
		    else 	current->parent->left =p; 
		  }
		delete current;
	  }
      }
	
	  
	//-------------------------------------//NODE HAS ONLY ONE CHILD---------------------------------------------------------------
	else
	  {
	      	if(current->right) 
		  {
		  
		    p=current->right;
		 
		    p->parent=current->parent;
		   
		    
		  }
		else if(current->left ) 
		  {
		    
		    p=current->left;
		    p ->parent=current->parent;
		  }
		if(current==root)  root=p;
		else
		  {
		    if(current->data.get_employee_ID().compare(current->parent->data.get_employee_ID())>0)
		      current->parent->right=p;
		    else 	current->parent->left =p; 
		  }
		delete current;
	  }
	//---------------------------------------------BALANCING THE TREE -----------------------------------------------------------------
	int bf=0;
	while(p)
	  {
	    cout<<"avl start"<<'\n';
	    
	    bf= balance_factor(p);
	    cout<<bf<<'\n';
	    if(bf==2)  
	      {
		bf=balance_factor(p->left);
		if(bf==1) 
		  {
		    right_rotation(p);
		    
		  }
		else if(bf==-1)
		  {
		    left_rotation(p->left);
		    right_rotation(p);
		  
		  }
		else  right_rotation(p);
		  
		
	      }
	
	    if(bf==-2)
	      {
		bf=balance_factor(p->right);
		if(bf==-1) 
		  {
		    left_rotation(p);
		 
		  }
		else if(bf==1)
		  {
		    right_rotation(p->right);
		    left_rotation(p);
		  }
		else left_rotation(p);
	      }
	    p=p->parent;
	  }
		traversal(4);
      
}    

void avl:: update_file(bst_node *node)
{// update the file
  if(!node) return;
  if(node==root) 
    {
      std::ofstream fp("employee2.txt",ios::trunc); //If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one   
      fp<<node->data.employee_ID;
      fp<<'\n';
      fp<<node->data.Name;
       fp<<'\n';
      fp<<node->data.Email;
       fp<<'\n';
      fp<<node->data.Address;
       fp<<'\n';
      fp<<node->data.Position;
       fp<<'\n';
      fp<<node->data.salary;
       fp<<'\n';
      fp<<node->data.mobile_num;
      fp<<'\n';
      fp<<'\n';
      fp.close();
     
    }
  else
    {
  std::ofstream fp("employee2.txt",ios::app);
   fp<<node->data.employee_ID;
    fp<<'\n';
   fp<<node->data.Name;
    fp<<'\n';
   fp<<node->data.Email;
    fp<<'\n';
   fp<<node->data.Address;
    fp<<'\n';
   fp<<node->data.Position;
    fp<<'\n';
   fp<<node->data.salary;
    fp<<'\n';
   fp<<node->data.mobile_num;
   fp<<'\n';
   fp<<'\n';
   fp.close();
    }
  update_file(node->left);
  update_file(node->right);
   
}



void avl::preordertraversal(bst_node *node)
{// Preorder Traversal :-> root -> left -> right 
  if(node==0) return;
  cout<<"Employee ID :-> "<<node->data.get_employee_ID()<<'\t';
  cout<<"\n";
  int bf=balance_factor(node);
  cout<<'\t'<<"Balance Factor :-> "<<bf<<'\n';
  cout<<"\n";
  preordertraversal(node->left);
  preordertraversal(node->right);
}


void avl::inordertraversal(bst_node *node)
{// Inorder Traversal :-> left -> root -> right
  if(node==0) return;
  inordertraversal(node->left);
  cout<<"Employee ID :-> "<<node->data.get_employee_ID()<<'\t';
  cout<<"\n";
  int bf=balance_factor(node);cout<<'\t'<<"Balance Factor :-> "<<bf<<'\n';
   cout<<"\n";
  inordertraversal(node->right);
}


void avl::postordertraversal(bst_node *node)
{// Postorder Traversal :-> left -> right -> root
  if(node==0) return;
  postordertraversal(node->left);
  postordertraversal(node->right);
  cout<<"Employee ID :-> "<<'\t'<<node->data.get_employee_ID()<<'\t';
   cout<<"\n";
  int bf=balance_factor(node);cout<<"Balance Factor :-> "<<bf<<'\n';
   cout<<"\n";
}






void avl::traversal(int a)
{
  if(a==1) preordertraversal(root);
  if(a==2) inordertraversal(root);
  if(a==3) postordertraversal(root);
  if(a==4) update_file(root); 
}



/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
 main()
 {

   int i=0,c=1,choice=0;
  Employee_record a,b;
  string id="b131",id1="b231";

  char name[]="Priyanka Mahawar",email[]="pr@live.com",address[]="kota",position[]="Student";

  int salary=500000;long int mobileno=758986235;
 int size , maxsize;
char ch='n';int check=0,search;
 
 a.insert(id,name,email,address,position,salary,mobileno);
 b.insert(id1,name,email,address,position,salary,mobileno);
 cout<<"\n\n*>>>>>>>>>>>>>>>>>>>>>>>>>. Dictionary .<<<<<<<<<<<<<<<<<<<<<<<<<<<*\n\n";  
  cout<<"Enter your choice of dictionary implementation "<<'\n'<<"1. Hashing "<<'\n'<<"2. Binary Search tree"<<'\n'<<"3. AVL Tree"<<'\n';
  cin>>choice;
	

  
  if(choice==1)
    {
 

  	cout<<"Enter the max size of hash table"<<'\n';
  	cin>>maxsize;
    }
  	cout<<"\nFirst Populate the File\n\n";
  	cout<<"Enter the number of employees to be registered\n"<<'\n';
   	cin>>size;
   if(choice==1)
     {
  	cout<<"\nEnter your choice of collison resolution\n "<<'\n'<<"1. Chaining" <<'\n'<<"2. Linear Probing"<<'\n'<<"3. Double hashing"<<'\n';
   //cout<<"By Default chaining is used"<<'\n';
  	cin>>c;
     }


   hashtable h1(maxsize);
   LinearList h2(maxsize);
   double_hash h3(maxsize); 
   bst bT;avl T;
     
   ofstream fp("employee2.txt",ios::app);
   cout<<"\n***** Enter Data one by one *****\n"<<'\n';
   for(i=0;i<size;i++)
     {
      
       cout<<"Enter Employee ID      :->"<<'\t';
       cin>>id;
       fp<<id;
       fp<<'\n';
       cout<<"Enter Name             :->"<<'\t';
       cin>>name;
       fp<<name;
       fp<<'\n';

       cout<<"Enter Email            :->"<<'\t';
       cin>>email;
       fp<<email;
       fp<<'\n';
       
       cout<<"Enter Address          :->"<<'\t';
       cin>>address;
       fp<<address;
       fp<<'\n';
       
       cout<<"Enter Position         :->"<<'\t';
       cin>> position;
       fp<< position;
       fp<<'\n';
       
       cout<<"Enter Salary           :->"<<'\t';
       cin>>salary;
       fp<<salary;
       fp<<'\n';

       cout<<"Enter Mobile Number    :->"<<'\t';
       cin>>mobileno;
       fp<<mobileno;
       fp<<'\n';
       fp<<'\n';

     }
   fp.close();

   ifstream fp1; 
   fp1.open("employee2.txt",ios::app);

   if(choice==2) c=4;
   else if(choice==3) c=5;
   
    
   
   
   for(i=0;i<size;i++)
     {
       while(fp1>>id>>name>>email>>address>>position>>salary>>mobileno)
	 {
	   a.insert(id,name,email,address,position,salary,mobileno);
	   if(c==1)   h1.insert(a);
	   else if(c==2)   h2.insert(a);
	   
	   else if(c==3)   h3.insert(a);
	   else if(c==4)   bT.insert(a);
	   else if(c==5)   T.insert(a);
	   
	 }
     }
   fp1.close();

   cout<<'\t'<<'\t'<<"\t\t *>>>>> DICTIONARY <<<<<*\n\n"<<'\n';
        if(c==1)   h1.print();
        else if(c==2)   h2.print();
	else if(c==3)   h3.print();
	else if(c==4) 
	  {
	     cout<<"Choose traversal"<<'\n'<<"1. Preorder"<<'\n'<<"2. Inorder"<<'\n'<<"3. Postorder"<<'\n';
	    cin>>i;
	    bT.traversal(i);
	  }
	else if(c==5)  
	  {
	     cout<<"Choose traversal"<<'\n'<<"1. Preorder"<<'\n'<<"2. Inorder"<<'\n'<<"3. Postorder"<<'\n';
	    cin>>i;
	    T.traversal(i);
	  }
       while(1)
	 {
	  cout<<"\nFor other functions enter [y/n]\n"<<'\n';
	   cin>>ch;
	   if(ch=='y')
	     {
	       cout<<'\n'<<"1. Search"<<'\n'<<"2. Delete"<<'\n' <<"3. Insert"<<'\n'<<"4. Display"<<'\n';
	       cin>>check;
	       if(check==1)
		 { cout<<"\n\n *>>>>>>>> Searching <<<<<<<*\n\n";
		   cout<<"Enter Employee Id to be searched"<<'\n';
		   cin>>id;
		   if(c==1)  search=h1.search(id);
		   else if(c==2)  search=h2.search(id);
		   else if(c==3)  search=h3.search(id);
		   else if(c==4)  search=bT.search(id);
		   else if(c==5) search =T.search(id);
		   if(search==-1) 
			{
			cout<<"Unsucessfull search.Employee not found"<<'\n';
			}		
                   else 
			{
			cout<<"Successfull search. Position/Level is "<<search<<'\n';
			}
		 }
	       if(check==2)
		 {
		   cout<<"*\n\n>>>>>>> Deletion <<<<<<<<*\n\n";
		   cout<<"\nEnter Employee id to be deleted :->"<<'\t';
		   cin>>id;
		   if(c==1)  search=h1.search(id);
		   else if(c==2)  search=h2.search(id);
		   else if(c==3)  search=h3.search(id);
		   else if(c==4)  search=bT.search(id);
		   else if(c==5) search =T.search(id);
	       
		   if(search==-1) cout<<"\n\nEmployee Not Found\n"<<'\n';
		   else 
		     {
		       if(c==1)    h1.delete_element(id,a);
		       else if(c==2)    h2.delete_element(id,a);
		       else if(c==3)    h3.delete_element(id,a);
		       else if(c==4)  bT.delete_element(id,a);
		       else if(c==5) T.delete_element(id,a);
		       cout<<"Deleted Employee details :-> "<<'\n';
		       a.print_record();
		       cout<<"\n";
		     }
		 }
	        if(check==3)
		  {  cout<<"\n\n*>>>>>>> Insertion <<<<<<<*\n\n";
		     ofstream fp2("employee2.txt",ios::app);
		     cout<<"\nEnter Data of Employee\n"<<'\n';
		     cout<<"Enter Employee ID     :->"<<'\t';
		     cin>>id;
		     fp2<<id;
		     fp2<<'\n';
		     cout<<"Enter Name            :->"<<'\t';
		     cin>>name;
		     fp2<<name;
		     fp2<<'\n';
		     
		     cout<<"Enter Email           :->"<<'\t';
		     cin>>email;
		     fp2<<email;
		     fp2<<'\n';
		     
		     cout<<"Enter Address         :->"<<'\t';
		     cin>>address;
		     fp<<address;
		     fp<<'\n';
       
		     cout<<"Enter Position        :->"<<'\t';
		     cin>> position;
		     fp2<< position;
		     fp2<<'\n';
       
		     cout<<"Enter Salary          :->"<<'\t';
		     cin>>salary;
		     fp2<<salary;
		     fp2<<'\n';
		     
		     cout<<"Enter Mobile Number   :->"<<'\t';
		     cin>>mobileno;
		     fp2<<mobileno;
		     fp2<<'\n';
		     fp2<<'\n';
		     
		     fp2.close();
		     
		     a.insert(id,name,email,address,position,salary,mobileno);
		     if(c==1)   h1.insert(a);
		     else if(c==2)   h2.insert(a);
		     else if(c==3)   h3.insert(a);
		     else if(c==4)   bT.insert(a);
		     else if(c==5)   T.insert(a);
		  }


		 if(check==4)
		   { cout<<"\n\n*>>>>>> Display Data <<<<<<<*\n\n";
		     if(c==1)   h1.print();
		     else if(c==2)   h2.print();
		     else if(c==3)   h3.print();
		     else if(c==4) 
		       {
			 cout<<"Choose traversal"<<'\n'<<"1. Preorder"<<'\n'<<"2. Inorder"<<'\n'<<"3. Postorder"<<'\n';
			 cin>>i;
			 bT.traversal(i);
		       }
		     else if(c==5)  
		       {
			 cout<<"Choose traversal"<<'\n'<<"1. Preorder"<<'\n'<<"2. Inorder"<<'\n'<<"3. Postorder"<<'\n';
			 cin>>i;
			 T.traversal(i);
		       }
		   }
		 
	     }
	   else break; 
	 } 
      
 }

