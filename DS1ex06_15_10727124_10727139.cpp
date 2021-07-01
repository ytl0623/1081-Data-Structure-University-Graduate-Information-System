// 10727124 劉宇廷 10727139 蘇崇傑
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std ;

typedef char Str [1000] ;     // cstr 
int N ;     // 資料總比數 

struct Item {
	int schoolid ;     // 排序使用 
	string schoolname ;
	string departmentname ;
	string dayornight ;
	string level ;
	int students ;
	int teachers ;
	int graduaters ;
};

struct BinaryTree {
	int height ;     // 樹高 
	Item data ;
	BinaryTree *leftChildPtr ;
	BinaryTree *rightChildPtr ;	
	BinaryTree *parent ;	

};

void SetData( Str cStr, Item &temp ) {     // 從整行字串中擷取所需資料 
	string buffer, cut ;
	int tabN = 0 ;
	int indexOfTab = 0 ;
	int i = 0 ;
	
	buffer.assign( cStr ) ;     // cstr to string 
	
	while ( tabN < 10 ) {
		indexOfTab = buffer.find_first_of( '\t', i ) ;

		if ( tabN == 0 ) {
			cut = buffer.substr( 0, indexOfTab ) ;
			temp.schoolid = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 1 ) {
			temp.schoolname = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 3 ) {
			temp.departmentname = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 4 ) {
			temp.dayornight = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 5 ) {
			temp.level = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 6 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.students = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 7 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.teachers = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 8 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.graduaters = atoi( cut.c_str() ) ;
		}
		i = indexOfTab+1 ;
		tabN++ ;
    }
}

bool ReadFile( string filename, vector<Item> &list ) {
	FILE *infile = fopen( filename.c_str(), "r" ) ;

	if ( infile == NULL ) {
    	cout << endl << filename << " does not exist!\n\n" ;
    	return false ;
  	}
  	else {
    	Str tempstr ;
    	Item tempItem ;

    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 
    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 
    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 

    	for ( int i = 1; fscanf( infile, "%[^\n]%*c", &tempstr ) != EOF ; i++ ){
      		SetData( tempstr, tempItem ) ;
      		list.push_back( tempItem ) ;
      		N = i;
    	}
  	}
  	return true ;
}

void Swap( Item &a, Item &b ) {
  	Item temp ;

  	temp.schoolid = a.schoolid ;
 	a.schoolid = b.schoolid ;
 	b.schoolid = temp.schoolid ;
  
 	temp.schoolname = a.schoolname ;
 	a.schoolname = b.schoolname ;
	b.schoolname = temp.schoolname ;
  
 	temp.departmentname = a.departmentname ;
	a.departmentname = b.departmentname ;
 	b.departmentname = temp.departmentname ;
  
	temp.dayornight = a.dayornight ;
	a.dayornight = b.dayornight ;
 	b.dayornight = temp.dayornight ;
  
 	temp.level = a.level ;
 	a.level = b.level ;
	b.level = temp.level ;
  
	temp.students = a.students ;
	a.students = b.students ;
	b.students = temp.students ;
  
  	temp.teachers = a.teachers ;
  	a.teachers = b.teachers ;
  	b.teachers = temp.teachers ;

	temp.graduaters = a.graduaters ;
  	a.graduaters = b.graduaters ;
  	b.graduaters = temp.graduaters ;
}

void SelectSort( vector<Item> &list ) {
	int max ;
  	for( int i = 0 ; i < N-1 ; i++ ){
    	max = i ;
    	for( int j = i + 1 ; j < N  ; j++ ){
      		if ( list[j].schoolid < list[max].schoolid ){
      			max = j ;
      		}
    	}
    	Swap( list[i], list[max] ) ;
  	}
}

void PrintFile( vector<Item> list, int n ) {	
	for ( int i = 0 ; i < n ; i++ ) {
		cout << "[" << i+1 << "]" << "\t" ;
		cout << list[i].schoolname << "\t" ;
		cout << list[i].departmentname << "\t" ;
		cout << list[i].dayornight << "\t" ;
		cout << list[i].level << "\t" ;
		cout << list[i].students << "\t" ;
		cout << list[i].teachers << "\t" ;
		cout << list[i].graduaters << endl ;
	}
}

void SetBinaryTreeByGraduaters( BinaryTree *&tree, vector<Item> list ) {
	BinaryTree *temp ;
	BinaryTree *pre ;
	int height = 0 ;
    
	int i = 0 ;
	while ( i < N ) {
		int j = 1 ;
		if ( tree == NULL ) {
			tree = new BinaryTree ;
			tree->leftChildPtr = NULL ;
			tree->rightChildPtr = NULL ;
			tree->parent = NULL ;
			
			Swap( tree->data, list[i] ) ;
			tree->height = j ;
		}
		else {
			temp = tree  ;
			
			while ( temp->leftChildPtr != NULL || temp->rightChildPtr != NULL ) {     // find position
				if ( list[i].graduaters < temp->data.graduaters && temp->leftChildPtr != NULL ) {
					temp = temp->leftChildPtr ;
					j++ ;
				}
				else if ( list[i].graduaters >= temp->data.graduaters && temp->rightChildPtr != NULL ) {
					temp = temp->rightChildPtr ;
					j++ ;
				}
				else {
					break ;     // found
				}
			}

			pre = temp ;

			if ( list[i].graduaters < temp->data.graduaters ) {     // insert list[i]
				temp->leftChildPtr = new BinaryTree ;
				temp = temp->leftChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;
				
				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
			else if ( list[i].graduaters >= temp->data.graduaters ) {
				temp->rightChildPtr = new BinaryTree ;
				temp = temp->rightChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;

				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
		}
		
		if ( j > height ) {
		  height = j ;
		}

		i++ ;
	}
	tree->height = height ;
}

void SetBinaryTreeBySchoolName( BinaryTree *&tree, vector<Item> list ) {
    BinaryTree *temp ;
	BinaryTree *pre ;
    int height = 0 ;
    
	int i = 0 ;
	while ( i < N ) {
		int j = 1 ;
		if ( tree == NULL ) {
			tree = new BinaryTree ;
			tree->leftChildPtr = NULL ;
			tree->rightChildPtr = NULL ;
			tree->parent = NULL ;
			
			Swap( tree->data, list[i] ) ;
			tree->height = j ;
		}
		else {
			temp = tree  ;
			
			while ( temp->leftChildPtr != NULL || temp->rightChildPtr != NULL ) {     // find position
				if ( list[i].schoolname.compare( temp->data.schoolname ) < 0 && temp->leftChildPtr != NULL ) {
					temp = temp->leftChildPtr ;
					j++ ;
				}
				else if ( list[i].schoolname.compare( temp->data.schoolname ) >= 0 && temp->rightChildPtr != NULL ) {
					temp = temp->rightChildPtr ;
					j++ ;
				}
				else {
					break ;     // found
				}
			}
			
			pre = temp ;

			if ( list[i].schoolname.compare( temp->data.schoolname ) < 0 ) {     // insert list[i]
				temp->leftChildPtr = new BinaryTree ;
				temp = temp->leftChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;
				
				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
			else if ( list[i].schoolname.compare( temp->data.schoolname ) >= 0 ) {
				temp->rightChildPtr = new BinaryTree ;
				temp = temp->rightChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;
				
				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
		}
		
		if ( j > height ) {
		  height = j ;
		}
		
		i++ ;
	}
	tree->height = height ;
}

void SearchByGraduaters( int search, BinaryTree *tree, vector<Item> &temp  ) {
	if ( tree != NULL ) {
		if ( tree->data.graduaters >= search ) {
			temp.push_back( tree->data ) ;
		}
		SearchByGraduaters( search, tree->leftChildPtr, temp ) ;
		SearchByGraduaters( search, tree->rightChildPtr, temp ) ;
	}
}

void SearchBySchool( string search, BinaryTree *tree, vector<Item> &temp  ) {
	if ( tree != NULL ) {
		if ( tree->data.schoolname.compare( search ) == 0 ) {
			temp.push_back( tree->data ) ;
		}
		SearchBySchool( search, tree->leftChildPtr, temp ) ;
		SearchBySchool( search, tree->rightChildPtr, temp ) ;
	}
}

void Find( BinaryTree *tree, string search, BinaryTree *&temp ) {
	if ( tree != NULL ) {
		if ( tree->data.schoolname.compare( search ) == 0 ) {
			temp = tree ;
		}
		Find( tree->leftChildPtr, search, temp ) ;
		Find( tree->rightChildPtr, search, temp ) ;
	}
} 

void PrintTitle() {
	cout << "*** University Graduate Information System ***" << endl ;
  	cout << "* 0. Quit                                    *" << endl ;
  	cout << "* 1. Create Two Binary Search Trees          *" << endl ;
  	cout << "* 2. Search by Number of Graduates           *" << endl ;
  	cout << "* 3. Search by School Name                   *" << endl ;
  	cout << "* 4. Removal by School Name                  *" << endl ;
  	cout << "**********************************************" << endl ;
  	cout << "Input a command(0, 1, 2, 3, 4): " ;
}

void DeleteTree1( BinaryTree *&tree, string search ) {
	BinaryTree *temp = NULL ;
	Find ( tree, search, temp ) ;

	while ( temp != NULL ) {
				cout << temp->data.departmentname  ;

		if ( temp->leftChildPtr == NULL && temp->rightChildPtr == NULL ) {
			temp->parent->leftChildPtr = NULL ;
			temp->parent->rightChildPtr = NULL ;
			delete temp ;
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr == NULL ) {
			if ( temp->parent == NULL ) {
				tree = temp->leftChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.graduaters < temp->data.graduaters ) {
				temp->parent->rightChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.graduaters > temp->data.graduaters ) {
				temp->parent->leftChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr == NULL && temp->rightChildPtr != NULL ) {
			if ( temp->parent == NULL ) {
				tree = temp->rightChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.graduaters < temp->data.graduaters ) {
				temp->parent->rightChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.graduaters > temp->data.graduaters ) {
				temp->parent->leftChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr != NULL ) {
			BinaryTree *found = temp->rightChildPtr ;
			
			while ( found->leftChildPtr != NULL ) {
				found = found->leftChildPtr ;
			}
			
			Swap( temp->data, found->data ) ;
			
			if ( found->rightChildPtr != NULL ) {
				found->parent->leftChildPtr = found->rightChildPtr ;
				found->rightChildPtr->parent = found->parent ;
				delete found ;
			}
			else {
				delete found ;
			}
		}
		
		temp = NULL ;
		Find ( tree, search, temp ) ;
	}
}

void DeleteTree2( BinaryTree *&tree, string search ) {
	BinaryTree *temp = NULL ;
	Find ( tree, search, temp ) ;
	
	while ( temp != NULL ) {
		if ( temp->leftChildPtr == NULL && temp->rightChildPtr == NULL ) {
			temp->parent->leftChildPtr = NULL ;
			temp->parent->rightChildPtr = NULL ;
			delete temp ;
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr == NULL ) {
			if ( temp->parent == NULL ) {
				tree = temp->leftChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.schoolname.compare( temp->data.schoolname ) < 0 ) {
				temp->parent->rightChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.schoolname.compare( temp->data.schoolname ) > 0 ) {
				temp->parent->leftChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr == NULL && temp->rightChildPtr != NULL ) {
			if ( temp->parent == NULL ) {
				tree = temp->rightChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.schoolname.compare( temp->data.schoolname ) < 0 ) {
				temp->parent->rightChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.schoolname.compare( temp->data.schoolname ) > 0 ) {
				temp->parent->leftChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr != NULL ) {
			BinaryTree *found = temp->rightChildPtr ;
			
			while ( found->leftChildPtr != NULL ) {
				found = found->leftChildPtr ;
			}
			
			Swap( temp->data, found->data ) ;
			
			if ( found->rightChildPtr != NULL ) {
				found->parent->leftChildPtr = found->rightChildPtr ;
				found->rightChildPtr->parent = found->parent ;
				delete found ;
			}
			else {
				delete found ;
			}
		}
		
		temp = NULL ;
		Find ( tree, search, temp ) ;
	}
}

int Max( int a, int b ) {
	if ( a >= b ) {
		return a ;
	}
	else {
		return b ;
	}
}

int Count( BinaryTree *tree ) {
	if ( tree == NULL ) {
		return 0 ;
	}
	else {
		return 1 + Max( Count( tree->leftChildPtr ), Count( tree->rightChildPtr ) ) ; 
	}
}

int main() {
	string command ;
	vector<Item> list ;
	vector<Item> temp ;
	BinaryTree *tree1 ;
	BinaryTree *tree2 ;
  	
	PrintTitle() ;
  	cin >> command ;
  
	while ( command != "0" ){
  		if ( command == "1" ) {
  			list.clear() ;
  			temp.clear() ;
  			
			cout << "Input a file number: " ;
  			string filenum ;
			cin >> filenum ;
			string filename ;
			filename = "input" + filenum + ".txt" ;
			
        	if ( ReadFile( filename, list ) ) {
        		temp = list ;
        		SelectSort( temp ) ;
		  		cout << endl ;
		  	//	PrintFile( temp, N ) ;
		  		cout << endl ;

				tree1 = NULL ;
				tree2 = NULL ;
				SetBinaryTreeByGraduaters( tree1, list ) ;
	  			SetBinaryTreeBySchoolName( tree2, list ) ;
	 			cout << "Tree heights:\n<Number of graduates> = " << tree1->height << endl << "<School name> = " << tree2->height << endl << endl ;
			}
		}
		else if ( command == "2" ) {
  			temp.clear() ;
			
			if ( list.empty() ) {
				cout << "\nPlease choose command 1 first!\n\n" ;
			}
			else {
				cout << "Input the number of graduates: " ;
				string search1 ;
				cin >> search1 ;
				
				int graduaters =  atoi( search1.c_str() ) ;
				if ( graduaters < 0 ) {
					cout << "\nThe input string " << search1 << " is not a decimal number!\n\n" ;					
				}
				else {
					SearchByGraduaters( graduaters, tree1, temp ) ;
					
					if ( temp.empty() ) {
						cout << "\nThere is no match!\n\n" ;
					}
					else {
						cout << "\nSearch results:\n" ;
						PrintFile( temp, temp.size() ) ;
						cout << endl ;
					}
				}
			}
		}
		else if ( command == "3" ) {
  			temp.clear() ;
			
			if ( list.empty() ) {
				cout << "\nPlease choose command 1 first!\n\n" ;
			}
			else {
				cout << "Input a school name: " ;
				string search2 ;
				cin >> search2 ;

				SearchBySchool( search2, tree2, temp ) ;
					
				if ( temp.empty() ) {
					cout << "\nThere is no match!\n\n" ;
				}
				else {
					cout << "\nSearch results:\n" ;
					PrintFile( temp, temp.size() ) ;
					cout << endl ;
				}
			}
		}
		else if ( command == "4" ) {
			temp.clear() ;
			
			if ( list.empty() ) {
				cout << "\nPlease choose command 1 first!\n\n" ;
			}
			else {
				cout << "\nInput a school name: " ;
				string search3 ;
				cin >> search3 ;

				SearchBySchool( search3, tree2, temp ) ;
				
				if ( temp.empty() ) {
					cout << "\nThere is no match!\n\n" ;
				}
				else {
					cout << "\nDelete records:\n" ;
					//PrintFile( temp, temp.size() ) ;
					cout << endl ;
				}
				
				DeleteTree1( tree1, search3 ) ;
				DeleteTree2( tree2, search3 ) ;
				
				int x = Count( tree1 ) ; 
				int y = Count( tree2 ) ;
	 			cout << "Tree heights:\n<Number of graduates> = " << x << endl << "<School name> = " << y << endl << endl ;


			}
		}
    	else {
      		cout << endl << "Command does not exit!\n\n" ;
		}
		PrintTitle() ;
		cin >> command ;
  	}
}
