#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef unsigned long int uli;
typedef vector<uli> MATROW;
typedef vector<MATROW> MAT;
typedef map<int,vector<int>> MP;
vector<int> findNonOverlapping(MAT &mat,int maxid,MP &mp){
  vector<int> ans;
  for(int col=1;col<=maxid;++col){
    if(mp.find(col) != mp.end()){
      vector<int> &pr = mp[col];
      bool valid=true;
      int x1=pr[0];int y1=pr[1];int x2=pr[2];int y2=pr[3];
        for(int r=x1;r<=x2;++r){
          for(int c=y1;c<=y2;++c){
            uli val = mat[r][c];
            if(val != col){
              valid=false;
              break;
            }
          }
          if(!valid) break;
        }
      if(valid) ans.push_back(col);
    }
  }
  return ans;
}
void removeCols(MAT &mat,int maxid,MP &mp){
  for(int col=0;col<=maxid;++col){
    if(mp.find(col) != mp.end()){
      vector<int> &pr = mp[col];
      int x1=pr[0];int y1=pr[1];int x2=pr[2];int y2=pr[3];
        for(int r=x1;r<=x2;++r){
          for(int c=y1;c<=y2;++c){
            mat[r][c] -= col;
          }
        }
    }
  }
}
void printMat(MAT &mat){
    for(int r=0;r<mat[0].size();++r){
      cout<<endl;
      for(int c=0;c<mat[0].size();++c){
        cout<<mat[r][c]<<' ';
      }
    }
}
int main()
{
  int T;
  cin>>T;
  for(int i=0;i<T;++i){
    int N;cin>>N;
    int k;cin>>k;
    int maxid=0;
    MP mp;
    for(int r=0;r<N;++r){
      for(int c=0;c<N;++c){
        int col; cin>>col;
        maxid = std::max(maxid,col);
        if(!col) continue;
        if(mp.find(col) == mp.end()){
          vector<int> &pr = mp[col];
          pr.push_back(r);
          pr.push_back(c);
          pr.push_back(r);
          pr.push_back(c);
        } else {
          vector<int> &pr = mp[col];
          pr[0] = std::min(pr[0],r);
          pr[1] = std::min(pr[1],c);
          pr[2] = std::max(pr[2],r);
          pr[3] = std::max(pr[3],c);
        }
      }
    }
    
    //iterate over colors and mark the bits
    MAT mat(N,MATROW(N,0));
    for(int col=0;col<=maxid;++col){
      if(mp.find(col) != mp.end()){
        vector<int> &pr = mp[col];
        int x1=pr[0];int y1=pr[1];int x2=pr[2];int y2=pr[3];
        for(int r=x1;r<=x2;++r){
          for(int c=y1;c<=y2;++c){
            mat[r][c] += col;
          }
        }
      }
    }
    
   // printMat(mat);
    //find nonOverlapping ones
    vector<int> ans;
    vector<int> cols = findNonOverlapping(mat,maxid,mp);
    while(!cols.empty()){
      std::sort(cols.begin(),cols.end(),greater<int>());
      for(auto i:cols)ans.push_back(i);
      removeCols(mat,maxid,mp);
      cols = findNonOverlapping(mat,maxid,mp);
    }
    std::reverse(ans.begin(),ans.end());
    cout<<"\n#"<<(i+1);
    if(ans.size() && k<=(ans.size()-1)){
      cout<<ans[k];
    } else cout<<(int)(-1);
    for(auto a:ans){
        cout<<' '<<a;
    }
  }
    return 0;
}
