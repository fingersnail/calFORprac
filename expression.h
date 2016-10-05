//此文件为计算表达式所需函数的接口文件
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

class expression {
public:
    expression();
    expression(QString);

    //检查表达式中的错误
    bool errorCheck() const;

    //将中缀表达式变换为后缀表达式
    QString infixToSuffix();

    //计算一般（中缀）表达式的值
    double calExpression();

private:
    QString rawExpression;
    QString formatedExpression;
    QString suffixExpression;

    const static QString ALL_OPERATOR;
    const static QString BINARY_OPERATOR;
    const static QString UNARY_OPERATOR;
    const static QString BRACKET;
    const static QString MITIPLE_SIGN;
    const static QString DIVISION_SIGN;

    void formatExpression();    //将表达式规范化

    void formatOperator();    //统一符号格式
    void removeBlank();       //去除空白字符
    void removeEqualsSign();  //去除尾部可能出现的等号
    void removeRedundentBracket();   //去除多余的括号
    //void turnLnToLog();
    void processSignedNumber();   //将带符号数处理成0减或加正数的形式
    bool isSignedNumber(const QString &, int) const; //判断字符串的第相应位位是不是带符号数的正负号
    bool isPartOfANumber(const QString &, int) const; //判断字符串的第相应位位是不是一个数字的一部分
    void insertMultipleSign();      //在必要位置插入乘号，比如3sin2变为3*sin2
    bool isMultipleSignOmitedPosition(const QString &, int) const;  //判断该处是不是省略了乘号
    bool isSubExpressionBeginPosition(const QChar) const;   //判断字符是不是子表达式开始的地方

    bool checkAllCharLegal() const;      //检查是否所有字符都合法
    bool checkDecimalPoint() const;      //检查小数点使用是否合法
    bool checkOperator() const;          //检查操作符使用是否合法
    bool isBinaryOperatorPositionRight(const QString &, int) const; //判断该处的双目运算符是否处在正确位置今年
    bool checkBracketMatch() const;      //检查括号是否匹配
    bool checkExpresionEnding() const;   //检查表达式结尾是否合法

    double calSuffix(const QString &);       //计算后缀表达式的值
};
#endif // EXPRESSION_H
