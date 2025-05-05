//DOP-7/02/2025
//Implement all the functions of a dictionary (ADT) using open
//hashing technique: separate chaining using linked list Data: Set of
//(key, value) pairs, Keys are mapped to values, Keys must be
//comparable, and Keys must be unique. Standard Operations: Insert
//(key, value), Find(key), Delete(key)

#include <iostream>
using namespace std;

class Node{
public:
	string keyword;
	string meaning;
	Node* next;

	Node(string k, string m){
		keyword = k;
		meaning = m;
		next = nullptr;
	}
};

void insert(string k, string m, int size, Node* arr[]) {
    int sum = 0;
    for(int i = 0; i < k.length(); i++) {
        sum = sum + int(k[i]);
    }

    int posi = sum % size;
    Node* newNode = new Node(k, m);
    if(arr[posi] == nullptr) {
        arr[posi] = newNode;
    } else {
        Node* temp = arr[posi];
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void print(int size, Node* arr[]) {
    cout << "Keyword" << "		" << "Meaning" << endl;
    for(int i = 0; i < size; i++) {
        Node* temp = arr[i];
        if(temp==nullptr){
        	cout<<"NULLPTR"<<endl;
        }
        else{
        	while(temp!=nullptr){
        		cout<<temp->keyword<<"		"<<temp->meaning<<endl;
        		temp = temp->next;
        	}
        }
    }
}

Node* find(string k, int size, Node* arr[]){
	int sum = 0;
	for(int i = 0;i<k.length();i++){
		sum = sum + int(k[i]);
	}
	int posi = sum%size;

	Node* temp = arr[posi];
	while(temp!=nullptr){
		if(temp->keyword == k){
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

void deleteKey(string k, int size, Node* arr[]) {
    int sum = 0;
    for (int i = 0; i < k.length(); i++) {
        sum += int(k[i]);
    }

    int posi = sum % size;
    Node* temp = arr[posi];
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->keyword == k) {
            if (prev == nullptr) {
                arr[posi] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Key not found!" << endl;
}


int main(){
	int size;
	cout<<"Enter the size of the hash table: ";
	cin>>size;

	Node* hash[size] = {nullptr};
	int choice;
	cout<<"MENU:"<<endl;
	do{
		string value,meaning,keyword,word,Keyword;
		Node* ans;
		cout<<"1.Insert Keyword \n2.Delete Key \n3.Find key \n4.Print \n5.Exit";
		cout<<"Enter your choice: ";
		cin>>choice;

		switch(choice){
			case 1:
				cout<<"Enter the keyword and its meaning to be inserted: ";
				cin>>value;
				cin.ignore();
				getline(cin,meaning);
				insert(value,meaning,size,hash);
				break;

			case 2:
				cout<<"Enter the key to be deleted: ";
				cin>>keyword;
				deleteKey(keyword,size,hash);
				break;

			case 3:
				cout<<"Enter the key to be found in the hash table: ";
				cin>>word;
				ans = find(word,size,hash);
				if(ans==nullptr){
					cout<<"The key is not found in the hash table"<<endl;
				}
				else{
					cout<<"Key is found in the hash table"<<endl;
					cout<<ans->keyword<<" "<<ans->meaning<<endl;
				}
				break;

			case 4:
				print(size,hash);
				break;

			case 5:
				cout<<"Exiting the program..."<<endl;
				break;
		}
	}while(choice!=5);
}
