#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
//============================================================
struct MyList{
	int key;
	MyList *next;
	MyList *prev;
};
//============================================================
void makeNewList( MyList *&list );
bool add( MyList *&list, int key );
void showFromBegin( MyList *list );
void showFromEnd( MyList *list );
bool die( MyList *list, int key );
bool allMustDie( MyList *list );
bool find( MyList *list, int key );
void randMyNumbers( MyList *&list, int number );
//============================================================
//============================================================
void main(){

	int number, key1, key2, key3, key4;

	ifstream file;
	file.open( "inlab02.txt" );
	
	file >> number >> key1 >> key2 >> key3 >> key4;

	clock_t startTime = clock();

	MyList *list;
	makeNewList( list );
	//die( list, key1 );
	randMyNumbers( list, number );
	add( list, key2 );
	die( list, key2 );
	find( list, key3 );
	add( list, key4 );
	die( list, key4 );

	showFromBegin( list );
	showFromEnd( list );

	allMustDie( list );

	clock_t stopTime = clock();
	double result =  ( stopTime - startTime ) / ( CLOCKS_PER_SEC ) ;
	cout << "time: " << result << endl;

	system( "pause" );
}
//============================================================
//============================================================
void makeNewList( MyList *&list ){
	list = NULL;
}
//============================================================
bool add( MyList *&list, int key ){

	MyList *newItem = new MyList;
	newItem->next = NULL;
	newItem->prev = NULL;
	newItem->key = key;

	if( list == NULL ){
		list = new MyList;
		list->next = newItem;
		list->prev = newItem;
		return( true );
	}

	MyList *pointer = list->next; // na pierwszy element
	MyList *rememberLast = NULL;
	while( pointer ){
		if( pointer->key == key ){
			//juz taki key istnieje
			return( false );
		}else if( pointer->key < key ){
			//podany key jest wiekszy niech szuka dalej
			rememberLast = pointer;
			pointer = rememberLast->next;
		}else{
			//wlasciwe miejsce
			if( !rememberLast ){
				//przedmiot jest najmniejszy wiec staje sie head-em
				list->next = newItem;
				newItem->next = pointer;
				pointer->prev = newItem;
			}else{
				//przedmiot jest w srodku
				rememberLast->next = newItem;
				pointer->prev = newItem;
				newItem->next = pointer;
				newItem->prev = rememberLast;
			}
			return( true );
		}

	}
	//ostatni element
	list->prev = newItem;
	rememberLast->next = newItem;
	newItem->prev = rememberLast;

	return( true );
}
//============================================================
void showFromBegin( MyList *list ){

	MyList *element, *next;

	element = list->next;

	while( element ){
		cout << element->key << endl;
		next = element->next;
		element = next;
	}

}
//============================================================
void showFromEnd( MyList *list ){

	MyList *element, *prev;

	element = list->prev;

	while( element ){
		cout << element->key << endl;
		prev = element->prev;
		element = prev;
	}

}
//============================================================
bool die( MyList *list, int key ){

	MyList *pointerBegin = list->next;
	//MyList *pointerEnd = list->prev;
	MyList *rememberLast = NULL;
	//MyList *rememberLastEnd = NULL;
	MyList *forMoment = NULL;

	if( !pointerBegin ){
		return( false );// lista pusta
	}

	while( pointerBegin ){

		if( pointerBegin->key == key ){
			//znaleziono element
			if( !rememberLast ){
				list->next = pointerBegin->next;
				forMoment = pointerBegin->next;
				forMoment->prev = pointerBegin->prev;
			}else{
				rememberLast->next = pointerBegin->next;
				forMoment = pointerBegin->next;
				if( !forMoment ){
					list->prev = rememberLast;
				}else{
					forMoment->prev = pointerBegin->prev;
				}
			}
			delete pointerBegin;
			return( true );
		}else if( pointerBegin->key > key ){
			//nie ma elementu
			return( false );
		}
		//szuka dalej
		rememberLast = pointerBegin;
		pointerBegin = rememberLast->next;
	}
	return( true );
}
//============================================================
bool allMustDie( MyList *list ){
	
	MyList *pointer = list->next;
	MyList *rememberLast = NULL;

	if( !pointer ){
		delete list;
		return( false );// lista pusta
	}

	while( pointer ){
		rememberLast = pointer;
		pointer = rememberLast->next;
		delete rememberLast;
	}
	delete list;

	return( true );
}
//============================================================
bool find( MyList *list, int key ){

	MyList *pointerBegin = list->next;
	MyList *pointerEnd = list->prev;
	MyList *rememberLast = NULL;
	MyList *rememberLastEnd = NULL;

	if( !pointerBegin ){
		return( false );// lista pusta
	}

	while( pointerBegin ){

		if( pointerBegin->key == key ){
			//znaleziono element
			return( true );
		}else if( pointerEnd->key == key ){
			//znaleziono element
			return( true );
		}else if( pointerBegin->key > key ){
			//nie ma elementu
			return( false );
		}else if( pointerEnd->key < key ){
			//nie ma elementu
			return( false );
		}
		//szuka dalej
		rememberLast = pointerBegin;
		pointerBegin = rememberLast->next;

		rememberLastEnd= pointerEnd;
		pointerEnd = rememberLastEnd->prev;
	}
	return( true );
}
//============================================================
void randMyNumbers( MyList *&list, int number ){

	srand( ( unsigned int )time(NULL) );
	int key;

	for( int i = 0; i<number; i++ ){
		key = rand()%100000 + 10;
		add( list, key );
	}

}
