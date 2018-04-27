#include "stdafx.h"
#include "GA.h"

GA::GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin) :
	data(std::vector<Data>(_max_genom_list, _var_num)),//dataの初期化
	eliteData(_var_num)
{
	//もらった変数をクラス内変数に格納
	max_genom_list = _max_genom_list;
	var_num = _var_num;
	varMax = _varMax;
	varMin = _varMin;
}

bool GA::init()
{
	for (int i = 0; i < max_genom_list; i++)
	{
		for (int j = 0; j < var_num; j++)
		{
			data[i].x[j] = random(varMin[j], varMax[j]);//遺伝子の初期設定
			printf_s("%lf", data[i].x[j]);
		}
		data[i].calcResult(varMax, varMin);//評価関数
		resultSumValue += data[i].result;//評価関数の合計を計算
		printf_s(" \t Result=%7.4lf\n", data[i].result);
	}
	return true;
}

bool GA::selection()
{
	int max_num = 0;//最も評価の良い個体の番号
	bool ret = false;

	calc(false);

	prev_data = data;

	resultSumValue = 0;
	for (int i = 0; i < max_genom_list; i++)
		//ルーレット選択用に評価関数の合計と一番評価の良い番号を取得
	{
		resultSumValue += prev_data[i].result;
		if (prev_data[i].result > prev_data[max_num].result)
			max_num = i;
	}

	eliteData = prev_data[max_num];//データの先頭は最も評価の良い個体
								   //	eliteData = prev_data[minNum];
	if (eliteData.result - prev_data[minNum].result >= 1)//最も評価の良い個体の変化の監視(デバッグ用)
		ret = true;

	for (int i = 0; i < max_genom_list; i++)
	{
		double selector = random(0.0, 1.0);//乱数を生成
		double needle = 0;//ルーレットの針を生成
		int j = 0;
		for (;; j++)
		{
			needle += (prev_data[j].result / resultSumValue);//ルーレットの針を乱数の値まで進める
			if (needle > selector)
				break;
			if (j == (max_genom_list - 1))
				break;
		}
		data[i] = prev_data[j];
	}
	return ret;
}

/*bool GA::uniformityCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2個ずつ交叉
	{
		for (int j = 0; j < var_num; j++)
		{
			bool isCrossover = (random(0.0, 1.0) >= crossoverRate ? true : false);//trueで交叉なし
			data[i + 1].x[j] = isCrossover ? prev_data[i + 1].x[j] : prev_data[i].x[j];
			//if (i != 0)//先頭のデータは保護
			data[i].x[j] = isCrossover ? prev_data[i].x[j] : prev_data[i + 1].x[j];
		}
	}
	return true;
}

bool GA::onePointCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2個ずつ交叉
	{
		int del1 = random(0, var_num - 1);
		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = 0; j < del1; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}
		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = del1; j < var_num; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}
	}
	return true;
}

bool GA::twoPointCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2個ずつ交叉
	{
		int del1 = random(0, var_num / 2);
		int del2 = random(del1, var_num - 1);
		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = 0; j < del1; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}
		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = del1; j < del2; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}

		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = del2; j < var_num; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}
	}
	return true;
}

bool GA::tsunoPointCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2個ずつ交叉
	{
		int del1 = random(0, var_num - 1);
		int del2 = random(del1, var_num);
		if (random(0.0, 1.0) <= crossoverRate)
		{
			for (int j = del1; j < del2; j++)
			{
				data[i + 1].x[j] = prev_data[i].x[j];
				data[i].x[j] = prev_data[i + 1].x[j];
			}
		}
	}

	return true;
}*/

bool GA::blxAlphaCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2個ずつ交叉
	{
		for (int j = 0; j < var_num; j++)
		{
			double varL, varH;

			if (data[i].x[j] > data[i + 1].x[j])
			{
				varH = data[i].x[j];
				varL = data[i+1].x[j];
			}
			else
			{
				varH = data[i + 1].x[j];
				varL = data[i].x[j];
			}

			bool isCrossover = (random(0.0, 1.0) >= crossoverRate ? true : false);//trueで交叉なし
			std::vector<double> range(var_num);
			for (int k = 0; k < var_num; k++)
			{
				range[k] = std::abs(data[i].x[k] - data[i + 1].x[k]);
			}
			data[i + 1].x[j] = data[i];
			data[i].x[j] = ;
		}
	}
	return true;
}

bool GA::mutation()
{
	for (int i = 0; i < max_genom_list; i++)
	{
		if (random(0.0, 1.0) <= individualMutationRate)//個体突然変異率の計算
		{
			for (int j = 0; j < var_num; j++)
			{
				data[i].x[j] = random(varMin[j], varMax[j]);
			}
		}
	}
	return true;
}

bool GA::calc(bool enableDisplay)
{
	for (int i = 0; i < max_genom_list; i++)
	{
		data[i].calcResult(varMax, varMin);//評価関数の計算
		if (data[i].result < data[minNum].result)
		{
			minNum = i;
		}
		if (data[i].result > data[maxNum].result)
		{
			maxNum = i;
		}
	}
	data[minNum] = eliteData;

	if (enableDisplay)
	{
		for (int i = 0; i < max_genom_list; i++)
		{
			for (int j = 0; j < var_num; j++)
			{
				printf_s("%d", data[i].x[j] ? 1 : 0);//デバッグ用
			}
			printf_s(" \t Result=%.4lf\n", data[i].result);
		}
	}
	return true;
}

int GA::random(int min, int max)
{
	//乱数の設定
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(engine);
}

double GA::random(int min, double max)
{
	return random((double)min, max);
}

double GA::random(double min, int max)
{
	return random(min, (double)max);
}

double GA::random(double min, double max)
{
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(engine);
}



GA::~GA()
{

}
