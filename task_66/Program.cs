Console.WriteLine ("Введите число: ");
int N = Convert.ToInt32(Console.ReadLine());
Console.WriteLine ("Введите число: ");
int M = Convert.ToInt32(Console.ReadLine());
int sum = 0;
 
 int SumDigit (int num1, int num2) {
    
    if (num1==num2) return num2;
    else return num1 + SumDigit(num1+1,num2);
 }
 if (N>M){
 int summ = SumDigit (M,N);
 Console.WriteLine (summ);
 }
 else {
    int summ = SumDigit (N,M);
    Console.WriteLine (summ);
 }
 