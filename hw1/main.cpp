#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void merge(vector<vector<int> > &array, int p,int q,int r ,int compare){
	vector<int> limit(4);
	limit[0] =limit[3] = 65535;
	vector<vector<int> > left(array.begin()+p,array.begin()+q+1);
	vector<vector<int> > right(array.begin()+q+1,array.begin()+r+1);
	left.insert(left.end(),limit);
	right.insert(right.end(),limit);
	int leftidx=0,rightidx=0;
	for(int i=p;i<=r;i++){
		if(left[leftidx][compare] <= right[rightidx][compare]){
			array[i] = left[leftidx];
			leftidx++;
		}
		else{
			array[i] = right[rightidx];
			rightidx++;
		}
	}
}
void mergesort(vector<vector<int> > &array, int p,int r ,int compare){
	if(p<r){
		int q = (p+r)/2;
		mergesort(array,p,q,compare);
		mergesort(array,q+1,r,compare);
		merge(array, p,q,r,compare);
	}
}

int main(int argc, char** argv) {
    ifstream ifs;
    ofstream ofs;
    string s;
    vector < vector<int> > student;
    vector < vector<int> > company;
    vector<int> aa(3);
    vector<int> bb(4);
    int student_quantity=0;
    int company_quantity=0;
    
    //ifs.open("student.txt");
    ifs.open(argv[1]);
   	while (getline(ifs, s)){
    	istringstream  input(s);
    	input >> aa[0] >>aa[1] >>aa[2];
    	student.push_back(aa);
	//	cout <<  student[student_quantity][0] <<"   "<< student[student_quantity][1] <<"   "<< student[student_quantity][2] <<"   " << endl << endl; 	
		student_quantity++;
	}
    ifs.close();
    

    //ifs.open("company.txt");
    ifs.open(argv[2]);
    while (getline(ifs, s)){
    	istringstream  input(s);
    	input >> bb[0] >>bb[1] >>bb[2]>>bb[3];
    	company.push_back(bb);
	//	cout <<  company[company_quantity][0] <<"   "<< company[company_quantity][1] <<"   "<< company[company_quantity][2] <<"   " << company[company_quantity][3]<< endl << endl; 
		company_quantity++;
	}
    ifs.close();
    
    
    mergesort(student,0,student_quantity-1,0);
	mergesort(company,0,company_quantity-1,3);
	
	
    //ofs.open("output.txt");
    ofs.open(argv[3]);
	int result=0;
	for(int i=0;i<student_quantity;i++){
		for(int ii=company_quantity-1;ii>=0;ii--){
			if(result==0){
				if((student[i][1]>=company[ii][1]) && (student[i][2]>=company[ii][2])){
					result = company[ii][0];	
				}	
			}
		}
	//	cout << student[i][0]<<" : "<<result<<endl;
		ofs <<  student[i][0]<<": "<<result << "\n";
		result=0;
	}
	ofs.close();
	
    return 0;
}
