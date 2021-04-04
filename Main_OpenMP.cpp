//Karpov Dmitry MOiAIS 184-1
#include <iostream>
#include <string>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Functions.h"

using namespace std;

#pragma region TASK1
/*Напишите программу, в которой две нити параллельно вычисляют сумму чисел от 1 до N.
Распределите работу по нитям с помощью оператора if языка С.
Для сложения результатов вычисления нитей воспользуйтесь OpenMP-параметром reduction.
Выполните расчёты для N {1,2,5,10,100,1000}*/
void Task1(int N)
{
	int result = 0;
	int sum1 = NULL;
	int sum2 = NULL;
	printf("---------------Task №1---------------\n");
#pragma omp parallel num_threads(2) reduction (+ : result)
	{
		int currentThread = omp_get_thread_num();
		if (currentThread == 0)
		{
			result = Adder(0, N / 2);
			printf("Первый поток посчитал: %d\n", result);
		}
		if (currentThread == 1)
		{
			result = Adder(N / 2 + 1, N);
			printf("Второй поток посчитал: %d\n", result);
		}
	}
	printf("Сумма чисел от 1 до %d = %d\n", N, result);
}
#pragma endregion
#pragma region TASK2
/*Модифицируйте программу таким образом, чтобы она работала для k нитей.
Покажите работу про-граммы для N {2,10,100,1000}, k {2,4,8,16}.*/
void Task2(int N, int proposedK)
{
	printf("-----------------------Task №2-----------------------\n");
	printf("-------------НА ВХОДЕ	N:%d	Потоков:%d-----------\n", N, proposedK);
	int result = 0, k = proposedK;
	//Если задачу нельзя поделить на всех, значит будем уменьшать кол-во нитей.
	//Зачем придумывать велосипед, если есть деректива for ?!
	//Можно сделать костылями так, что бы прям все потоки считали, но будут потоки, которые будут считать НУЛИ, а это не рационально.
	while (N % k != 0)
	{
		k--;
	}
	printf("-------------Потоков ПО ФАКТУ:%d---------------------\n", k);
	int half = N / k;
#pragma omp parallel num_threads(k) reduction (+ : result)
	{
		int currentThread = omp_get_thread_num();
		result = Adder(half * currentThread + 1, half * (currentThread + 1));
		printf("Поток №%d посчитал: %d\n", currentThread, result);
	}
	printf("Сумма чисел от 1 до %d = %d\n", N, result);
}
#pragma endregion
#pragma region TASK3
void Task3(int N, int k)
{
	printf("-----------------------Task №3-----------------------\n");
	printf("-------------НА ВХОДЕ	N:%d	Потоков:%d-----------\n", N, k);
	int result = 0, i;
#pragma omp parallel num_threads(k) reduction(+ : result)
	{
#pragma omp for
		for (i = 1; i <= N; i++)
		{
			int currentThread = omp_get_thread_num();
			result += i;
			printf("[%d]: Sum = %d\n", currentThread, result);
		}
	}
	printf("Sum = %d\n", result);
}
#pragma endregion
#pragma region TASK4
void Task4()
{
	printf("-----------------------Task №4-----------------------\n");
	int sum = 0;
	int  i;
#pragma omp parallel num_threads(4) reduction(+ : sum)
	{
#pragma omp for schedule(guided, 2)
		for (i = 1; i <= 10; i++) {
			int currentThread = omp_get_thread_num();
			sum += i;
			printf("[%d]: Sum = %d\n", currentThread, sum);
			printf("[%d]: calculation of the iteration number %d\n", currentThread, i);
		}
	}
	printf("Sum = %d\n", sum);
}
#pragma endregion
#pragma region TASK5
//Вычисление числа Пи для разных числов потоков, с разной точностью eps...
void Task5(int NTHREADS, const unsigned long numSteps)
{
	printf("-----------------------Task №5-----------------------\n");
	double step;
	double PI25DT = 3.141592653589793238462643;
	double pi = 0;
	double sum = 0.0;
	double x;
#pragma omp parallel num_threads(NTHREADS)
	{
#pragma omp master
		{
			int cntThreads = omp_get_num_threads();
			cout << "OpenMP. number of threads = " << cntThreads << std::endl;
		}
	}
	double clockStart, clockStop;
	step = 1. / static_cast<double>(numSteps);
	clockStart = omp_get_wtime();
#pragma omp parallel for num_threads(NTHREADS) private (x), reduction (+:sum)
	for (int i = 0; i < numSteps; i++)
	{
		x = (i + .5) * step;
		sum = sum + 4.0 / (1. + x * x);
	}
	pi = sum * step;
	clockStop = omp_get_wtime() - clockStart;
	cout << "The value of PI is " << pi << " Error is " << fabs(pi - PI25DT) << std::endl;
	cout << "The time to calculate PI was ";
	double secs = clockStop;
	cout << secs << " seconds\n" << std::endl;
	//Запись в файл
	ofstream out("timeTest.txt", std::ios::app);
	if (out.is_open())
	{
		out << secs << std::endl;
	}
	out.close();
}
#pragma endregion
#pragma region MAIN
int main()
{
	setlocale(LC_ALL, "Russian");
	//Task1
	int* nArray_1 = new int[6]{ 1,2,5,10,100,1000 };
	for (int i = 0; i < 6; i++)
	{
		Task1(nArray_1[i]);
	}
	printf("\n\n\n");
	//Task2
	int* nArray_2 = new int[4]{ 2,10,100,1000 };
	int* kArray_2 = new int[4]{ 2,4,8,16 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Task2(nArray_2[i], kArray_2[j]);
		}
	}
	printf("\n\n\n");
	//Task3
	for (int i = 0; i < 2; i++)   // если поставить i < 4 , будет перебор как по заданию. Но вывод слишком большой...
	{
		for (int j = 0; j < 4; j++)
		{
			Task3(nArray_2[i], kArray_2[j]);
		}
	}
	printf("\n\n\n");
	//Task4
	Task4();
	printf("\n\n\n");
	//Task5
	for (int numThreads = 1; numThreads <= 20; numThreads++)
	{
		//Запись в файл
		ofstream out("timeTest.txt", std::ios::app);
		if (out.is_open())
		{
			out << "Count of threads: " << numThreads << std::endl;
		}
		out.close();
		int* psevdoEps = new int[7]{ 5,25,50,250,500,2500,5000 };
		for (int i = 0; i < 7; i++)
		{
			Task5(numThreads, psevdoEps[i]);
		}
		printf("\n\n\n");
		//Запись в файл, обычная пустая строка
		if (out.is_open())
		{
			out << " " << std::endl;
		}
		out.close();
	}
	return 0;
}
#pragma endregion
