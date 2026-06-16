#include <iostream>
#include <string>
#include <new>
#include <filesystem>
#include <fstream>

using namespace std;

/**
 * Deterministic function to convert string to int
 * Not collision resistent - Usable only depending on scope
 *
 * @param string s - The string to be converted
 *
 */
int convertToInt( string s ) {
		
	int value = 0;

    	for (long unsigned int i = 0; i < s.length(); i++) {
        	value += static_cast<int>( s[i] );
	}

    	return value; 
}

/**
 *	Recursively iterate over filesystem entries of current directory
 *	Write names of entries in a file
 */
void snapshot( const char* filename ) {

	auto entry_length{3UZ};

	string file = "";

	for (const filesystem::directory_entry& dir_entry :
            filesystem::recursive_directory_iterator("./")) {
	
		file += dir_entry.path().string();
		file += '\n';

        	if (auto l{dir_entry.path().string().length()}; entry_length < l) {
			entry_length = l;
    
		}
	}
	fstream( filename, ios::out | ios::trunc ) << file;
}

/**
 *	Compare two filesystem map files
 *	To-Do : Actually compare, so far it only outputs line by line
 *	
 *	@param string baseFile
 *	@param string compareFile
 */
void compare( string baseFile, string compareFile ) {
	//string baseContent;
	//fstream( baseFile, ios::in) >> baseContent;
	//cout << baseContent;
	string baseFileContent;
	ifstream BaseFileStream( baseFile );
	while( getline(BaseFileStream, baseFileContent) ) {
		// While we are not at the end.
		cout << baseFileContent;	
	}
	BaseFileStream.close();
}

void init() { snapshot( "track" ); }


void status() {
	snapshot( "current" );
	compare( "current", "track" );
}


void commit() {}

int main ( int argc, char *argv[] ) {
		
	if ( argc < 2 )	{ 
		cout << "Please specify one of the following arguments:\ninit, status, commit" << endl;
		return 0; 
	}
	
	int value = convertToInt( argv[1] );

	switch ( value ) {	

		case 436 :
			init();
			break;
		case 676 :
			status();
			break;
		case 649 :
			commit();
			break;
		default:
			cout << "Argument unknown" << endl;
			break;
	}

	return 0;
}
