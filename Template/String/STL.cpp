/**
reverse(s.begin(), s.end());
transform(s.begin(), s.end(), s.begin(), ::toupper);  (::tolower)
string->number:
    int a;
    stringstream(s) >> a;
number->char*
    char s[100];
    sprint(s,"%d",a);
//返回pos开始的长度为len的字符串
substr(pos,len);
//在pos位置插入字符串s
insert(int pos,string s)
//从索引pos开始往后全删除
erase(pos);
//从索引pos开始往后删num个
erase(pos,num);
//删除迭代器it指向的字符，返回删除后迭代器的位置
erase(it);
//删除迭代器[first，last)之间的所有字符，返回删除后迭代器的位置
erase(first,last);
//从pos开始查找字符c/字符串s在当前字符串的位置
int find(c/s,pos);
**/