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
    Token1 K; //�ؼ���
    Token2 P; //���
    Token3 I; //��ʶ��
    Token4 C; //����
};

Node token;
pair<char, int> ans;
bool check_k(string s, int& pos) //���س��� Ҳ���� �ж� ǰ�����ַ� �Ƿ�����
{

    for (int i = 1; i <= token.K.cnt; i++)
    {
        string target = token.K.s[i];  //�õ�����ƥ����ַ���
        int len       = target.size(); //�õ�����

        string temp = s.substr(pos, len);
        if (temp == target && !isalnum(s[pos + len])) //ƥ��ɹ� ��һ���ַ������ֺ��ַ� ��ô�϶����� ��ʶ����
        {
            ans.first  = 'K';
            ans.second = i;
            pos += len;
            return true;
        }
    }
    return false;
}
bool check_p(string s, int& pos) //������ �Ƿ�����
{
    for (int i = 1; i <= token.P.cnt; i++)
    {
        string target = token.P.s[i];  //�õ�����ƥ����ַ���
        int len       = target.size(); //�õ�����

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
bool check_c(string s, int& pos) //�������ĸ�� ���� ��ô�϶��� ������
{
    if (!isdigit(s[pos]))
        return false;

    //����һ��
    for (int i = 1; i < token.C.cnt; i++)
    {
        string target = token.K.s[i];  //�õ�����ƥ����ַ���
        int len       = target.size(); //�õ�����

        string temp = s.substr(pos, len);
        if (temp == target && !isdigit(s[pos + len]))
        {
            pos += len;
            ans.first  = 'C';
            ans.second = 'i';
            return true;
        }
    }
    string res; //���� ������
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
        string target = token.I.s[i];  //�õ�����ƥ����ַ���
        int len       = target.size(); //�õ�����

        string temp = s.substr(pos, len);
        if (temp == target && !isalnum(s[pos + len])) //ƥ��ɹ� ��һ���ַ��������ֺ��ַ� ��ô�϶����� ��ʶ����
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
    token.I.s[now] = res; //�����ַ���
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
        cout <<"Token���У�";
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
        cout <<"��ʶ����";
        for(int i =1 ; i < token.I.cnt;i++)
        {
            cout << token.I.s[i];
            if(i!=token.I.cnt - 1) cout <<" ";
            else cout << endl;
        }


        cout <<"������";
        for(int i =1 ; i < token.C.cnt;i++)
        {
            cout << token.C.s[i];
            if(i!=token.C.cnt - 1) cout <<" ";
        }
    }
}