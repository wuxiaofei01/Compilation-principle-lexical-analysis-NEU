#include <bits/stdc++.h>

using namespace std;

struct Token1
{
    string s[100] = {"0", "int", "void", "break", "float", "while", "do", "struct",
                     "const", "case", "for", "return", "if", "default", "else"};
    int cnt       = 14;
};

struct Token2
{
    string s[100] = {"0", "-", "/", "(", ")", "==", "<=", "<", "+",
                     "*", ">", "=", ",", ";", "++","{","}"};
    int cnt       = 16;
};

struct Token3
{
    string s[10000];
    int cnt = 1;
};
struct Token4
{
    string s[10000];
    int cnt = 1;
};

struct Node
{
    Token1 K; //关键字
    Token2 P; //界符
    Token3 I; //标识符
    Token4 C; //常数
};

Node token;
pair<char, int> ans;
bool check_k(string s, int& pos) //返回长度 也就是 判断 前几个字符 是否满足
{

    for (int i = 1; i <= token.K.cnt; i++)
    {
        string target = token.K.s[i];  //得到进行匹配的字符串
        int len       = target.size(); //得到长度

        string temp = s.substr(pos, len);
        if (temp == target && !isalnum(s[pos + len])) //匹配成功 下一个字符是数字和字符 那么肯定不是 标识符了
        {
            ans.first  = 'K';
            ans.second = i;
            pos += len;
            return true;
        }
    }
    return false;
}
bool check_p(string s, int& pos) //不考虑 非法输入
{
    for (int i = 1; i <= token.P.cnt; i++)
    {
        string target = token.P.s[i];  //得到进行匹配的字符串
        int len       = target.size(); //得到长度

        string temp = s.substr(pos, len);
        if (temp == target)
        {
            ans.first  = 'P';
            ans.second = i;
            pos += len;
            return true;
        }
    }
    return false;
}
bool check_c(string s, int& pos) //如果首字母是 数字 那么肯定是 常数了
{
    if (!isdigit(s[pos]))
        return false;

    //先找一遍
    for (int i = 1; i < token.C.cnt; i++)
    {
        string target = token.K.s[i];  //得到进行匹配的字符串
        int len       = target.size(); //得到长度

        string temp = s.substr(pos, len);
        if (temp == target && !isdigit(s[pos + len]))
        {
            pos += len;
            ans.first  = 'C';
            ans.second = 'i';
            return true;
        }
    }
    string res; //创建 常数表
    for (; pos < s.size(); pos++)
    {
        if (!isdigit(s[pos]))
            break;
        res += s[pos];
    }
    int& now = token.C.cnt;

    token.C.s[now] = res;
    now++;
    ans.first  = 'C';
    ans.second = now - 1;
    return true;
}
void check_i(string s, int& pos)
{
    for (int i = 1; i <= token.I.cnt; i++)
    {
        string target = token.I.s[i];  //得到进行匹配的字符串
        int len       = target.size(); //得到长度

        string temp = s.substr(pos, len);
        if (temp == target && !isalnum(s[pos + len])) //匹配成功 下一个字符不是数字和字符 那么肯定不是 标识符了
        {
            ans.first  = 'I';
            ans.second = i;
            pos += len;
            return;
        }
    }

    string res;
    if (s[pos] == '_')
        res += '_', pos++;
    for (; pos < s.size(); pos++)
    {
        if (!isalnum(s[pos]))
            break;
        res += s[pos];
    }

    int& now       = token.I.cnt;
    token.I.s[now] = res; //插入字符串
    now++;
    ans.first  = 'I';
    ans.second = now - 1;
}
int main()
{
    string s;
    while (getline(cin, s))
    {
        for (int i = 1; i <= token.C.cnt; i++)
            token.C.s[i].clear();
        token.C.cnt = 1;
        for (int i = 1; i <= token.I.cnt; i++)
            token.I.s[i].clear();
        token.I.cnt = 1;
        cout <<"Token序列：";
        for (int i = 0; i < s.size();)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            if (check_k(s, i))
            {
            }
            else if (check_p(s, i))
            {
            }
            else if (check_c(s, i))
            {
            }
            else
                check_i(s, i);

            cout << "(" << ans.first << " " << ans.second << ")";
        }
        cout << endl;
        cout <<"标识符表：";
        for(int i =1 ; i < token.I.cnt;i++)
        {
            cout << token.I.s[i];
            if(i!=token.I.cnt - 1) cout <<" ";
            else cout << endl;
        }


        cout <<"常数表：";
        for(int i =1 ; i < token.C.cnt;i++)
        {
            cout << token.C.s[i];
            if(i!=token.C.cnt - 1) cout <<" ";
        }
    }
}