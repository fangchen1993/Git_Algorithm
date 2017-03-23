
// 迭代计算类
#include "iteration.h"
#include <iostream>

using namespace std;

// 打印方程解
void printResults (CIterator iterator);

int main()
{
    char ch;
    // 定义迭代类对象
    CIterator iterator;
    cout<<"Choose method:\n";
    cout<<"a) Jacobi iteration\t"<<"b) Gaussian iteration\n";
    cout<<"c) Super-relaxation iteration\t"<<"d) Sample iteration\n";

    cin>>ch;
    //until enter the correct choice
    while(ch != 'a' && ch !='b' && ch !='c' && ch !='d')
    {
        cout<<"You enter the wrong choice,enter the choice(a,b,c,d) again:\n";
        cin>>ch;
    }

    // 设置计算环境 (如系数矩阵等)
    iterator.SetEnvironment();
  switch (ch){
    // 雅克比迭代法计算方程解
    case 'a':
  {
      if (!iterator.JacobianCalculate()) {
        cout << "规定次数内未完成迭代计算" << endl;
        return 0;
    }
      break;
}
    // 高斯迭代法计算方程解

    case 'b' :
  {
      if (!iterator.GaussCalculate()) {
        cout << "规定次数内未完成迭代计算" << endl;
        return 1;
    }

    break;
  }

    // 超松弛迭代法计算方程解
    case 'c' :
    {
      double omiga = 1.5;        // 松弛迭代系数
    if (!iterator.RelaxationCalculate(omiga)) {
        cout << "规定次数内未完成迭代计算" << endl;
        return 1;
    }
      break;
  }
  case 'd':
   {
      //Sample iteration
      if(!iterator.SampleIteration())
      {
          cout << "规定次数内未完成迭代计算" << endl;
          return 1;
      }
      break;
  }
  default:break;

}
    // 打印方程解
    printResults (iterator);

    return 0;
}

// 打印方程解
void printResults (CIterator iterator)
{
    cout << "计算成功，打印方程解:  " << endl;
    for (int i=0; i<iterator.GetOrder(); i++)
        cout << "x" << i << " = " << iterator.GetSolution()[i] << endl;

    cout << endl;
}
