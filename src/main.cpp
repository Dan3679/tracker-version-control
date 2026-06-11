#include <iostream>
#include <string>
#include <new>


using namespace std;

/**
 * !! Not collision resistent - Usable only depending on scope
 *
 * @param string s - The string to be converted
 *
 */
int convertToInt( string s ) {
		
	int value = 0;

    	for (long unsigned int i = 0; i < s.length(); i++) {
        	value += static_cast<int>( s[i] );
	}
	
	cout << value << endl;


    	return value; 
}



int main ( int argc, char *argv[] ) {
		
	if ( argc < 2 )	{ 
		cout << "Please specify one of the following arguments:\ninit, status, commit" << endl;
		return 0; 
	}
	
	int value = convertToInt( argv[1] );

	switch ( value ) {	

		case 436 :
			cout << argv[1] << endl;
			break;
		case 676 :
			cout << argv[1] << endl;
			break;
		case 649 :
			cout << argv[1] << endl;
			break;
		default:
			cout << "Argument unknown" << endl;
			break;
	}

	return 0;
}
