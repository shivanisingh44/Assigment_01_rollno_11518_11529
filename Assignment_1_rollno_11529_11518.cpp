#include <iostream>		
#include <string.h>		
#include <fstream>		
#include <stdlib.h>	


using namespace std;

string g_file_name = "text_file.txt";

void displays();
void process_option(char a);
void count_probability(string search_string);
void find_words_using_dictionary_search(string search_string);
void clear_screen();
void count_paragraphs();
void find_words_using_dictionary_search(string search_string);
void KMPMainAlgo(string search_string, string main_string);
bool single_kmp(string search_string, string main_string);
void computepfArray(string search_string, int string_size, int pf[]);




int main()
{
	displays();
	return 0;
}

void displays(){

	char input_choice;	
	cout << "Menu Options: " << endl;
	cout << "0.) Clear Screen" << endl;
	cout << "1.) KMP Search" << endl;
	cout << "2.) Count number of paragraphs" << endl;
	cout << "3.) Dictionary Search" << endl;
	cout << "4.) Probability of word in document" << endl;
	cout << "5.) Exit" << endl;
	cout << "Enter your choice: ";
	cin >> input_choice;
	string futile_string;		
	getline(cin, futile_string);
	process_option(input_choice);
}


void process_option(char a){
	string search_string;		// string to be searched
	string main_string;			// Main text on which processing is being done
	switch (a){
		case '0':
			clear_screen();
			displays();
			break;
		case '1':
			cout << "Options chosen: KMP Search." << endl;
			cout << "Enter main string" << endl;
			getline(cin, main_string);
			cout << "Enter sub string to be searched" << endl;
			getline(cin, search_string);
			KMPMainAlgo(search_string, main_string);
			cout << endl;
			cout << endl;
			displays();
			break;
		case '2':
			cout << endl;
			cout << "Options chosen: Count paragraphs." << endl;
			count_paragraphs();
			cout << endl;
			cout << endl;
			displays();
			break;
		case '3':
			cout << endl;
			cout << "Options chosen: Dictionary search." << endl;
			cout << "Enter the string you want to use for dictionary search" << endl;
			cin >> search_string;
			find_words_using_dictionary_search(search_string);
			cout << endl;
			cout << endl;
			displays();
			break;
		case '4':
			cout << endl;
			cout << "Options chosen:To find the Probability of word in document." << endl;
			cout << "Enter the string you want to get probability of" << endl;
			cin >> search_string;
			count_probability(search_string);
			cout << endl;
			cout << endl;
			displays();
			break;
		case '5':
			clear_screen();
			cout << endl;
			cout << endl;
			cout << "Thank you!!" << endl;
			cout << endl;
			cout << endl;
			exit(0);
			break;
	}
}



//	Counts the probability of a certain word in the text file.

void count_probability(string search_string){
	ifstream file (g_file_name.c_str());		
	int count_words = 0;				
	if (file.is_open()){				
	string word;					
    char x ;							
    word.clear();					
    int total_words = 0;				
    bool found_char = false;
    while ((x = file.get()) != EOF)
    {
        while ( x != ' ' && x !='\n')
        {
        	found_char = true;
            word = word + x;
            if ((x = file.get()) == EOF){
	            break;
	        }
        }
        if (found_char)
        {
        	total_words++;
        	found_char = false;
        }
        if (word.length()>0){
	        if (single_kmp(search_string, word)){
	        	count_words++;
	        }
	    }
        word.clear();
    }
	file.close();
	cout << "Total words = " << total_words << endl;
	cout << "Total occurances of selected string = " << count_words << endl;
	cout << "Probability = " << (count_words*100 / total_words) << " percent" <<endl;
	}else{
		cout << "Unable to open file" << endl;
	}
}

/**
   	Finds words using dictionary search.
    
*/

void find_words_using_dictionary_search(string search_string)
{	ifstream file (g_file_name.c_str());
	cout << endl;
	cout << endl;
	cout << "If any word is found, it will be mentioned below: " << endl;
	int counter = 0;
	if (file.is_open()){
		string word = "";
	    char x ;
	    while ((x = file.get()) != EOF)
	    {
	        while ( x != ' ' && x !='\n')
	        {
	            word = word + x;
	            if ((x = file.get()) == EOF){
	            	break;
	            }
	        }
	        if (word.length()>0){
	        	if (single_kmp(search_string, word)){
	        		counter ++;
	        		cout << word << endl;
	        	}
	        }
	        word = "";
	    }
	    file.close();
	    if (counter == 0){
	    	cout << endl;
	    	cout << "No word found." << endl;
	    }else{
	    	cout << endl;
	    	cout << "Total words found: " << counter << endl;
	    }
	}
	else{
		cout << "Unable to open file" << endl;
	}
}


void clear_screen(){
	cout << string( 100, '\n' );
}

/**
   	Counts number of paragraphs in a text file.
*/

void count_paragraphs(){
	string line;
	bool found_something = false;
	ifstream file (g_file_name.c_str());
	if (file.is_open())
	{
		int count = 1;
		int internal_count = 0;
		char ch;
		bool char_found = false;
		while((ch = file.get()) != EOF)
		{
			if (ch != '\n' && ch != ' ' && ch != '\t')
			{
				found_something = true;
				char_found = true;
			}else{
				if (char_found)
				{
					if (internal_count == 1)
					{
						count += 1;
						internal_count = 0;
						char_found = false;
					}else if (ch == '\n')
					{
						internal_count += 1;
					}
				}
			}
		}
		file.close();
		if (found_something) cout << "Total paragraph count = " << count<< endl;
		else cout << "No paragraphs found" << endl;
	}else{
		cout << "file cannot be opened" << endl;
	}
}

/**
    Implements KMP algorithm for string matching.
*/
void KMPMainAlgo(string search_string, string main_string){
	int string_size = search_string.length();	
	int N = main_string.length();			

	int pf[string_size];						
	int j = 0;						
	computepfArray(search_string, string_size, pf);

	int i = 0;									//counter variable for text.

	while (i < N){
		if (search_string[j] == main_string[i])
		{
			j++;
			i++;
		}
		if (j == string_size)
		{
			cout << "Found given search string at index " << (i - j) << endl;
			j = pf[j-1];
		}
		else if (i < N && search_string[j] != main_string[i]){
			if (j != 0)
			{
				j = pf[j-1];
			}else{
				i = i + 1;
			}
		}
	}
}

bool single_kmp(string search_string, string main_string){
	int string_size = search_string.length();
	int N = main_string.length();

	int pf[string_size];
	int j = 0;

	computepfArray(search_string, string_size, pf);

	int i = 0;

	while (i < N){
		if (search_string[j] == main_string[i])
		{
			j++;
			i++;
		}
		if (j == string_size)
		{
			return true;
		}
		else if (i < N && search_string[j] != main_string[i]){
			if (j != 0)
			{
				j = pf[j-1];
			}else{
				i = i + 1;
			}
		}
	}

	return false;
}
/**
    Computes prefix array for a given pattern.
*/

void computepfArray(string search_string, int string_size, int pf[]){
	int len = 0; 
	int i;      


	pf[0] = 0;
	i = 1;

	while (i < string_size){
		if (search_string[i] == search_string[len])
		{
			len++;
			pf[i] = len;
			i++;
		}else{
			if (len != 0)
			{
				len = pf[len - 1]; // checks whether prefix and suffix are same and we can bypass characters.
			}
			else{
				pf[i] = 0;		     
				i++;
				}
		}
	}
}

