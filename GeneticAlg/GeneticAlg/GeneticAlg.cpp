#include <iostream>
using namespace std;
#define G 4 //количество генов в хромосоме
#define I 10 //количество особоей в попул€ции

class Ind //Individual
{
    int X[G+1]; //хромосома
public:
    //заполнение хромосомы генами
    Ind() 
    {
        for (int i = 0; i <= G; i++)
            X[i] = rand() % 2; // [0;1]
    }
    //перевод в дес€тичную ——
    int ConvertToDecimal() 
    {
        int dem = 0;
        for (int i = G-1, j = 1; j <= G; i--, j++)
        {
            dem += X[j] * pow(2, i);
        }
        if (X[0] == 1) dem = 0 - dem;
        return dem;
    }
    //рассчЄт значени€ функции
    int FoundY() 
    {
        int Y = ConvertToDecimal();
        Y = pow(Y, 2) + 4;
        return Y;
    }
    //мутаци€ генов хромосомы
    void Mutation()
    {
        int num = rand() % 2;
        int num2 = rand() % G;
        X[num2] = num;
    }

    //вывод генов (двоична€)
    void PrintG() 
    {
        cout << "  ";
        for (int i = 0; i < G; i++)
            cout << X[i];
    }
    //вывод хромосомы (дес€тична€)
    void PrintX()
    {
        cout << "  " << ConvertToDecimal();
    }
    //кроссинговер
    void Crossover(Ind& One)
    {
        int half = G / 2;
        int one = abs(One.ConvertToDecimal());
        int two = abs(this->ConvertToDecimal());
         if (one < two)
         {
             for (int i = 0; i <= half; i++) this->X[i] = One.X[i];
         }
         else
             if (one > two)
             {
                 for (int i = 0; i <= half; i++) One.X[i] = this->X[i];
             }
             else
             {
                 for (int i = 0, j = G-1; i <= half; i++, j--) swap(One.X[i],this->X[j]);
             }
    }
};

class Pop // (Population)
{
    Ind* Arr; //попул€ци€ (массив хромосом)
    float Prob[I]; //веро€тности скрещивани€
public:
    //заполнение попул€ции
    Pop() 
    {
            Arr = new Ind[I];
            for (int i = 0; i < I; i++)
                Prob[i] = 0;
    }
    ~Pop()
    {
        delete[] Arr;
    }
    //вывод попул€ции
    void PrintPop()
    {
        cout << "\n Population: ";
        for (int i = 0; i < I; i++)
            Arr[i].PrintX();
    }
    //ѕроверка значений целевой функции дл€ попул€ции (вывод значений и торможение алгоритма)
    bool FunRes()
    {
        int count = 0, j = 0; 
        cout << "\n Function result: ";
        for (int i = 0; i < I; i++)
        {
            cout << "  " << Arr[i].FoundY();
            if (Arr[i].FoundY() == 4)
            {
                count++;
                j = i;
            }
        }
        if (count > 0)
        {
            cout << "\n      SOLUTION FOUND:\n x =";
            Arr[j].PrintX();
            cout << "  y = " << Arr[j].FoundY() << endl;
            return true;
        }
        return false;
    }
    //‘итнесс функци€ (оценивание попул€ции) + веро€тность скрещивани€ особи
    void Fitness()
    {
        float Fit[I]; //приспособленности  
        float Sum = 0.0;
        cout << "\n Population fitness: ";
        for (int i = 0; i < I; i++)
        {
            Fit[i] = 1.0/Arr[i].FoundY();
            Sum += Fit[i];
            cout << "  " << Fit[i];
        }
        cout << "\n Probability of population: ";
        for (int i = 0; i < I; i++)
        {
            Prob[i] = Fit[i] / Sum;
            cout << "  " << Prob[i];
        }
    }
    //рулеточна€ селекци€
    void Selection()
    {
        cout << "\n Selection: ";
        int count = 0;
        Ind Chosen[I];
        for (int i = 0; i < I; i++)
        {
            float num = (rand() % 10 + 1); // [1;9]
            num = num / 12.0;
            float circle = 0.0;
            for (int j = 0; j < I; j++)
            {
                circle += Prob[j];
                if (num <= circle)
                {
                    Chosen[count] = Arr[j];
                    count++;
                    break;
                }
            }
        }
        for (int i = 0; i < I; i++)
        {
            Arr[i] = Chosen[i];
            Arr[i].PrintX();
        }
    }
    //нова€ попул€ци€ (скрещивание и мут€ци€ попул€ции)
    void NewPop()
    {
        cout << "\n New population: ";
        int half = G / 2;
        int one, two;
        for (int i = 0; i < I; i+=2)
        {
            Arr[i].Crossover(Arr[i + 1]);
            Arr[i].Mutation(); Arr[i + 1].Mutation();
            Arr[i].PrintX(); Arr[i + 1].PrintX();
        }
    }
};

int main()
{
    srand(time(NULL));
    int i = 1;
    Pop one;
    cout << "\n\n      POPULATION # " << i;
    one.PrintPop();
    while (!one.FunRes())
    {
        one.Fitness();
        one.Selection();
        i++;
        cout << "\n\n      POPULATION # " << i;
        one.NewPop();    
    }
}
