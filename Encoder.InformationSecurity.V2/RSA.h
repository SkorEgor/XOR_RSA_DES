
#include <stdlib.h>
#include <iomanip>


#include <utility>
#include <exception>
#include <tuple>

//Тип для хранения n,e и d
class NED {
public:
	unsigned n;
	unsigned e;
	unsigned d;
};

//Хранит методы для шифрования RSA
class RSA {
public:

	//Генерирует n, e, d
	static NED keyGen() {

		NED outputValues;

		//СЧИТАЕМ : p и q < 16 bit (unsigned int -> 32 bit -> до 4.294.967.295)
		//Генеририруем для них простые числа
		unsigned int p = simple_number_generator(16);
		unsigned int q = simple_number_generator(16);

		//Вычисляем модуль n — произведение наших p и q
		outputValues.n = p * q;

		//Вычисляем функцию Эйлера:
		unsigned int fi = (p - 1) * (q - 1);
		int r;
		do {
			outputValues.e = simple_number_generator(16);
			r = gcd(outputValues.e, fi);
		} while (r != 1);

		//Найдем d
		outputValues.d = Extended_Euclid(outputValues.e, fi);// Extended_Euclid(e, fi);

		return(outputValues);
	}


	//Зашифровевает символ по открытому ключу {e, n}
	static unsigned encryptionRSA(wchar_t inputSymbol, unsigned inputE, unsigned inputN) {
		return(pow_mod((unsigned)inputSymbol, inputE, inputN));
	}

	//Зашифровевает строку символо по открытому ключу {e, n}
	//На выходе строка, с по символьным шифрованием, шифротекст котороых, на отдельных строках
	static CString encryptionRSA(CString input_text, unsigned inputE, unsigned inputN) {
		CString Ciphertext;
		CString str;
		for (int i = 0; i < input_text.GetLength(); i++) {
			str.Format("%u", encryptionRSA(input_text[i], inputE, inputN));

			Ciphertext += str + _T("\r\n");
		}
		return(Ciphertext);
	}


	//Расшифровывает символ по закрытому ключу {d, n}
	static unsigned decryptionRSA(unsigned ciphertext, unsigned inputD, unsigned inputN) {
		return(pow_mod(ciphertext, inputD, inputN));
	}

	//Расшифровывает последовательности символов,раздленных строкой, по открытому ключу {e, n}
	//Выходе строка,расшифрованного сообщения
	static CString decryptionRSA(CString input_text, unsigned inputD, unsigned inputN) {
		CString decodedSymbol;
		CString decodedtext;
		unsigned decodedint;
		while (input_text.GetLength()) {
			decodedSymbol = input_text.Left(input_text.Find("\n"));		//+Получаем строчку

			decodedint = _atoi64(decodedSymbol);						//Переводим в int
			decodedint = decryptionRSA(decodedint, inputD, inputN);		//Дешифруем
			decodedtext.AppendChar(decodedint);							//Сохраняем в выходном тексте


			input_text = input_text.Right(input_text.GetLength() - (decodedSymbol.GetLength() + 1));
		}
		//decodedtext.Format(_T("%u"), decodedint);
		
		return(decodedtext);
	}

protected:
	/*Прописанны методы для методов выше*/


	//Возведение в степень по модулю
	//Параметры:
	// 1) num - основание степени;
	// 2) pow - показатель степень;
	// 3) mod - делитель.
	static unsigned pow_mod(unsigned num, unsigned pow, unsigned mod)
	{
		unsigned long long test;
		unsigned long long n = num;
		for (test = 1; pow; pow >>= 1)
		{
			if (pow & 1)
				test = ((test % mod) * (n % mod)) % mod;
			n = ((n % mod) * (n % mod)) % mod;
		}

		return test; /* note this is potentially lossy */
	}


	//Генератор простых чисел
	//Параметр: кол-во бит числа в 2-ной системе
	static unsigned int simple_number_generator(int number_bits) {
		unsigned int output_number;			//Выходное число
		const int countTest = 10;			//Кол-во проверок на простоту
		bool not_simple;
		do {
			output_number = 0;

			//первый и последний биты равны единицы
			output_number = output_number + 1;
			output_number = output_number + pow(2, number_bits - 1);

			//Проходим по битам и рандомно записываем их значения
			for (int i = 1; i < number_bits - 1; i++) {
				if (rand() % 2) {
					output_number = output_number + pow(2, i);
				}
			}

			//Делаем проверку по малой теореме Ферма
			not_simple = false;
			for (int i = 1; i < countTest; i++) {
				if (pow_mod(1 + rand() % 100, output_number - 1, output_number) != 1) {
					not_simple = true;
					break;
				}
			}

		} while (not_simple);	//Если проверку не прошло, начинаем сначала

		//Возвращаем сгененированное число
		return(output_number);
	}


	//Алгоритм Евклида нахождения НОД (наибольшего общего делителя)
	//Параметры: 1 и 2 числа (!=0), для которых ищем наибольший общий делитель
	static int gcd(unsigned a, unsigned b) {
		//b: true - gcd(b, a % b); false - a.
		return b ? gcd(b, a % b) : a;
	}


	//Расширенный Алгоритм Евклида
	static long long Extended_Euclid(long long a, long long n)
	{
		long long t = 0, newt = 1;
		long long r = n, newr = a;
		while (newr != 0) {
			auto quotient = r / newr;
			std::tie(t, newt) = std::make_tuple(newt, t - quotient * newt);
			std::tie(r, newr) = std::make_tuple(newr, r - quotient * newr);
		}
		/*if (r > 1)
			throw runtime_error("a is not invertible");*/
		if (t < 0)
			t += n;
		return t;
	}
};