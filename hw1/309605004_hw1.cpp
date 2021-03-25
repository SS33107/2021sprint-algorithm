#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void merge(vector<vector<unsigned int> > &array, unsigned int p, unsigned int q, unsigned int r , unsigned int compare){
	vector<unsigned int> limit(4);
	limit[0] = limit[3] = 65535;
	vector<vector<unsigned int> > left(array.begin()+p,array.begin()+q+1);
	vector<vector<unsigned int> > right(array.begin()+q+1,array.begin()+r+1);
	left.insert(left.end(),limit);
	right.insert(right.end(),limit);
	unsigned int leftidx=0,rightidx=0;
	for(unsigned int i=p;i<=r;i++){
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
void mergesort(vector<vector<int> > &array, unsigned int p, unsigned int r , unsigned int compare){
	if(p<r){
		unsigned int q = (p+r)/2;
		mergesort(array,p,q,compare);
		mergesort(array,q+1,r,compare);
		merge(array, p,q,r,compare);
	}
}

int main(int argc, char** argv) {
    ifstream ifs;
    ofstream ofs;
    string s;
    vector < vector<unsigned int> > student;
    vector < vector<unsigned int> > company;
    vector<unsigned int> aa(3);
    vector<unsigned int> bb(4);
	unsigned int student_quantity=0;
	unsigned int company_quantity=0;
    
    ifs.open(argv[1]);
   	while (getline(ifs, s)){
    	istringstream  input(s);
    	input >> aa[0] >>aa[1] >>aa[2];
    	student.push_back(aa);
		student_quantity++;
	}
    ifs.close();
    

    ifs.open(argv[2]);
    while (getline(ifs, s)){
    	istringstream  input(s);
    	input >> bb[0] >>bb[1] >>bb[2]>>bb[3];
    	company.push_back(bb);
		company_quantity++;
	}
    ifs.close();
    
    
    mergesort(student,0,student_quantity-1,0);
	mergesort(company,0,company_quantity-1,3);
	
	
    ofs.open(argv[3]);
	unsigned int result=0;
	for(unsigned int i=0;i<student_quantity;i++){
		for(unsigned int ii=company_quantity-1;ii>=0;ii--){
			if(result==0){
				if((student[i][1]>=company[ii][1]) && (student[i][2]>=company[ii][2])){
					result = company[ii][0];	
				}	
			}
		}
		ofs <<  student[i][0]<<": "<<result << "\n";
		result=0;
	}
	ofs.close();
	
    return 0;
}
