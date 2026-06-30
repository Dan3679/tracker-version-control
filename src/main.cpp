#include <iostream>
#include <string>
#include <new>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <chrono>


using namespace std;
using namespace std::chrono_literals;
namespace fs = filesystem;

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

	for (const fs::directory_entry& dir_entry :
            fs::recursive_directory_iterator("./")) {
		
		string path = dir_entry.path().string();
		file += path;
		if ( !fs::is_directory( path )){
			string size = to_string( fs::file_size( path ));
			file += " Size: " + size;

			fs::file_time_type time = dir_entry.last_write_time();
			string timeString = format("{}", time);
			file += " Time: " + timeString;
		}
				
		file += "\n";
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

	// Prepare base file
	string baseFileContent;
	ifstream BaseFileStream( baseFile );

	// Prepare file to compare against
	string compareFileContent;
	ifstream CompareFileStream( compareFile );

	list<string> deleted;
	list<string> added;

	map<string, int> baseMap;

	// Compare Loop
	while( getline( BaseFileStream, baseFileContent )) {
		baseMap[baseFileContent];
	}
	
	BaseFileStream.close();

	while( getline( CompareFileStream, compareFileContent )) {
		if( !baseMap.count( compareFileContent ) )
			added.push_back( compareFileContent );
		baseMap[compareFileContent] = 1;
	}	
		
	for (const auto& [file, value] : baseMap) {
		if( value == 0)
			deleted.push_back( file );
	}

	for (const auto& file : added)
		cout << "New file: " << file << endl;

	for (const auto& file : deleted)
		cout << "Deleted file: " << file << endl;
}


/**
 * Program argument functions
 *
 */

void init() { snapshot( "track" ); }


void status() {
	snapshot( "current" );
	compare( "track", "current" );
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
