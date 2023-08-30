// tower of hanoi, txt version
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <string>
/*
void toh_text(int n, const char* start, const char* aux, const char* end){
    if (n==1){
        std::cout<<" move "<< n<< " from "<< start<< " to "<< end<<std::endl;
        return;
    }
    toh_text(n-1,  start, end, aux);
    std::cout<<"move "<< n<< " from "<< start<< " to "<<end<<std::endl;
    toh_text( n-1,  aux, start,end);
}

int main() {
    // Write C++ code here
    toh_text(6,"A","B","C");
    return 0;
}
*/


// Online C++ compiler to run C++ program online
// Online C++ compiler to run C++ program online
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <algorithm>


struct Bundle {
    const char* name;
    std::vector<int> values;
};

int toh(int n, const char* start, const char* aux, const char* end, std::vector<int> & start_v,std::vector<int> & aux_v,std::vector<int> & end_v, int &count){
    if (n==1){
        end_v.push_back(start_v.back());
        start_v.pop_back();
        count ++;
        Bundle bundles[]={
            {start,start_v},
            {aux,aux_v},
            {end,end_v},
        };
        const char* names[] = {"A", "B", "C"};
        for (int q=0; q<3;q++){
            for (int i=0; i<3; i++){
                if (bundles[i].name==names[q]){
                    std::cout << bundles[i].name << " ";
                    for (int j = 0; j < bundles[i].values.size(); j++) {
                        std::cout << bundles[i].values[j] << " ";
                    }
                    std::cout << std::endl;
                }
            }

        }
        std::cout << std::endl;

        return count;
    }
    toh(n-1,  start, end, aux, start_v, end_v,aux_v, count);
    end_v.push_back(start_v.back());
    start_v.pop_back();
    count ++;
    Bundle bundles[]={
            {start,start_v},
            {aux,aux_v},
            {end,end_v},
        };
    const char* names[] = {"A", "B", "C"};
    for (int q=0; q<3;q++){
        for (int i=0; i<3; i++){
            if (bundles[i].name==names[q]){
                std::cout << bundles[i].name << " ";
                for (int j = 0; j < bundles[i].values.size(); j++) {
                    std::cout << bundles[i].values[j] << " ";
                }
                std::cout << std::endl;
            }
        }

    }
    std::cout << std::endl;
    
    toh( n-1,  aux, start,end, aux_v, start_v,end_v, count);
    return count;
}

int main() {
    // Write C++ code here
    while (true){
        int n;
        std::cin.clear(); 
        
        std::cout << "Enter a number: ";
       
    
        std::cin >> n;
        if (std::cin.fail() or (n <=0)) {
            std::cin.clear();   // clear the error flag
            std::cin.ignore();  // ignore any remaining input
            continue;
        }
        
        std::vector<int> start_v = {};
        for (int i=n;i>=1;i-- ){
            start_v.push_back(i);
        }
        std::vector<int> aux_v{};
        std::vector<int> end_v{};
        std::cout<<"A"<<" : ";
        for (int i = 0; i < start_v.size(); i++) {
        std::cout << start_v[i] << " ";
        }
        std::cout << std::endl;
        std::cout<<"B"<<" : ";
        for (int i = 0; i < aux_v.size(); i++) {
        std::cout << aux_v[i] << " ";
        }
        std::cout << std::endl;
        std::cout<<"C"<<" : ";
        for (int i = 0; i < end_v.size(); i++) {
        std::cout << end_v[i] << " ";
        };
        std::cout << std::endl;
        std::cout << std::endl;
        int count =0;
        count = toh(n, "A", "B", "C", start_v, aux_v, end_v, count);
        std::cout<< "No. of steps: " << count;
        std::cout << std::endl;
        


    }
    
    return 0;
}
