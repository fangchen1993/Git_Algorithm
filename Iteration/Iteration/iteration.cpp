#include "iteration.h"
#include <iostream>
#include <math.h>

using namespace std;

// 构造函数
CIterator :: CIterator ()
{
    matrixA = NULL;
    order = 0;
    vectorB = NULL;
    solution = NULL;
}

// 析构函数
CIterator :: ~CIterator ()
{
    // 释放内存空间
    if (!vectorB) {
        delete [] vectorB;
        vectorB = NULL;
    }
    if (!solution) {
        delete [] solution;
        solution = NULL;
    }
    if (matrixA!=NULL) {
        for (int i=0; i<order; i++) {
            delete [] matrixA[i];
            matrixA[i] = NULL;
        }
        //delete [] matrixA;
        matrixA = NULL;
    }
}

// 设置计算环境 (如系数矩阵等)
bool CIterator :: SetEnvironment ()
{
    cout << "系数矩阵阶数: ";
    cin >> order;
    cout << endl;

    matrixA =  (double **)new double [order];
    for (int i=0; i<order; i++)
        matrixA[i] = new double [order];

    for (int i=0; i<order; i++) {
        cout << "第 " << i << " 行系数: ";
        for (int j=0; j<order; j++)
            cin >> matrixA[i][j];
    }
    cout << endl;

    vectorB = new double [order];
    cout << "b 向量: ";
    for (int i=0; i<order; i++)
            cin >> vectorB[i];
    cout << endl;

    solution = new double [order];

    cout << "运算环境搭建完毕" << endl << endl;

    return true;
}

// 雅克比迭代法计算方程解

bool CIterator :: JacobianCalculate ()
{
    cout << "下面使用雅克比迭代法计算该线性方程组" << endl << endl;

    // 设置迭代精度控制值
    cout << "迭代精度控制值: ";
    double bias;
    cin >> bias;
    cout << endl;

    // 设置迭代次数控制值
    cout << "迭代次数控制值: ";
    int itMax;
    cin >> itMax;
    cout << endl;

    // 当前满足迭代精度控制的解分量数
    int meetPrecisionCount = 0;

    // 辅助向量，存放上一次迭代的解向量。
    double * auxiliary = new double [order];

    // 初始化解向量
    for (int i=0; i<order; i++) {
        auxiliary[i] = 0;
        solution[i] = 1;
    }

    // 当前迭代次数
    int itCur = 0;

    // 若当前满足迭代精度控制的解分量数等于解向量维数或者迭代次数达到最大次数则跳出循环
    while (meetPrecisionCount<order && itCur<itMax) {

        // 当前满足迭代精度控制的解分量数清零
        meetPrecisionCount = 0;

        // 将当前解向量存入辅助向量
        for (int i=0; i<order; i++)
            auxiliary[i] = solution[i];

        // 计算新的解向量
        for (int i=0; i<order; i++) {

            // 暂存当前解分量
            double temp = solution[i];

            // 清零当前解分量
            solution[i] = 0;

            // 雅克比迭代计算
            for (int j=0; j<i; j++) {
                solution[i] += matrixA[i][j]*auxiliary[j];
            }
            for (int j=i+1; j<order; j++) {
                solution[i] += matrixA[i][j]*auxiliary[j];
            }
            solution[i] = (vectorB[i]-solution[i])/matrixA[i][i];

            // 更新当前满足迭代精度控制的解分量数
            if (fabs(temp-solution[i])<bias)
                meetPrecisionCount++;
        }

        // 当前迭代次数递增
        itCur++;
    }

    // 若在规定的迭代次数内未完成计算任务，则返回错误。
    if (itCur == itMax) return false;

    return true;
}

// 高斯迭代法计算方程解
bool CIterator :: GaussCalculate ()
{
    cout << "下面使用高斯迭代法计算该线性方程组" << endl << endl;

    // 设置迭代精度控制值
    cout << "迭代精度控制值: ";
    double bias;
    cin >> bias;
    cout << endl;

    // 设置迭代次数控制值
    cout << "迭代次数控制值: ";
    int itMax;
    cin >> itMax;
    cout << endl;

    // 当前满足迭代精度控制的解分量数
    int meetPrecisionCount = 0;

    // 初始化解向量
    for (int i=0; i<order; i++) {
        solution[i] = 0;
    }

    // 当前迭代次数
    int itCur = 0;

    // 若当前满足迭代精度控制的解分量数等于解向量维数或者迭代次数达到最大次数则跳出循环
    while (meetPrecisionCount<order && itCur<itMax) {

        // 当前满足迭代精度控制的解分量数清零
        meetPrecisionCount = 0;

        // 计算新的解向量
        for (int i=0; i<order; i++) {

            // 暂存当前解分量
            double temp = solution[i];

            // 清零当前解分量
            solution[i] = 0;

            // 高斯迭代计算
            for (int j=0; j<i; j++) {
                solution[i] += matrixA[i][j]*solution[j];
            }
            for (int j=i+1; j<order; j++) {
                solution[i] += matrixA[i][j]*solution[j];
            }
            solution[i] = (vectorB[i]-solution[i])/matrixA[i][i];

            // 更新当前满足迭代精度控制的解分量数
            if (fabs(temp-solution[i])<bias)
                meetPrecisionCount++;
        }

        // 当前迭代次数递增
        itCur++;
    }

    // 若在规定的迭代次数内未完成计算任务，则返回错误。
    if (itCur == itMax) return false;

    return true;
}

// 超松弛迭代法计算方程解
bool CIterator :: RelaxationCalculate (double omiga)
{
    cout << "下面使用超松弛迭代法计算该线性方程组" << endl << endl;

    // 设置迭代精度控制值
    cout << "迭代精度控制值: ";
    double bias;
    cin >> bias;
    cout << endl;

    // 设置迭代次数控制值
    cout << "迭代次数控制值: ";
    int itMax;
    cin >> itMax;
    cout << endl;

    // 当前满足迭代精度控制的解分量数
    int meetPrecisionCount = 0;

    // 当前满足迭代精度控制的解分量数
    for (int i=0; i<order; i++) {
        solution[i] = 0;
    }

    // 当前迭代次数
    int itCur = 0;

    // 若当前满足迭代精度控制的解分量数等于解向量维数或者迭代次数达到最大次数则跳出循环
    while (meetPrecisionCount<order && itCur<itMax) {

        // 当前满足迭代精度控制的解分量数清零
        meetPrecisionCount = 0;

        // 计算新的解向量
        for (int i=0; i<order; i++) {

            // 暂存当前解分量
            double temp = solution[i];

            // 清零当前解分量
            solution[i] = 0;

            // 超松弛迭代计算
            for (int j=0; j<i; j++) {
                solution[i] += matrixA[i][j]*solution[j];
            }
            for (int j=i+1; j<order; j++) {
                solution[i] += matrixA[i][j]*solution[j];
            }
            solution[i] = omiga*(vectorB[i]-solution[i])/matrixA[i][i] + (1-omiga)*temp;

            // 更新当前满足迭代精度控制的解分量数
            if (fabs(temp-solution[i])<bias)
                meetPrecisionCount++;
        }

        // 当前迭代次数递增
        itCur++;
    }

    // 若在规定的迭代次数内未完成计算任务，则返回错误。
    if (itCur == itMax) return false;

    return true;
}


//Sample iteration

bool CIterator::SampleIteration()
{
    cout << "下面使用简单迭代法计算该线性方程组" << endl << endl;

    // 设置迭代精度控制值
    cout << "迭代精度控制值: ";
    double bias;
    cin >> bias;
    cout << endl;

    // 设置迭代次数控制值
    cout << "迭代次数控制值: ";
    int itMax;
    cin >> itMax;
    cout << endl;

    // 当前满足迭代精度控制的解分量数
    int meetPrecisionCount = 0;

    // 初始化解向量
    for (int i=0; i<order; i++) {
        solution[i] = 0;
    }

    // 当前迭代次数
    int itCur = 0;

    //calculate the iteration matrix;
    double x[order][order];
    double b[order];
    for(int i=0;i<order;i++)
    {
        for(int j=0;j<order;j++)
           {
            if(i==j)
                x[i][i] = 0;
            else
                x[i][j] = -matrixA[i][j]/matrixA[i][i];
        }
    }

    //the vector of plus
    for(int i=0;i<order;i++)
        b[i] = vectorB[i]/matrixA[i][i];

    // 若当前满足迭代精度控制的解分量数等于解向量维数或者迭代次数达到最大次数则跳出循环
    while (meetPrecisionCount<order && itCur<itMax) {

        // 当前满足迭代精度控制的解分量数清零
        meetPrecisionCount = 0;

        // 计算新的解向量
        for (int i=0; i<order; i++) {

            // 暂存当前解分量
            double temp = solution[i];

            // 清零当前解分量
            solution[i] = 0;

            // 高斯迭代计算
            for (int j=0; j<order; j++) {
                solution[i] += x[i][j]*solution[j];

            }
            solution[i] +=b[i];


            // 更新当前满足迭代精度控制的解分量数
            if (fabs(temp-solution[i])<bias)
                meetPrecisionCount++;
        }

        // 当前迭代次数递增
        itCur++;
    }

    // 若在规定的迭代次数内未完成计算任务，则返回错误。
    if (itCur == itMax) return false;

    return true;
}


// 获取系数矩阵
double ** CIterator :: GetMatrixA ()
{
    return this->matrixA;
}

// 获取系数矩阵的阶
int CIterator :: GetOrder ()
{
    return this->order;
}

// 获取方程组右值向量
double * CIterator :: GetVectorB ()
{
    return this->vectorB;
}

// 获取方程解向量
double * CIterator :: GetSolution ()
{
    return this->solution;
}

