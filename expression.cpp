#include "expression.h"
#include <stack>
#include <cstdlib>
#include <cmath>

using namespace std;

const QString expression::s_operator = "+-*/\^sincoslogtan. ()（）[]{}dot%";
const QString expression::bySymbol = "×";
const QString expression::divideSymbol = "÷";

bool expression::errorCheck(QString& s)
{
    int i = 0;
    int bracketMatch = 0;
    if (s[s.size() - 1] == '=')
        s.remove(s.size() - 1, 1);         //因为习惯可能在表达式最后面家里个等号
    for (i = 0; i < s.size(); i++)
    {
        s[i]=formatOperator(s[i]);

        if (s[i] == ' ')
        {
            s.remove(i, 1);
            i--;
            continue;
        }                           //去掉空格
        if (s[i] == 'l'&&i<s.size() - 1 && s[i + 1] == 'n')
        {
            s.remove(i, 2);
            s.insert(i, "log");
        }                            //将ln换成log
        if (s[i] == '-' || s[i] == '+')
        {
            if (i == 0 || i == s.size() - 1 || !(s[i - 1].isDigit()) && s[i - 1] != ')' && (s[i + 1].isDigit()))
            {
                s.insert(i, "(0");
                int j = i + 3;
                while (j<s.size() && (s[j].isDigit() || s[j] == '.'))
                    j++;
                s.insert(j, ")");
            }
        }                           //处理正负号的情况，如-8变为(0-8)，方便处理
        if (s[i] == '.')
        {
            if (i == 0 || i == s.size() || !s[i - 1].isDigit() || !s[i + 1].isDigit())
            {
                qDebug() << "1小数点使用错误.";
                return false;
            }
        }                           //判断小数点
        if (s_operator.indexOf(s[i]) >= s_operator.length() && !s[i].isDigit())
        {
            qDebug() << "2表达式中含有非法字符.";
            return false;
        }            //检验表达式中是否有非法字符
        if (s_operator.indexOf(s[i]) == 22 || s_operator.indexOf(s[i]) == 24)
        {
            qDebug() << "3请不要输入中文括号.";
            return false;
        }                           //中文括号处理起来太麻烦了
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            if (i == 0 || i == s.size() || (!(s[i + 1] == 's') && !(s[i + 1] == 'c') && !(s[i + 1] == 't') && !(s[i + 1] == 'l') && !(s[i + 1] == 'd') && !(s[i + 1] == '(')))
                if (i == 0 || i == s.size() || !s[i - 1].isDigit() || !s[i + 1].isDigit())
                {
                    qDebug() << "4运算符使用错误.";
                    return false;
                }
        }                           //双目运算两边必须为数字或左括号或其他函数
        if (s[i] == 's' || s[i] == 'c' || s[i] == 't' || s[i] == 'd' || s[i] == 'l' || s[i] == '(')
        {
            if (i>0 && (s[i - 1].isDigit() || s[i - 1] == 'x' || s[i - 1] == ')'))
                s.insert(i, "*");
        }                          //将类似3sin5化成3*sin5的形式，方便处理
        if (s[i] == ')'&&i<s.size() - 1 && (s[i + 1].isDigit()))
        {
            s.insert(i + 1, "*");
        }
        if (s[i] == '(')
            bracketMatch++;
        if (s[i] == ')')
            bracketMatch--;
        if (bracketMatch<0)
        {
            qDebug() << "5括号不匹配.";
            return false;
        }                           //括号匹配
        if (s[i] == 'c'&&s[i + 1] == 'o')
            s[i] = 'd';               //将cot变为dot方便处理
    }
    if (bracketMatch)
    {
        qDebug() << "6括号不匹配.";
        return false;
    }                           //括号匹配
    if (!s[s.size() - 1].isDigit() && (s[s.size() - 1]) != ')')
    {
        qDebug() << "7表达式尾部格式错误.";
        return false;
    }
    return true;
}

QChar expression::formatOperator(QChar c) {
    if (c == '\\' || c == '%' || c == divideSymbol[0])    //暂不支持取余操作，%算为除
        c = '/';
    if (c == bySymbol[0])
        c = '*';
    if (c == '[' || c == '[')
        c = '(';
    if (c == ']' || c == '}')
        c = ')';               //统一符号
    return c;
}

QString expression::infixToSuffix(const QString &s) {
    stack<QChar> stackForOp;
    QString suf;            //存放后缀表达式
    QString one = "+-";
    QString two = "*/";
    QString three = "sincostanlogdot";
    QString four = "^";          //四种运算优先级

    for (int i = 0; i<s.size(); i++)
    {
        if (s[i].isDigit() || s[i] == '.')
        {
            while (i<s.size() && (s[i].isDigit() || s[i] == '.'))
            {
                suf += s[i];
                i++;
            }
            i--;
            suf += ' ';
        }
        else if (one.indexOf(s[i]) != -1)
        {
            while (stackForOp.size() && (one.indexOf(stackForOp.top()) != -1 || two.indexOf(stackForOp.top()) != -1
                || three.indexOf(stackForOp.top()) != -1 || four.indexOf(stackForOp.top()) != -1))
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            stackForOp.push(s[i]);
        }
        else if (two.indexOf(s[i]) != -1)
        {
            while (stackForOp.size() && (two.indexOf(stackForOp.top()) != -1 || three.indexOf(stackForOp.top()) != -1
                || four.indexOf(stackForOp.top()) != -1))
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            stackForOp.push(s[i]);
        }
        else if (three.indexOf(s[i]) != -1)
        {
            int flag = 0;
            if (i>0 || s[i - 1] == '^')
                flag = 1;
            while (stackForOp.size() && (four.indexOf(stackForOp.top()) != -1) && flag == 0)
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            switch (s[i].unicode())
            {
            case 's':
                stackForOp.push('s');
                break;
            case 'c':
                stackForOp.push('c');
                break;
            case 't':
                stackForOp.push('t');
                break;
            case 'd':
                stackForOp.push('d');
                break;
            case 'l':
                stackForOp.push('l');
                break;
            default:
                //cout << "表达式有误.\n";
                return NULL;
                break;
            }
            while (stackForOp.size() && (four.indexOf(stackForOp.top()) != -1))
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            i += 2;
        }
        else if (four.indexOf(s[i]) != -1)
        {
            while (stackForOp.size() && four.indexOf(stackForOp.top()) != -1)
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            stackForOp.push(s[i]);
        }
        else if (s[i] == ')')
        {
            while (stackForOp.top() != '(')
            {
                suf += stackForOp.top();
                stackForOp.pop();
            }
            stackForOp.pop();
        }
        else stackForOp.push(s[i]);
    }
    while (stackForOp.size())
    {
        suf += stackForOp.top();
        stackForOp.pop();
    }
    return suf;
}

double expression::calSuffix(const QString &s)
{
    stack<double> result;
    double temp;
    QString num = "";
    int i = 0;
    double a1, a2;
    for (i = 0; i<s.size(); i++)
    {
        if (s[i].isDigit() || s[i] == '.')
        {
            num += s[i];
            continue;
        }
        if (s[i] == ' ')
        {
            temp = num.toDouble();
            result.push(temp);
            num = "";
            continue;
        }
        switch (s[i].unicode())
        {
        case '+':
            if (result.size()<2)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            a2 = result.top();
            result.pop();
            temp = a1 + a2;
            result.push(temp);
            break;
        case '-':
            if (result.size()<2)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            a2 = result.top();
            result.pop();
            temp = a2 - a1;
            result.push(temp);
            break;
        case '*':
            if (result.size()<2)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            a2 = result.top();
            result.pop();
            temp = a1*a2;
            result.push(temp);
            break;
        case '/':
            if (result.size()<2)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            a2 = result.top();
            result.pop();
            if (a1 == 0)
            {
                return INFINITY;
            }
            else
            {
                temp = a2 / a1;
                result.push(temp);
            }
            break;
        case '^':
            if (result.size()<2)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            a2 = result.top();
            result.pop();
            temp = pow(a2, a1);
            if (isnan(temp))
            {
                //cout << "表达式无意义.\n";        可以选择显示提示，但可能对解方程程序有影响
                return NAN;
            }
            result.push(temp);
            break;
        case 's':
            if (result.size()<1)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            temp = sin(a1);
            result.push(temp);
            break;
        case 'c':
            if (result.size()<1)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            temp = cos(a1);
            result.push(temp);
            break;
        case 't':
            if (result.size()<1)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            temp = tan(a1);
            result.push(temp);
            break;
        case 'd':
            if (result.size()<1)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            temp = 1 / tan(a1);
            result.push(temp);
            break;
        case 'l':
            if (result.size()<1)
            {
                //cout << "表达式有误.\n";
                return NAN;
            }
            a1 = result.top();
            result.pop();
            temp = log(a1);
            result.push(temp);
            break;
        default:
            //cout << "表达式有误.\n";
            return NAN;
            break;
        }
    }
    if (result.size() != 1)
    {
        //cout << "表达式有误.\n";
        return NAN;
    }
    return result.top();
}

double expression::cal_E(QString s)
{
    if (!errorCheck(s))
        return NAN;
    qDebug() << s;
    s = infixToSuffix(s);
    qDebug() << s;
    return calSuffix(s);
}

double expression::cal_E(char* c)
{
    QString s = c;
    return cal_E(s);
}

double expression::cal_E_Formal(const QString &s)
{
    return calSuffix(infixToSuffix(s));
}
