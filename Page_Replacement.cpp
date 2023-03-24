#include <iostream> // cout, endl
#include <fstream> // open, is_open, close, ignore
#include <string> // string, find_last_of, substr
#include <string.h> // string, find_last_of, substr
#include <vector> // vector, push_back
#include <cstdlib> // system, atoi
#include <iomanip> // setw
#include <sstream>
#include <stdio.h>
#include <time.h>


using namespace std;

typedef struct data_inf {
	int ID = 0 ;
	string queue = "" ;
	string is_Faults = "" ;
} information;

typedef struct page {
	int Page_Faults = 0 ;
	int Page_Replaces = 0 ;	
	vector <data_inf> ID ;
} page_data;

typedef struct lfu {
	int ID = 0 ;
	int run_time = 0 ;
	int Counter = 0 ;	
} LFU_data;

typedef struct arbpr {
	int ID = 0 ;
	int zero_num = 0 ;
	int run_time = 0 ;
	string shifter = "" ;	
} ARB_data;

string input = "" ;
int page_frame = 0 ;

vector <int> process_ID ;
page FIFO ;
page LRU ;
page LFU ;
page MFU ;
page ARB ;
page SCPR ;


bool readFile() {

	cout << endl << "Input file name : " ;
	cin >> input ;

	fstream file ;
	string tempname = input + ".txt" ;
	file.open( tempname.c_str(), ios::in);	
	
	if (!file.is_open()){
		cout << "檔案無法開啟\n" ;
		return false ;		
	}
	else {
		string temp_com = "" ;
		getline(file,temp_com) ;
		stringstream ss(temp_com.c_str()); 

    	ss >> page_frame ;
	    
	    string temp = "" ;
	    getline(file,temp) ;

		while( !file.eof()) { 
			for(int i = 0; i < temp.size();i ++){
				if(temp[i]!= ' '){
    				int num  = (int)temp[i] - 48 ;
					process_ID.push_back(num) ;
				}
			}
			
			getline(file,temp) ;

		}
		
		file.close() ;
	}
	
	return true ;
} 

void do_FIFO(){
	vector <int> FIFO_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		
		for(int k = 0 ; k < FIFO_queue.size() ; k ++ ){
			if (process_ID[i] == FIFO_queue[k]){
				exits = true ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			string temp_queue = "" ;
			for(int j = 0 ; j < FIFO_queue.size() ; j ++ ){		
				ostringstream os; 
				os << FIFO_queue[j] ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			temp.is_Faults = "F" ;
			FIFO.Page_Faults = FIFO.Page_Faults + 1 ;
			
			if(FIFO_queue.size() < page_frame){
				FIFO_queue.insert(FIFO_queue.begin(),process_ID[i]) ;
			}
			else{
				FIFO.Page_Replaces = FIFO.Page_Replaces + 1 ;
				FIFO_queue.insert(FIFO_queue.begin(),process_ID[i]) ;
				FIFO_queue.pop_back() ;
			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < FIFO_queue.size() ; j ++ ){		
				ostringstream os; 
				os << FIFO_queue[j] ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		FIFO.ID.push_back(temp) ;
		
	}
}

void do_LRU(){
	vector <int> LRU_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		int index = 0 ;
		for(int k = 0 ; k < LRU_queue.size() ; k ++ ){
			if (process_ID[i] == LRU_queue[k]){
				index = k ;
				exits = true ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			LRU_queue.erase(LRU_queue.begin()+index) ;
			LRU_queue.insert(LRU_queue.begin(),process_ID[i]) ;

			string temp_queue = "" ;
			for(int j = 0 ; j < LRU_queue.size() ; j ++ ){		
				ostringstream os; 
				os << LRU_queue[j] ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			temp.is_Faults = "F" ;
			LRU.Page_Faults = LRU.Page_Faults + 1 ;
			
			if(LRU_queue.size() < page_frame){
				LRU_queue.insert(LRU_queue.begin(),process_ID[i]) ;
			}
			else{
				LRU.Page_Replaces = LRU.Page_Replaces + 1 ;
				LRU_queue.insert(LRU_queue.begin(),process_ID[i]) ;
				LRU_queue.pop_back() ;
			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < LRU_queue.size() ; j ++ ){		
				ostringstream os; 
				os << LRU_queue[j] ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		LRU.ID.push_back(temp) ;
		
	}
}

void do_LFU(){
	vector <lfu> LFU_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		int num = 0 ;
		for(int k = 0 ; k < LFU_queue.size() ; k ++ ){
			if (process_ID[i] == LFU_queue[k].ID){
				exits = true ;
				num = k ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			LFU_queue[num].Counter = LFU_queue[num].Counter + 1 ;
			LFU_queue[num].run_time = i ;
			string temp_queue = "" ;
			for(int j = 0 ; j < LFU_queue.size() ; j ++ ){		
				ostringstream os;  
				os << LFU_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			temp.is_Faults = "F" ;
			LFU.Page_Faults = LFU.Page_Faults + 1 ;

			lfu temp_LFU ;
			temp_LFU.ID = process_ID[i];
			temp_LFU.run_time = i ;
			temp_LFU.Counter = 0 ;
			
			if(LFU_queue.size() < page_frame){
				LFU_queue.insert(LFU_queue.begin(),temp_LFU) ;
			}
			else{
				LFU.Page_Replaces = LFU.Page_Replaces + 1 ;
				int small = LFU_queue[0].Counter ;
				int index = 0 ;
				int t_time = LFU_queue[0].run_time ;
				for(int k = 0 ; k < LFU_queue.size() ; k ++ ){
					if(LFU_queue[k].Counter < small  ){
						t_time = LFU_queue[k].run_time ;
						small = LFU_queue[k].Counter ;
						index = k ;
					}
					else if (LFU_queue[k].Counter == small && LFU_queue[k].run_time <= t_time){
						t_time = LFU_queue[k].run_time ;
						small = LFU_queue[k].Counter ;
						index = k ;						
					}
				}
				
				
				LFU_queue.erase(LFU_queue.begin()+index) ;				
				LFU_queue.insert(LFU_queue.begin(),temp_LFU) ;

			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < LFU_queue.size() ; j ++ ){		
				ostringstream os; 
				os << LFU_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		LFU.ID.push_back(temp) ;
		
	}
}

void do_MFU(){
	vector <lfu> MFU_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		int num = 0 ;
		for(int k = 0 ; k < MFU_queue.size() ; k ++ ){
			if (process_ID[i] == MFU_queue[k].ID){
				exits = true ;
				num = k ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			MFU_queue[num].Counter = MFU_queue[num].Counter + 1 ;
			MFU_queue[num].run_time = i ;
			string temp_queue = "" ;
			for(int j = 0 ; j < MFU_queue.size() ; j ++ ){		
				ostringstream os; 
				os << MFU_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			temp.is_Faults = "F" ;
			MFU.Page_Faults = MFU.Page_Faults + 1 ;
			lfu temp_MFU ;
			temp_MFU.run_time = i ;	
			temp_MFU.ID = process_ID[i];
			temp_MFU.Counter = 0 ;
			
			if(MFU_queue.size() < page_frame){
				MFU_queue.insert(MFU_queue.begin(),temp_MFU) ;
			}
			else{
				MFU.Page_Replaces = MFU.Page_Replaces + 1 ;
				int small = MFU_queue[0].Counter ;
				int index = 0 ;
				int t_time = MFU_queue[0].run_time ;
				for(int k = 0 ; k < MFU_queue.size() ; k ++ ){
					if(MFU_queue[k].Counter > small  ){
						t_time = MFU_queue[k].run_time ;
						small = MFU_queue[k].Counter ;
						index = k ;
					}
					else if (MFU_queue[k].Counter == small && MFU_queue[k].run_time <= t_time){
						t_time = MFU_queue[k].run_time ;
						small = MFU_queue[k].Counter ;
						index = k ;						
					}
				}


				
				MFU_queue.erase(MFU_queue.begin()+index) ;				
				MFU_queue.insert(MFU_queue.begin(),temp_MFU) ;

			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < MFU_queue.size() ; j ++ ){		
				ostringstream os; 
				os << MFU_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		MFU.ID.push_back(temp) ;
		
	}
}

void do_ARB(){
	vector <arbpr> ARB_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		int num = 0 ;
		for(int k = 0 ; k < ARB_queue.size() ; k ++ ){
			if (process_ID[i] == ARB_queue[k].ID){
				exits = true ;
				num = k ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			for(int k = 0 ; k < ARB_queue.size() ; k ++ ){
				if (k == num){
					ARB_queue[k].shifter = "1" + ARB_queue[k].shifter  ;
				}
				else {
					ARB_queue[k].shifter = "0" + ARB_queue[k].shifter  ;
				}
			}

			string temp_queue = "" ;
			for(int j = 0 ; j < ARB_queue.size() ; j ++ ){		
				ostringstream os; 
				os << ARB_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			for(int k = 0 ; k < ARB_queue.size() ; k ++ ){
				ARB_queue[k].shifter = "0" + ARB_queue[k].shifter  ;
			}
			
			temp.is_Faults = "F" ;
			ARB.Page_Faults = ARB.Page_Faults + 1 ;

			arbpr temp_ARB ;
			temp_ARB.ID = process_ID[i];
			temp_ARB.shifter = "1" ;
			
			if(ARB_queue.size() < page_frame){
				ARB_queue.insert(ARB_queue.begin(),temp_ARB) ;
			}
			else{
				ARB.Page_Replaces = ARB.Page_Replaces + 1 ;
				
				//int small = strtol(ARB_queue[0].shifter.c_str(),NULL,2);

				for(int k = 0 ; k < ARB_queue.size() ; k ++ ){

					int dex = 0 ;
					ARB_queue[k].zero_num = 0 ;
					while(ARB_queue[k].shifter[dex] != '1'){
						ARB_queue[k].zero_num = ARB_queue[k].zero_num + 1 ;
						dex = dex + 1 ;
					}

				}
				
				int index = 0 ;
				int small = ARB_queue[0].zero_num ;
				for(int k = 0 ; k < ARB_queue.size() ; k ++ ){

					if(ARB_queue[k].zero_num  >= small){
						small = ARB_queue[k].zero_num ;
						index = k ;
					}

				}
				
				ARB_queue.erase(ARB_queue.begin()+index) ;				
				ARB_queue.insert(ARB_queue.begin(),temp_ARB) ;

			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < ARB_queue.size() ; j ++ ){		
				ostringstream os; 
				os << ARB_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		ARB.ID.push_back(temp) ;
		
	}
}

void do_SCPR(){
	vector <arbpr> SCPR_queue ; 
	for(int i = 0 ; i < process_ID.size(); i++){
		bool exits = false ;
		int num = 0 ;
		for(int k = 0 ; k < SCPR_queue.size() ; k ++ ){
			if (process_ID[i] == SCPR_queue[k].ID){
				exits = true ;
				num = k ;
			}
		}
		
		data_inf temp ;
		temp.ID = process_ID[i] ;
		
		if(exits){
			SCPR_queue[num].shifter = "1" ;
			SCPR_queue[num].run_time = i ;
			string temp_queue = "" ;
			for(int j = 0 ; j < SCPR_queue.size() ; j ++ ){		
				ostringstream os; 
				os << SCPR_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;
		}	
		else{
			
			temp.is_Faults = "F" ;
			SCPR.Page_Faults = SCPR.Page_Faults + 1 ;

			arbpr temp_SCPR ;
			temp_SCPR.ID = process_ID[i];
			temp_SCPR.shifter = "1" ;
			temp_SCPR.run_time = i ;
			if(SCPR_queue.size() < page_frame){
				SCPR_queue.insert(SCPR_queue.begin(),temp_SCPR) ;
			}
			else{
				SCPR.Page_Replaces = SCPR.Page_Replaces + 1 ;
				int index = 0 ;
				bool find = false ;
				while(SCPR_queue[2].shifter == "1"){
					SCPR_queue[2].shifter = "0" ;
					arbpr temp_SCPR2 ;
					temp_SCPR2 = SCPR_queue[2] ;
					SCPR_queue.erase(SCPR_queue.begin()+2) ;				
					SCPR_queue.insert(SCPR_queue.begin(),temp_SCPR2) ;					
					
				}

				SCPR_queue.erase(SCPR_queue.begin()+2) ;				
				SCPR_queue.insert(SCPR_queue.begin(),temp_SCPR) ;

			}
			
			string temp_queue = "" ;
			for(int j = 0 ; j < SCPR_queue.size() ; j ++ ){		
				ostringstream os; 
				os << SCPR_queue[j].ID ; 
				temp_queue =  temp_queue + os.str() ;
			}
			temp.queue = temp_queue ;			
			
		}
		
		SCPR.ID.push_back(temp) ;
		
	}
}

void outputfile(){
	fstream outputfile ;
	string outputname = input + "_output.txt" ;
	outputfile.open( outputname.c_str(), ios::out) ; //開啟寫入模式 
	
	outputfile << "--------------FIFO-----------------------"<< endl ;
	for(int i = 0 ; i < FIFO.ID.size() ; i ++ ){
		outputfile << left << setw(10) << FIFO.ID[i].ID << left << setw(10) << FIFO.ID[i].queue <<  left << setw(10) << FIFO.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << FIFO.Page_Faults << "  Page Replaces = " << FIFO.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;
	
	outputfile << "--------------LRU-----------------------"<< endl ;
	for(int i = 0 ; i < LRU.ID.size() ; i ++ ){
		outputfile << left << setw(10) << LRU.ID[i].ID << left << setw(10) << LRU.ID[i].queue << left << setw(10) << LRU.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << LRU.Page_Faults << "  Page Replaces = " << LRU.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;
	
	outputfile << "--------------Additional Reference Bits-----------------------"<< endl ;
	for(int i = 0 ; i < ARB.ID.size() ; i ++ ){
		outputfile << left << setw(10) << ARB.ID[i].ID << left << setw(10) << ARB.ID[i].queue << left << setw(10) << ARB.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << ARB.Page_Faults << "  Page Replaces = " << ARB.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;
	
	outputfile << "--------------Second chance Page-----------------------"<< endl ;
	for(int i = 0 ; i < SCPR.ID.size() ; i ++ ){
		outputfile << left << setw(10) << SCPR.ID[i].ID << left << setw(10) << SCPR.ID[i].queue << left << setw(10) << SCPR.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << SCPR.Page_Faults << "  Page Replaces = " << SCPR.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;
	
	outputfile << "--------------Least Frequently Used Page Replacement-----------------------"<< endl ;
	for(int i = 0 ; i < LFU.ID.size() ; i ++ ){
		outputfile << left << setw(10) << LFU.ID[i].ID << left << setw(10) << LFU.ID[i].queue <<  left << setw(10) << LFU.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << LFU.Page_Faults << "  Page Replaces = " << LFU.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;	

	outputfile << "--------------Most Frequently Used Page Replacement-----------------------"<< endl ;
	for(int i = 0 ; i < MFU.ID.size() ; i ++ ){
		outputfile << left << setw(10) << MFU.ID[i].ID << left << setw(10) << MFU.ID[i].queue << left << setw(10) << MFU.ID[i].is_Faults << endl ;
	}
	
	outputfile  << "Page Fault = " << MFU.Page_Faults << "  Page Replaces = " << MFU.Page_Replaces << " Page Frames = " << page_frame << endl << endl ;	
	
	outputfile.close() ;  
}

int main(void) {	
	readFile() ;
	do_FIFO() ;
	do_LRU() ;
	do_ARB() ;	
	do_SCPR() ;
	do_LFU() ;
	do_MFU() ;


	outputfile() ;
	

	
	return 0;
} // end of main









