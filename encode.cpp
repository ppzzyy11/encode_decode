#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>


using namespace std;

ostream& operator<<(ostream& os,const unordered_map<char,pair<int,int>> &hash)
{
    for(auto it=hash.begin();it!=hash.end();it++)
    {
        cout<<it->first<<'\t'<<'('<<it->second.first<<','<<it->second.second<<')'<<'\n';
    }
    return os;
}

void Write(ofstream& coded,int& n)
{
    for(int i=sizeof(int)-1;i>=0;i--)
    {
        coded.write((char*)(&n)+i,sizeof(char));
    }
}


int main(int argc,char** argv)//book file, messagefile, codefile
{
    if(argc!=4)
    {
        cerr<<"****************************\nnumber of arguments is wrong\n****************************"<<endl;
        return 1;
    }

    ifstream book(argv[1],ios::in);//build the encode table
    if(!book.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[1]<<"\n****************************"<<endl;
        return 1;
    }
    ifstream message(argv[2],ios::in);//message to encode
    if(!book.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[2]<<"\n****************************"<<endl;
        return 1;
    }
    ofstream coded(argv[3],ios::out|ios::binary);//coded file
    if(!coded.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[3]<<"\n****************************"<<endl;
        return 1;
    }

    unordered_map<char,queue<pair<int,int>>> hash;//hash recode the coordinates of characters
    int i=0,j=0;
    char ch;
    while(book.get(ch))//when there is input from book
    {
        if(ch=='\n')
        {
            j=0;
            i++;
        }
        hash[ch].push(make_pair(i,j));
        j++;
    }


    while(message.get(ch))
    {
        if(hash.count(ch)==0||hash[ch].size()==0)
        {
            cerr<<"****************************\nMeet a unknown character in "<<argv[2]<<"  "<<ch<<"\t,its ascii number is "<<(int)ch<<"\n****************************"<<endl;
            return 1;
        }
        pair<int,int> fnt=hash[ch].front();
        hash[ch].pop();//once used ,pop
        int x=fnt.first;
        int y=fnt.second;
        Write(coded,x);
        Write(coded,y);
        //coded.write((char*)&x,sizeof(int));//use write function to write in binary form
        //coded.write((char*)&y,sizeof(int));
    }
    book.close();//cole file
    message.close();
    coded.close();

    return 0;
}
