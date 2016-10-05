#include "expression.h"
#include <stack>
#include <cstdlib>
#include <cmath>

using namespace std;

const QString expression::ALL_OPERATOR = "+-*/\^sincoslogtan. ()[]{}dot%";
const QString expression::BINARY_OPERATOR = "+-*/\%^";
const QString expression::UNARY_OPERATOR = "scltd"; //sin, cos, ln, tan, dot(cot)的第一个字母
const QString expression::BRACKET = "()[]{}";
const QString expression::MITIPLE_SIGN = "×";
const QString expression::DIVISION_SIGN = "÷";

expression::expression() {
    rawExpression = "";
    formatedExpression = "";
    suffixExpression = "";
}

expression::expression(QString rawExpression) {
    this->rawExpression = rawExpression;
    formatExpression();
}

void expression::formatExpression() {
    formatedExpression = rawExpression;
    formatOperator();
    removeBlank();
    removeEqualsSign();
    //turnLnToLog();
    //turncotToDot();
    processSignedNumber();
    insertMultipleSign();
    qDebug() << "formatedExpression:" << formatedExpression;
}

void expression::formatOperator() {
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (formatedExpression[i] == '\\' || formatedExpression[i] == '%' || formatedExpression[i] == DIVISION_SIGN[0])
            //暂不支持取余操作，%算为除
            formatedExpression[i] = '/';
        if (formatedExpression[i] == MITIPLE_SIGN[0])
            formatedExpression[i] = '*';
        if (formatedExpression[i] == '[' || formatedExpression[i] == '[')
            formatedExpression[i] = '(';
        if (formatedExpression[i] == ']' || formatedExpression[i] == '}')
            formatedExpression[i] = ')';
    }
}

void expression::removeBlank() {
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (formatedExpression[i].isSpace()) {
            formatedExpression.remove(i, 1);
            i--;
        }
    }
}

void expression::removeEqualsSign() {
    if (formatedExpression.isEmpty())
        return;
    if (formatedExpression[formatedExpression.size() - 1] == '=')
        formatedExpression.remove(formatedExpression.size() - 1, 1);
}

//void expression::turnLnToLog(){
//    if (s[i] == 'l'&&i<s.size() - 1 && s[i + 1] == 'n')
//    {
//        s.remove(i, 2);
//        s.insert(i, "log");
//    }
//}
//void expression::turnCotToDot(){
//    if (s[i] == 'l'&&i<s.size() - 1 && s[i + 1] == 'n')
//    {
//        if (s[i] == 'c'&&s[i + 1] == 'o')
//            s[i] = 'd';               //将cot变为dot方便处理
//    }
//}

void expression::processSignedNumber() {
    int j;
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (isSignedNumber(formatedExpression, i)) {
            formatedExpression.insert(i, "(0");
            j = i + 3;
            while (isPartOfANumber(formatedExpression, j))
                j++;
            formatedExpression.insert(j, ")");
        }
    }

}

bool expression::isSignedNumber(const QString& s, int i) const {
    if ((s[i] == '-' || s[i] == '+') && i < s.size() - 1) {
        return ((i == 0 || (i > 0) && (!s[i - 1].isDigit() || s[i - 1] == ')')) && (s[i + 1].isDigit() || isSubExpressionBeginPosition(s[i + 1])));
    }
        return false;
}

bool expression::isPartOfANumber(const QString& s, int i) const {
    return (i < s.size() && i >= 0 && (s[i].isDigit() || s[i] == '.'));
}

void expression::insertMultipleSign() {
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (isMultipleSignOmitedPosition(formatedExpression, i)) {
                formatedExpression.insert(i, "*");
        }
    }
}

bool expression::isMultipleSignOmitedPosition(const QString& s, int i) const {
    return (isSubExpressionBeginPosition(s[i]) && (i > 0 && (s[i - 1].isDigit() || s[i - 1] == ')')) ||
            (i > 0 && s[i-1] == ')' && s[i].isDigit()));   //形如3sin2或(3+2)5
}

bool expression::isSubExpressionBeginPosition(const QChar c) const {
    return (c == 's' || c == 'c' || c == 't' || c == 'd' || c == 'l' || c == '(');
}

bool expression::errorCheck() const{

    return checkAllCharLegal() && checkDecimalPoint() && checkOperator() && checkBracketMatch() && checkExpresionEnding();
}

bool expression::checkAllCharLegal() const{
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (ALL_OPERATOR.indexOf(formatedExpression[i]) == -1 && !formatedExpression[i].isDigit()) {
            qDebug() << "2表达式中含有非法字符.";
            return false;
        }
    }
    return true;
}

bool expression::checkDecimalPoint() const{
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (formatedExpression[i] == '.') {
            if (i == 0 || i == formatedExpression.size() - 1 || !formatedExpression[i - 1].isDigit() || !formatedExpression[i + 1].isDigit()) {
                qDebug() << "1小数点使用错误.";
                return false;
            }
            i++;
            while (i < formatedExpression.size() && formatedExpression[i].isDigit()) i++;
            if (i < formatedExpression.size() && formatedExpression[i] == '.') {
                qDebug() << "1小数点使用错误.";
                return false;
            }
        }
    }
    return true;
}

bool expression::checkOperator() const{
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (BINARY_OPERATOR.indexOf(formatedExpression[i]) != -1 && !isBinaryOperatorPositionRight(formatedExpression, i)) {
            qDebug() << "4运算符使用错误.";
            return false;
        }
        //检查单目运算符...
    }
    return true;
}

bool expression::isBinaryOperatorPositionRight(const QString& s, int i) const {
    if (i == 0 || i == s.size() - 1) {
        return false;
    }
    return (UNARY_OPERATOR.indexOf(s[i+1]) != -1 || s[i + 1] == '(' || s[i + 1].isDigit()) &&
            (s[i - 1].isDigit() || s[i - 1] == ')');
}            //双目运算右边必须为数字或左括号或其他函数，左边必须为数字或左括号

bool expression::checkBracketMatch() const{
    int leftBracketNum = 0;
    for (int i = 0; i < formatedExpression.size(); i++) {
        if (formatedExpression[i] == '(')
            leftBracketNum++;
        if (formatedExpression[i] == ')')
            leftBracketNum--;
        if (leftBracketNum < 0) {
            qDebug() << "5括号不匹配.";
            return false;
        }
    }
    if (leftBracketNum != 0) {
        qDebug() << "6括号不匹配.";
        return false;
    }
    return true;
}

bool expression::checkExpresionEnding() const{
    if (formatedExpression.isEmpty())
        return true;
    if (!formatedExpression[formatedExpression.size() - 1].isDigit() && (formatedExpression[formatedExpression.size() - 1]) != ')') {
        qDebug() << "7表达式尾部格式错误.";
        return false;
    }
    return true;
}

QString expression::infixToSuffix() {
    QString s = formatedExpression;
    stack<QChar> stackForOp;
    QString suf;            //存放后缀表达式
    QString one = "+-";
    QString two = "*/";
    QString three = "sincostanlndot";
    QString four = "^";          //四种运算优先级

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i].isDigit() || s[i] == '.')
        {
            while (i < s.size() && (s[i].isDigit() || s[i] == '.'))
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
            if (i > 0 && s[i - 1] == '^')
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
                i--;
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

double expression::calExpression()
{
    if (!errorCheck())
        return NAN;
    qDebug() << "No error";
    suffixExpression = infixToSuffix();
    return calSuffix(suffixExpression);
}

