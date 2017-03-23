#ifndef ITERATION_H
#define ITERATION_H


class CIterator
{
 public:
     // 构造函数
     CIterator ();
     // 析构函数
    ~CIterator ();
    // 设置计算环境 (如系数矩阵等)
    bool SetEnvironment ();
     // 雅克比迭代法计算方程解
     bool JacobianCalculate ();
     // 高斯迭代法计算方程解
     bool GaussCalculate ();
     // 超松弛迭代法计算方程解
     bool RelaxationCalculate (double omiga);
     //Sample iteration
     bool SampleIteration();
     // 获取系数矩阵
     double ** GetMatrixA ();
     // 获取系数矩阵的阶
     int GetOrder ();
     // 获取方程组右值向量
     double * GetVectorB ();
     // 获取方程解向量
     double * GetSolution ();

 private:
     double **matrixA;    // 系数矩阵
     int order;            // 系数矩阵的阶
     double *vectorB;    // 方程组右值向量
     double *solution;    // 解向量
 };

 #endif
