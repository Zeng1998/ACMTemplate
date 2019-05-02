/*
遍历
    int a[]={2,1,3,4,5,6,8,7} ;
    set s(a,a+8) ;
    set::iterator it=s.begin() ;
    for(;it!=s.end();it++){
        printf("%d\n",*it);
    }
插入
    set s;
    int a[]={2,1,3,4,5,6,8,7} ;
    for(int i=0;i<8;i++){
        s.insert(a[i]);
    }
    set::iterator it=s.begin();
    for(;it!=s.end();it++){
        printf("%d\n",*it);
    }
删除
    int a[]={2,1,3,4,5,6,8,7} ;
    set s(a,a+8);
    s.erase(s.begin()) ;
    set::iterator it=s.begin() ;
    for(;it!=s.end();it++){
        printf("%d\n",*it);
    }
    s.erase(s.find(8)) ;
    set::iterator it1=s.begin() ;
    for(;it1!=s.end();it1++){
        printf("%d\n",*it1);
    }
    s.erase(s.begin(),s.end()) ;
    set::iterator it2=s.begin() ;
    for(;it2!=s.end();it2++){
        printf("%d\n",*it2);
    }
计数
    int a[]={2,1,3,4,5,6,8,7,8,8};
    multiset s(a,a+10);
    printf("%d\n",s.count(8));
*/