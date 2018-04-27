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
	int max_genom_list;//�̐�
	int var_num;//�i���̌�
	//double crossoverRate = 0.8;//������
	double individualMutationRate = 0.1;//�̓ˑR�ψٗ�
	//double genomMutaionRate = 0.04;//��`�q�ˑR�ψٗ�
	int minNum = 0, maxNum = 0;
	double alpha = 0.5;
public:
	std::vector<double> varMax, varMin;
	double resultSumValue;//�]���֐��̍��v

	class Data//�f�[�^�i�[�p�N���X
	{
	private:
		//double coefficient = 0.01;//�]���֐��p�̒萔
		int var_num;//�ϐ��̐�
	public:
		std::vector<double> x;//�i�������邩�ǂ����̔z��
		double functionValue;//�]���֐��̒l
		double result;

		Data(int _var_num)//�R���X�g���N�^
		{
			var_num = _var_num;

			x.resize(var_num);//isIncluded�̔z��̒����̐ݒ�
		}

		/*double calcResult(std::vector<double> _varMax, std::vector<double> _varMin)//�]���֐�
		{
			bool flag = true;
			for (int i = 0; i < var_num; i++)
			{
				if (x[i] > _varMax[i] || x[i] < _varMin[i])
					flag = false;
			}

			functionValue = std::sin(x[0] + x[1]) + std::pow((x[0] - x[1]), 2.0) - 1.5*x[0] + 2.5*x[1] + 1;
			if (!flag)//�ő�d�ʂ𒴂��Ȃ���΂��̂܂�
			{
				functionValue = coefficient * functionValue;
			}
			return functionValue;
		}*/
	};

	std::vector<Data> data, prev_data;//����O��Œl��ێ����邽�߂�2��
	Data eliteData;
	GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin);	//�R���X�g���N�^
	bool init();//������
	bool selection();//�I��

	/*bool uniformityCrossover();//����
	bool onePointCrossover();
	bool twoPointCrossover();
	bool tsunoPointCrossover();*/
	bool blxAlphaCrossover();
	bool mutation();//�ˑR�ψ�
	bool calc(bool enableDisplay);//�]���֐��̌v�Z
	bool calcResult();
	int random(int min, int max);
	double random(int min, double max);
	double random(double min, int max);
	double random(double min, double max);

	~GA();//�f�R���X�g���N�^
};


