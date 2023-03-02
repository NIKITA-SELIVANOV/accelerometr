Console.WriteLine ("Введите число: ");
int number = Convert.ToInt32(Console.ReadLine());

NaturalNum (number);

void NaturalNum (int num) {
    if (num==0) return;
    Console.Write($" {num}");

    NaturalNum(num -1);

}

