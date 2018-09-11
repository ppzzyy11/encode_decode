#include<iostream>
#include<climits>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

ostream& operator<<(ostream& os,const vector<vector<char>>& mat)
{
    for(int i=0;i<mat.size();i++)
    {
        for(int j=0;j<mat[i].size();j++)
        {
            cout<<mat[i][j]<<' ';
        }
        cout<<endl;
    }
    return os;
}

void Read(ifstream& coded,int &n)
{
    for(int i=sizeof(int)-1;i>=0;i--)
    {
        coded.read((char*)(&n)+i,sizeof(char));
    }
}

int main(int argc,char** argv)
{
    if(argc!=4)
    {
        cerr<<"****************************\nnumber of arguments is wrong\n****************************"<<endl;
        return 1;
    }

    ifstream book(argv[1],ios::in);//open file
    if(!book.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[1]<<"\n****************************"<<endl;
        return 1;
    }
    ifstream coded(argv[2],ios::in|ios::binary);
    if(!coded.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[2]<<"\n****************************"<<endl;
        return 1;
    }
    ofstream decoded(argv[3],ios::out);
    if(!decoded.is_open())
    {
        cerr<<"****************************\ncan't open"<<argv[3]<<"\n****************************"<<endl;
        return 1;
    }

    vector<queue<pair<int,int>>> rec;//record , access using char
    queue<pair<int,int>> tmp;
    for(int i=0;i<256;i++)
    {
        rec.push_back(tmp);
    }
    int i=0,j=0;

    char ch;
    while(book.get(ch))
    {
        if(ch=='\n')
        {
            //map.push_back(vector<char>(0,0));//new line , new vector
            i++;
            j=0;
            rec[ch].push(make_pair(i,j));
        }else
        {
            rec[ch].push(make_pair(i,j));
        }
        j++;
    }
    int x=INT_MIN;
    int y=INT_MIN;
    int px=INT_MIN;
    int py=INT_MIN;
    //alwys output the last character twice
    while(coded)
    {
        Read(coded,x);
        Read(coded,y);
        //coded.read((char*)&x,sizeof(int));
        //coded.read((char*)&y,sizeof(int));
        if(py==INT_MIN&&px==INT_MIN)//try to not output the last character twice
        {
        }else
        {
            auto pxy=make_pair(px,py);
            for(int i=0;i<256;i++)
            {
                if(rec[i].size()!=0)
                {
                    pair<int,int>& fnt=rec[i].front();//once used.pop
                    if(fnt.first==pxy.first&&fnt.second==pxy.second)
                    {
                        decoded<<(char)i;
                        rec[i].pop();
                        break;
                    }
                }
            }
        }
        py=y;
        px=x;
    }

    book.close();//close files
    coded.close();
    decoded.close();


    return 0;
}
