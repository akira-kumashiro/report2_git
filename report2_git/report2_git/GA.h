#pragma once

#include<vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

class GA
{
private:
	int max_genom_list;//個体数
	int var_num;//品物の個数
	//double crossoverRate = 0.8;//交叉率
	double individualMutationRate = 0.1;//個体突然変異率
	//double genomMutaionRate = 0.04;//遺伝子突然変異率
	int minNum = 0, maxNum = 0;
	double alpha = 0.5;
public:
	std::vector<double> varMax, varMin;
	double resultSumValue;//評価関数の合計

	class Data//データ格納用クラス
	{
	private:
		//double coefficient = 0.01;//評価関数用の定数
		int var_num;//変数の数
	public:
		std::vector<double> x;//品物を入れるかどうかの配列
		double functionValue;//評価関数の値
		double result;

		Data(int _var_num)//コンストラクタ
		{
			var_num = _var_num;

			x.resize(var_num);//isIncludedの配列の長さの設定
		}

		/*double calcResult(std::vector<double> _varMax, std::vector<double> _varMin)//評価関数
		{
			bool flag = true;
			for (int i = 0; i < var_num; i++)
			{
				if (x[i] > _varMax[i] || x[i] < _varMin[i])
					flag = false;
			}

			functionValue = std::sin(x[0] + x[1]) + std::pow((x[0] - x[1]), 2.0) - 1.5*x[0] + 2.5*x[1] + 1;
			if (!flag)//最大重量を超えなければそのまま
			{
				functionValue = coefficient * functionValue;
			}
			return functionValue;
		}*/
	};

	std::vector<Data> data, prev_data;//操作前後で値を保持するために2個
	Data eliteData;
	GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin);	//コンストラクタ
	bool init();//初期化
	bool selection();//選択

	/*bool uniformityCrossover();//交叉
	bool onePointCrossover();
	bool twoPointCrossover();
	bool tsunoPointCrossover();*/
	bool blxAlphaCrossover();
	bool mutation();//突然変異
	bool calc(bool enableDisplay);//評価関数の計算
	bool calcResult();
	int random(int min, int max);
	double random(int min, double max);
	double random(double min, int max);
	double random(double min, double max);

	~GA();//デコンストラクタ
};


