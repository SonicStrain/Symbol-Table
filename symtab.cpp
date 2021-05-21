#include <bits/stdc++.h>
using namespace std;

fstream ofs;
map<string,string> hash_table; 
map<string,string>::iterator itr;
//map<string,pair<int,vector<int>>> attr;
map<string,pair<pair<int,int>,vector<pair<int,int>>>> attr;


void lookUpValue(string key){

    string result = "Not Found!";
    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
        if(itr->first == key){
            cout << "\t<KEY>\t<VALUE>\n";
            cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
            
            result = "Found!";
            break;
        }
    }
    cout << "\n" << result << "\n";
}

bool lookUpBool(string key){

    bool result = false;
    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
        if(itr->first == key){
            
            result = true;
            break;
        }
    }
    return result;
}

void findDeclaration(string key){
    pair<pair<int,int>,vector<pair<int,int>>> p;

    if(lookUpBool(key)){
        for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
            if(itr->first == key){
                p = attr[itr->first];
                if(p.first.first != -1){
                    cout << "\nDeclaration Line : " << p.first.first << "\n";
                }else{
                    cout << "\nDeclaration not needed!\n";
                }
                

                break;
            }
        }
    }else{
        cout << "key does not exist" << "\n";
    }

    
}

void findReferances(string key){
    pair<pair<int,int>,vector<pair<int,int>>> p;
    vector <pair<int,int>> v;
    string refs = "";

    if(lookUpBool(key)){
        for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
            if(itr->first == key){
                p = attr[itr->first];
                v = p.second;
                for(int i=0;i<(int)v.size();i++){
                    refs += to_string(v[i].first);
                    refs += ",";
                }

                cout << "\nReferanced Lines : " << refs << "\n";

                break;
            }
        }
    }else{
        cout << "key does not exist" << "\n";
    }
}

int helperForScope(string key){

    int result = 0;
    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
        if(itr->first == key){
            
            if(itr->second == "Identifier"){
                result = 2;
            }else{
                result = 1;
            }

            break;
        }
    }
    return result;
}

void findScope(string key,int lineno){
    int keyType = helperForScope(key);
    pair<pair<int,int>,vector<pair<int,int>>> p;
    vector <pair<int,int>> v;
    int flag = 1,notFound = 1;

    if(keyType == 2){

        if(notFound){

        for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
            if(itr->first == key){
                p = attr[itr->first];
                if(p.first.first == lineno){
                    cout << "\nScope : " << p.first.second << "\n";
                    notFound = 0;
                    flag = 0;
                    break;
                }
                
            }
        }

        }

        if(notFound){

        for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
            if(itr->first == key){
                p = attr[itr->first];
                v = p.second;
                for(int i=0;i<(int)v.size();i++){
                    if(v[i].first == lineno){
                        cout << "\nScope : " << v[i].second << "\n";
                        flag = 0;
                        notFound = 0;
                        break;
                    }
                }

                break;
            }
        }

        }

    }else if(keyType == 1){
        for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
            if(itr->first == key){
                p = attr[itr->first];
                v = p.second;
                for(int i=0;i<(int)v.size();i++){
                    if(v[i].first == lineno){
                        cout << "\nScope : " << v[i].second << "\n";
                        flag = 0;
                        break;
                    }
                }

                break;
            }
        }

       

    }else{
        cout << "\nkey does not exist" << "\n";
    }
    if(flag) cout << "\nNo key present at line " << lineno << "\n";
}


void printTable(){

    ofs.open("table.txt", ios::out | ios::trunc);

    map<string,string>::iterator itr;
    pair<pair<int,int>,vector<pair<int,int>>> p;
    vector <pair<int,int>> v;
    string refs = "";

    ofs << "\tNAME\tCLASS\tDECLARED\tREFERANCED\n";
    ofs << "\t------------------------------------\n";

    cout << "\tNAME\tCLASS\tDECLARED\tREFERANCED\n";
    cout << "\t------------------------------------\n";

    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
        p = attr[itr->first];
        v = p.second;

        for(int i=0;i<(int)v.size();i++){
            refs += "[ "+ to_string(v[i].first) + " " + to_string(v[i].second) + " ]";
            refs += ",";
        }

        ofs << '\t' << itr->first
             << '\t' << itr->second
             << '\t' << "[ " <<p.first.first << " " << p.first.second << " ]"
             << '\t' << refs << '\n';
        
        cout << '\t' << itr->first
             << '\t' << itr->second
             << '\t' << "[ " <<p.first.first << " " << p.first.second << " ]"
             << '\t' << refs << '\n';
        
        refs = "";
    }
    ofs.close();
}

void symbolTable(){
    //take the file as input----------------------------
    string inputFile , input;
	inputFile = "../sampleCode/";
	//cout << "Enter a file: " ;
	//cin >> input;

	input = inputFile + "test1.txt" ;
    std::ifstream filePath;
	filePath.open(input);
    //--------------------------------------------------

    //get the values into hashmap
	
    ifstream paramFile;
    paramFile.open("demo_table.txt");
    string line;
    string key;
    string value;
    string temp;
    
    while ( paramFile.good() ){
        getline(paramFile, line);
        istringstream ss(line);
        ss >> key >> value; 
        if(value == "Identifier"){
            hash_table[key] = value;
        }
        
    }
    paramFile.close();
    //--------------------------------------------------
    // for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {
    //     cout << '\t' << itr->first
    //          << " " << itr->second << '\n';
    // }

    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr) {

        if(itr->second == "Identifier"){
            //if(filePath.is_open()){
                unsigned int curLine = 0; 
                string line1;
                bool flag = true;
                vector <pair<int,int>> v;
                pair<int,int> p;
                int decLine;
                int scpnum = 0;
                while(!filePath.eof()) { 
                    getline(filePath, line1);
                    curLine++;

                    //find scope
                    if(line1.find("{") != string::npos){
                        scpnum++;
                    }
                    if (line1.find(itr->first) != string::npos) {
                        //cout << "found: " << itr->second << "   line: " << curLine << endl;
                        
                        if(flag){
                            decLine = curLine;
                            p = make_pair(decLine,scpnum);
                            flag = false;
                        }else{
                            v.push_back(make_pair(curLine,scpnum));
                        }
                    }

                    if(line1.find("}") != string::npos){
                        scpnum--;
                    }
                }

                //add to attribute map
                attr[itr->first] = make_pair(p,v);
                v.clear();

                filePath.clear();
                filePath.seekg(0);
           //}
        }else{
            //if(filePath.is_open()){
                unsigned int curLine = 0; 
                string line1;
                vector <pair<int,int>> v;
                int scpnum = 0;
                while(getline(filePath, line1)) {
                    curLine++;
                    //find scope
                    if(line1.find("{") != string::npos){
                        scpnum++;
                    }

                    if (line1.find(itr->first) != string::npos) {
                        //cout << "found: " << itr->second << "   line: " << curLine << endl;

                        //add to the referance list
                        v.push_back(make_pair(curLine,scpnum));
                    }
                    // for(int i=0;i<(int)line1.size();i++){
                    //     temp = line1[i];
                    //     if( temp == itr->first){
                    //         v.push_back(make_pair(curLine,scpnum));
                    //     }
                    // }

                    if(line1.find("}") != string::npos){
                        scpnum--;
                    }
                }
                //add to attribute map
                attr[itr->first] = make_pair(make_pair(-1,-1),v);
                v.clear();

                filePath.clear();
                filePath.seekg(0);
          // }
        }  
    }

    string holder;

    for (itr = hash_table.begin(); itr != hash_table.end(); ++itr){
        while(!filePath.eof()) { 
            getline(filePath, line);
            if(line.find("string") != string::npos){
                    holder = "string";
            }else if(line.find("int") != string::npos){
                    holder = "int";
            }else if(line.find("float") != string::npos){
                    holder = "float";
            }
            if(line.find(itr->first) != string::npos){
                hash_table[itr->first] = holder;
                if(itr->first == "main"){
                    hash_table[itr->first] = "function";
                }
                break;
            }
        }
        filePath.clear();
        filePath.seekg(0);
    }

    filePath.close();
}

int main(){

    symbolTable();
    
    //--------------------------------------------------------------------------------------
    printTable();

    cout << "\n------------------------------------------------------------------------\n";

    int selection = -1;
    string keyID;
    int lineno;

    while (selection != 42)
	{
		std::cout << "\nEnter Your Choice:\n"
						<< "\t1.Look up Symbol Table.\n"
                        << "\t2.Look up Declaration.\n"
                        << "\t3.Look up Referanced Lines.\n"
                        << "\t4.Look up Scope.\n"
						<< "\t0. exit" << std::endl;
		std::cout << "\nEnter a value [0/1/2/3/4] -> ";
		std::cin >> selection;
		if (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			continue;
		}

		switch (selection)
		{
			
			case 1:				
                cout << "\nEnter key : ";
                cin >> keyID;
                lookUpValue(keyID);	
                cout << "\n------------------------------------------------------------------------\n";
				break;
            case 2:
                cout << "\nEnter key : ";
                cin >> keyID;
                findDeclaration(keyID);
                cout << "\n------------------------------------------------------------------------\n";
                break;
            case 3:
                cout << "\nEnter key : ";
                cin >> keyID;
                findReferances(keyID);
                cout << "\n------------------------------------------------------------------------\n";
                break;
            case 4:
                cout << "\nEnter key : ";
                cin >> keyID;
                cout << "\nEnter line no : ";
                cin >> lineno;
                findScope(keyID,lineno);
                cout << "\n------------------------------------------------------------------------\n";
                break;
			case 0:
				selection = 42;
		}

	}

    return 0;
}