//此文件为计算表达式所需函数的接口文件
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

bool errorCheck(QString&);
//输入为以字符串表示的某个表达式
//该函数会判断表达式是否合法，给出不合法类型
//该函数会修改原字符串，使其更规范
//如表达式合法返回true，不合法返回false

QString infixToSuffix(const QString &);
//前条件：输入为正确的中缀表达式
//返回后缀表达式

double calSuffix(const QString &);
//前条件：输入为正确的后缀表达式
//返回表达式的值

double cal_E(QString);
//string为一般（中缀）表达式
//该函数会调用errorCheck，infixToSuffix，calSuffix函数
//返回表达式的值

double cal_E(char* );
//该函数为cal_E的重载函数

double cal_E_Formal(const QString &);
//输入规范的中缀表达式，计算值
//与cal_E函数相比省去了检错与规范化的步骤
#endif // EXPRESSION_H
