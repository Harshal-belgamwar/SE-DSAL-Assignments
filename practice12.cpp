#include<iostream>
#include<fstream>
using namespace std;

class student{
public:
    int rollno;
    char name[30],address[50];
    bool isDeleted;

   
};

const char* filename="student.txt";

void insertion(){
    fstream file(filename,ios::binary|ios::app);
    student s;

    if(!file.is_open()){
        cerr<<"Error opening file!"<<endl;
        return;
    }

    cout<<"Enter name:";
    cin>>s.name;

    cout<<"Enter roll no:";
    cin>>s.rollno;

    cout<<"enter address:";
    cin>>s.address;

    s.isDeleted=false;

    file.write((char*)&s,sizeof(s));
    cout<<"Data Inserted!"<<endl;
    file.close();
}

void deletion(){
    fstream file(filename,ios::binary|ios::in|ios::out);
    student s;
    bool found=false;
    if(!file.is_open()){
        cerr<<"Error opening file!"<<endl;
        return;
    }

    int roll;
    cout<<"enter roll no to be deleted!"<<endl;
    cin>>roll;

    while(file.read((char*)&s,sizeof(s))){
        if(s.rollno==roll && !s.isDeleted){
            found=true;
            s.isDeleted=true;
            file.seekp(-int(sizeof(s)),ios::cur);
            file.write((char*)&s,sizeof(s));
            cout<<"Data is deleted!"<<endl;
            file.close();
            return;
        }
    }
    file.close();
    if(!found) cout<<"Data not found!"<<endl;

}

void update(){
    fstream file(filename,ios::binary|ios::in|ios::out);
    student s;
    bool found=false;
    if(!file.is_open()){
        cerr<<"Error opening file!"<<endl;
        return;
    }

    int roll;
    cout<<"enter roll no to be updated!"<<endl;
    cin>>roll;

   

    while(file.read((char*)&s,sizeof(s))){
        if(s.rollno==roll && !s.isDeleted){
            found=true;
            
            cout<<"enter new name:";
            cin>>s.name;

            cout<<"enter new address:";
            cin>>s.address;


            file.seekp(-int(sizeof(s)),ios::cur);
            file.write((char*)&s,sizeof(s));
            cout<<"Data is updated!"<<endl;
            return;
        }
    }
    if(!found) cout<<"Data not found!"<<endl;
    file.close();
}

void display(){
    fstream file(filename,ios::binary|ios::in);
    student s;
    bool found=false;
    if(!file.is_open()){
        cerr<<"Error opening file!"<<endl;
        return;
    }

    while(file.read((char*)&s,sizeof(s))){
        if(!s.isDeleted){
            cout<<s.name<<" "<<s.rollno<<" "<<s.address<<endl;
            
        }
        
    }
    file.close();

}





int main(){

    while(true){
        cout<<"1.Insert data\n2.Display data\n3.update data\n4.delete\n5.exit"<<endl;
        int x;
        cout<<"enter operation:";
        cin>>x;

        if(x==1){
            insertion();
        }else if(x==2){
            display();
        }else if(x==3){
            update();
        }else if(x==4){
            deletion();
        }
        
        else{
            break;
        }

    }
    
}