#include<bits/stdc++.h>

using namespace std;

map<string , string> Token_K;//关键字
map<string , string> Token_P;//界符
map<string , string> Token_I;//标识符
map<string , string> Token_C1;//常数
map<string , string> Token_CT;//字符常量
map<string , string> Token_ST;//字符串常量
string s;

void init_K()
{
	Token_K.insert(pair<string , string>{"const"  , "CONSTTK"});
	Token_K.insert(pair<string , string>{"int"    , "INTTK"});
	Token_K.insert(pair<string , string>{"char"   , "CHARTK"});
	Token_K.insert(pair<string , string>{"void"   , "VOIDTK"});
	Token_K.insert(pair<string , string>{"main"   , "MAINTK"});
	Token_K.insert(pair<string , string>{"if"     , "IFTK"});
	Token_K.insert(pair<string , string>{"else"   , "ELSETK"});
	Token_K.insert(pair<string , string>{"do"     , "DOTK"});
	Token_K.insert(pair<string , string>{"while"  , "WHILETK"});
	Token_K.insert(pair<string , string>{"for"    , "FORTK"});
	Token_K.insert(pair<string , string>{"scanf"  , "SCANFTK"});
	Token_K.insert(pair<string , string>{"printf" , "PRINTFTK"});
	Token_K.insert(pair<string , string>{"return" , "RETURNTK"});
}
void init_P()
{
	Token_P.insert(pair<string , string>{"+" , "PLUS"});
	Token_P.insert(pair<string , string>{"-" , "MINU"});
	Token_P.insert(pair<string , string>{"*" , "MULT"});
	Token_P.insert(pair<string , string>{"/" , "DIV"});
	Token_P.insert(pair<string , string>{"<" , "LSS"});
	Token_P.insert(pair<string , string>{"<=", "LEQ"});
	Token_P.insert(pair<string , string>{">" , "GRE"});
	Token_P.insert(pair<string , string>{">=", "GEQ"});
	Token_P.insert(pair<string , string>{"==", "EQL"});
	Token_P.insert(pair<string , string>{"!=", "NEQ"});
	Token_P.insert(pair<string , string>{"=" , "ASSIGN"});
	Token_P.insert(pair<string , string>{";" , "SEMICN"});
	Token_P.insert(pair<string , string>{"," , "COMMA"});
	Token_P.insert(pair<string , string>{"(" , "LPARENT"});
	Token_P.insert(pair<string , string>{")" , "RPARENT"});
	Token_P.insert(pair<string , string>{"[" , "LBRACK"});
	Token_P.insert(pair<string , string>{"]" , "RBRACK"});
	Token_P.insert(pair<string , string>{"{" , "LBRACE"});
	Token_P.insert(pair<string , string>{"}" , "RBRACE"});

}
void init()
{
	init_K();
	init_P();
}
void Token_out(string a , string b)
{
	cout << a << " "<< b << endl;
}
void Fun_K(int &pos)
{
    if(!isalpha(s[pos])) return ;
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isalnum(s[i]))//不是字母 那么 就是 分隔符
        {
            if(Token_K.count(temp))
            {
                pos = i ;
                Token_out(Token_K[temp] , temp);
            }
            return ;
        }
        temp += s[i];
    }
}

void Fun_I(int &pos)
{
    if(!isalpha(s[pos]) && s[pos] != '_' )return ;
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isalnum(s[i]) && s[i] != '_')//标识符 只能是 数字字母 下划线
        {
            if(!Token_I.count(temp))//不存在
            //Token_I.insert(pair<string , int >{temp , Token_I.size() + 1 });
            Token_I[temp] = Token_I.size() + 1;
            Token_out("IDENFR" , temp);
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}

void Fun_C1(int &pos)
{
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isdigit(s[i]))
        {
            if(s[i] == '.' || s[i] == 'e')return ;//应该是实数
            else if(isalpha(s[i]))//标识符输出错误
            {
                cout <<"词法错误";
                exit(0);
            }
            else 
            {
                if(!Token_C1.count(temp))
                //Token_C1.insert(pair<string,int>{temp , Token_C1.size() + 1});
                Token_C1[temp] = Token_C1.size() + 1;
                Token_out("INTCON",temp);
                pos = i ;
                return ;
            }
        }
        temp += s[i];
    }
}


void Fun_CT(int &pos)
{
    if(s[pos] !='\'')return;
    string temp;
    for(int i = pos + 1 ; i <= s.size() ; i ++)
    {
        if(s[i] == '\'')
        {
            if(Token_CT.count(temp))
            //Token_CT.insert(pair<string,int>{temp,Token_CT.size() + 1});
            Token_CT[temp] = Token_CT.size() + 1;
            Token_out("CHARCON",temp);
            i++;
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}
void Fun_ST(int &pos)
{
    if(s[pos] !='\"')return;
    string temp;
    for(int i = pos + 1; i <= s.size() ; i ++)
    {
        if(s[i] == '\"') 
        {
            if(!Token_ST.count(temp))
            //Token_ST.insert(pair<string,int>{temp,Token_ST.size() + 1});
            Token_ST[temp] = Token_ST.size() +  1;
            Token_out("STRCON",temp);
            i++;
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}
void Fun_P(int &pos)
{
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(Token_P.count(temp))//判断单个字符 还有两个字符的
        {
			string temp2 = temp+s[i];
			if(Token_P.count(temp2))
			{
				Token_out(Token_P[temp2] , temp2);
            	pos = i + 1;
            	return ;
			}
            Token_out(Token_P[temp] , temp);
            pos = i ;
            return ;
        }
        temp+=s[i];
    }
}
int main()
{
	init();
	freopen("testfile.txt","r+",stdin); //输入重定向，输入数据将从in.txt文件中读取 
	freopen("output.txt","w",stdout); //输出重定向，输出数据将保存out.txt文件中 
	while(getline(cin , s))
	{
		if(s=="")return 0;
		for(int i = 0 ; i < s.size() ; )
		{
			if(s[i] == ' ')
			{
				i++;
				continue;
			}
			if(isalpha(s[i]) || s[i] == '_')//如果第一个字符是 字母 那么 就只能是 关键字 或者 标识符
			{
				Fun_K(i);
				Fun_I(i);
			}
			else if(isdigit(s[i]))//如果是 数字 那么是 ， 常数，常实数
			{
				Fun_C1(i);
			}
			else if(s[i] =='\'')//字符常量
			{
				Fun_CT(i);
			}
			else if(s[i] == '\"')//字符串常量
			{
				Fun_ST(i);
			}
			else  
			{
				int p = i;
				Fun_P(i);
				if(i == p) i ++;
			}

		}
	}
	fclose(stdin);//关闭重定向输入
	fclose(stdout);//关闭重定向输出 
	return 0;
}