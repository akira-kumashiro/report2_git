#include "stdafx.h"
#include "GA.h"

GA::GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin) :
	data(std::vector<Data>(_max_genom_list, _var_num)),//data�̏�����
	eliteData(_var_num)
{
	//��������ϐ����N���X���ϐ��Ɋi�[
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
			data[i].x[j] = random(varMin[j], varMax[j]);//��`�q�̏����ݒ�
			printf_s("%lf", data[i].x[j]);
		}
		//data[i].calcResult(varMax, varMin);//�]���֐�
		//resultSumValue += data[i].result;//�]���֐��̍��v���v�Z
		printf_s(" \t f(x,y)=%7.4lf\t Result=%9.5lf\n", data[i].functionValue, data[i].result);
	}
	prev_data = data;
	calcResult();
	return true;
}

bool GA::selection()
{
	int max_num = 0;//�ł��]���̗ǂ��̂̔ԍ�
	bool ret = false;

	calc(false);

	//resultSumValue = 0;
	//calcResult();
	for (int i = 0; i < max_genom_list; i++)
		//���[���b�g�I��p�ɕ]���֐��̍��v�ƈ�ԕ]���̗ǂ��ԍ����擾
	{
		//resultSumValue += prev_data[i].result;
		if (data[i].result > data[max_num].result)
			max_num = i;
	}

	eliteData = data[max_num];//�f�[�^�̐擪�͍ł��]���̗ǂ���
								   //	eliteData = prev_data[minNum];
	if (-eliteData.functionValue + prev_data[max_num].functionValue != 0)//�ł��]���̗ǂ��̂̕ω��̊Ď�(�f�o�b�O�p)
		ret = true;
	prev_data = data;
	for (int i = 0; i < max_genom_list; i++)
	{
		double selector = random(0.0, 1.0);//�����𐶐�
		double needle = 0;//���[���b�g�̐j�𐶐�
		int j = 0;
		for (;; j++)
		{
			needle += (prev_data[j].result / resultSumValue);//���[���b�g�̐j�𗐐��̒l�܂Ői�߂�
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

	for (int i = 0; i < max_genom_list; i += 2)//2������
	{
		for (int j = 0; j < var_num; j++)
		{
			bool isCrossover = (random(0.0, 1.0) >= crossoverRate ? true : false);//true�Ō����Ȃ�
			data[i + 1].x[j] = isCrossover ? prev_data[i + 1].x[j] : prev_data[i].x[j];
			//if (i != 0)//�擪�̃f�[�^�͕ی�
			data[i].x[j] = isCrossover ? prev_data[i].x[j] : prev_data[i + 1].x[j];
		}
	}
	return true;
}

bool GA::onePointCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2������
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

	for (int i = 0; i < max_genom_list; i += 2)//2������
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

	for (int i = 0; i < max_genom_list; i += 2)//2������
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

	for (int i = 0; i < max_genom_list; i += 2)//2������
	{
		for (int j = 0; j < var_num; j++)
		{
			double ave, length;//varL, varH, 

			/*if (data[i].x[j] > data[i + 1].x[j])
			{
				varH = data[i].x[j];
				varL = data[i + 1].x[j];
			}
			else
			{
				varH = data[i + 1].x[j];
				varL = data[i].x[j];
			}*/
			ave = (data[i].x[j] + data[i + 1].x[j]) / 2;
			//length = varH - varL;
			length = std::abs((data[i].x[j] - data[i + 1].x[j]));

			data[i].x[j] = random(ave - length * (1 + alpha*2) / 2, ave + length * (1 + alpha) / 2);
			data[i + 1].x[j] = random(ave - length * (1 + alpha) / 2, ave + length * (1 + alpha) / 2);

			/*bool isCrossover = (random(0.0, 1.0) >= crossoverRate ? true : false);//true�Ō����Ȃ�
			std::vector<double> range(var_num);
			for (int k = 0; k < var_num; k++)
			{
				range[k] = std::abs(data[i].x[k] - data[i + 1].x[k]);
			}
			data[i + 1].x[j] = data[i];
			data[i].x[j] = ;*/
		}
	}
	return true;
}

bool GA::mutation()
{
	for (int i = 0; i < max_genom_list; i++)
	{
		if (random(0.0, 1.0) <= individualMutationRate)//�̓ˑR�ψٗ��̌v�Z
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
	calcResult();
	for (int i = 0; i < max_genom_list; i++)
	{
		//data[i].calcResult(varMax, varMin);//�]���֐��̌v�Z
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

	calcResult();
	if (enableDisplay)
	{
		for (int i = 0; i < max_genom_list; i++)
		{
			for (int j = 0; j < var_num; j++)
			{
				printf_s("%lf,", data[i].x[j]);//�f�o�b�O�p
			}
			printf_s(" \t f(x,y)=%7.4lf\t Result=%7.4lf\n", data[i].functionValue, data[i].result);
		}
	}
	return true;
}

bool GA::calcResult()
{
	int maxNum = 0;
	double seg;
	for (int i = 0; i < max_genom_list; i++)
	{
		data[i].functionValue = std::sin(data[i].x[0] + data[i].x[1]) + std::pow((data[i].x[0] - data[i].x[1]), 2.0) - 1.5*data[i].x[0] + 2.5*data[i].x[1] + 1;
		if (data[maxNum].functionValue < data[i].functionValue)
		{
			maxNum = i;
		}
	}
	seg = data[maxNum].functionValue;
	resultSumValue = 0;

	for (int i = 0; i < max_genom_list; i++)
	{
		bool flag = true;
		double coefficient = 0.0001;//�]���֐��p�̒萔
		for (int j = 0; j < var_num; j++)
		{
			if (data[i].x[j] > varMax[j] || data[i].x[j] < varMin[j])
				flag = false;
		}
		data[i].result = std::pow((data[i].functionValue - seg), 2.0);

		if (!flag)//�ő�d�ʂ𒴂��Ȃ���΂��̂܂�
		{
			data[i].result *= coefficient;
		}
		resultSumValue += data[i].result;
	}
	return true;
}

int GA::random(int min, int max)
{
	//�����̐ݒ�
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
