#pragma once
#include <string>
//Кодируем 32 bit
class DES {
public:
	//Генерирует случайные 8 символов - ключ
	static CString encryptionKeyGenerator() {
		//64-битный ключ
		//char -> 8 бит -> 64/8 = 8 символов
		const int count_sumbol = 2;
		const unsigned numberMinSumbol = 32;
		const unsigned numberMaxSumbol = 4294967295;
		CString out_key = "";
		for (unsigned i = 0; i < count_sumbol; i++) {
			out_key.AppendChar( rand() % (numberMaxSumbol - numberMinSumbol) + numberMinSumbol);
		}
		return(out_key);
	}
	
	CString encryptionDES(CString inputText, CString EncryptionKey) {
		CString ciphertext;
		const int lenPackage = 2;			//8 - символов в пакете
		int addSymbols = 0;

		CString EncryptionKeyBin = convertStrToBinary(EncryptionKey);//Конвекируем ключ//+
		//return EncryptionKeyBin;
		generate_keys(EncryptionKeyBin);//?

		//Дополняем тескт длинна которого кратностна пакету //+
		if (inputText.GetLength() % lenPackage != 0) {
			addSymbols = lenPackage - inputText.GetLength() % lenPackage;	// 8 - 9%8 = 8 - 1 = 7 (проверка 7+9=16)
			for (int i = 0; i < addSymbols; i++) inputText.AppendChar('0');						// -повторение символа c заданное число n раз
		}

		
		//По пакетно щифруем
		int i = 0;
		CString packet;
		while (i < inputText.GetLength()) {
			packet = inputText.Mid( i, lenPackage); // строка, содержащая не более, чем len символов данной строки S, начиная с символа номер start
			packet = convertStrToBinary(packet);
			ciphertext += des(packet);
			i += lenPackage;
		}

		//В конце добавляем сивол - кол-ва добавленных символов
		CString addSymbolsStr;
		addSymbolsStr.Format("%i", addSymbols);
		ciphertext += addSymbolsStr;
		return(ciphertext);
	}
	
	CString decryptionDES(CString inputText, CString EncryptionKey) {
		CString encryptedText;
		const int lenPackage = 64;			//64 - символов разряда в бинарном пакете
		const int countSumbol = 32;

		//Определяем сколько символов добавили:
		int addSymbols = (inputText[inputText.GetLength() - 1]  == '1' ) ? 1 : 0;
		inputText = inputText.Left(inputText.GetLength() - 1);


		CString EncryptionKeyBin = convertStrToBinary(EncryptionKey);//Конвекируем ключ
		generate_keys(EncryptionKeyBin);

		// Обращение массива round_keys для дешифрования
		int i = 15;
		int j = 0;
		while (i > j)
		{
			CString temp = round_keys[i];
			round_keys[i] = round_keys[j];
			round_keys[j] = temp;
			i--;
			j++;
		}

		//Дешифрование
		int k = 0;
		CString packet;
		while (k < inputText.GetLength()) {
			packet = inputText.Mid( k, lenPackage); // строка, содержащая не более, чем len символов данной строки S, начиная с символа номер start
			packet = des(packet);
			for (int z = 0; z < lenPackage; z = z + countSumbol) {
				return packet.Mid(z, countSumbol);
				//encryptedText.AppendChar(convertBinaryToDecimal2( packet.Mid(z, countSumbol) ));
			}
			k += lenPackage;
		}
		encryptedText = encryptedText.Left( encryptedText.GetLength() - addSymbols);//Вырезаем символы дополняющие до пакета
		return(encryptedText);
	}

private:
	// Массив для хранения 16 ключей
	CString round_keys[16];
	// Функция для преобразования числа из десятичного числа в двоичное
	//decimal - само число, 
	CString convertDecimalToBinary(unsigned decimal, int minNumberDigits = 32)
	{
		CString binary;
		while (decimal != 0) {
			binary+= decimal % 2 ? "1" : "0";
			decimal = decimal / 2;
		}
		while (binary.GetLength() < minNumberDigits) { binary += "0"; }
		binary.MakeReverse();
		

		return (binary);
	}
	// Функция для преобразования двоичного числа в десятичное
	int convertBinaryToDecimal(CString binary)
	{
		int decimal = 0;
		int counter = 0;
		int size = binary.GetLength();
		for (int i = size - 1; i >= 0; i--)
		{
			if (binary[i] == '1') {
				decimal += pow(2, counter);
			}
			counter++;
		}
		return decimal;
	}
	unsigned convertBinaryToDecimal2(CString binary)
	{
		unsigned decimal = 0;
		unsigned counter = 0;
		unsigned size = binary.GetLength();
		for (int i = size - 1; i >= 0; i--)
		{
			if (binary[i] == '1') {
				decimal += pow(2, counter);
			}
			counter++;
		}
		return decimal;
	}

	// Функция для кругового сдвига влево на 1
	CString shift_left_once(CString key_chunk) {
		CString shifted = "";
		for (int i = 1; i < 28; i++) {
			shifted += key_chunk[i];
		}
		shifted += key_chunk[0];
		return shifted;
	}
	// Функция для кругового сдвига влево на 2
	CString shift_left_twice(CString key_chunk) {
		CString shifted = "";
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j < 28; j++) {
				shifted += key_chunk[j];
			}
			shifted += key_chunk[0];
			key_chunk = shifted;
			shifted = "";
		}
		return key_chunk;
	}
	// Функция для вычисления xor между двумя строками
	CString Xor(CString input_text, CString input_key) {
		CString Ciphertext;
		for (int i = 0; i < input_text.GetLength(); i++) {
			Ciphertext.AppendChar(input_text[i] ^ input_key[i % 4]);
		}
		return(Ciphertext);
	}
	// Функция для генерации 16 ключей.
	void generate_keys(CString key) {
		// The PC1 table
		int pc1[56] = {
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4
		};
		// The PC2 table
		int pc2[48] = {
		14,17,11,24,1,5,
		3,28,15,6,21,10,
		23,19,12,4,26,8,
		16,7,27,20,13,2,
		41,52,31,37,47,55,
		30,40,51,45,33,48,
		44,49,39,56,34,53,
		46,42,50,36,29,32
		};
		// 1. Сжатие ключа с помощью таблицы PC1
		CString perm_key = "";
		for (int i = 0; i < 56; i++) {
			perm_key += key[pc1[i] - 1];
		}
		// 2. Разделение ключа на две равные половины
		CString left = perm_key.Mid(0, 28);					//!!
		CString right = perm_key.Mid(28, 28);				//!!
		for (int i = 0; i < 16; i++) {
			// 3.1. Для раундов 1, 2, 9, 16 key_chunks
			// сдвинуты на единицу.
			if (i == 0 || i == 1 || i == 8 || i == 15) {
				left = shift_left_once(left);
				right = shift_left_once(right);
			}
			// 3.2. Для других раундов key_chunks
			// сдвинуты на два
			else {
				left = shift_left_twice(left);
				right = shift_left_twice(right);
			}
			// Объединение двух частей
			CString combined_key = left + right;
			CString round_key = "";
			// Наконец, используя таблицу PC2 для транспонирования битов ключа
			for (int i = 0; i < 48; i++) {
				round_key += combined_key[pc2[i] - 1];
			}
			round_keys[i] = round_key;
		}

	}
	// Реализация алгоритма
	CString des(CString inputText) {
		// Начальная таблица перестановок
		int initial_permutation[64] = {
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
		};
		// Таблица расширения
		int expansion_table[48] = {
		32,1,2,3,4,5,4,5,
		6,7,8,9,8,9,10,11,
		12,13,12,13,14,15,16,17,
		16,17,18,19,20,21,20,21,
		22,23,24,25,24,25,26,27,
		28,29,28,29,30,31,32,1
		};
		// Поля подстановки. Должен содержать значения
		// от 0 до 15 в любом порядке.
		int substition_boxes[8][4][16] =
		{ {
			14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
			0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
			4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
			15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
		},
		{
			15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
			3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
			0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
			13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
		},
		{
			10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
			13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
			13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
			1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
		},
		{
			7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
			13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
			10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
			3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
		},
		{
			2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
			14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
			4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
			11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
		},
		{
			12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
			10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
			9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
			4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
		},
		{
			4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
			13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
			1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
			6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
		},
		{
			13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
			1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
			7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
			2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
		} };
		// Таблица перестановок
		int permutation_tab[32] = {
		16,7,20,21,29,12,28,17,
		1,15,23,26,5,18,31,10,
		2,8,24,14,32,27,3,9,
		19,13,30,6,22,11,4,25
		};
		// Таблица обратной перестановки
		int inverse_permutation[64] = {
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25
		};
		// 1. Применяя начальную перестановку
		CString perm = "";
		for (int i = 0; i < 64; i++) {
			perm += inputText[initial_permutation[i] - 1];
		}
		// 2. Делим результат на две равные половины
		CString left = perm.Mid(0, 32);						//!!
		CString right = perm.Mid(32, 32);					//!!
		// Обычный текст зашифрован 16 раз
		for (int i = 0; i < 16; i++) {
			CString right_expanded = "";
			// 3.1. Правая половина обычного текста расширена
			for (int i = 0; i < 48; i++) {
				right_expanded += right[expansion_table[i] - 1];
			}; // 3.3. Результат фиксируется ключом
			CString xored = Xor(round_keys[i], right_expanded);
			CString res = "";
			// 3.4. Результат делится на 8 равных частей и проходит
			// через 8 полей подстановки. Пройдя через
			// блок подстановки, каждый блок сокращается с 6 до 4 бит.
			for (int i = 0; i < 8; i++) {
				// Нахождение индексов строки и столбца для поиска // поля подстановки
				CString row1 = xored.Mid(i * 6, 1) + xored.Mid(i * 6 + 5, 1);
				int row = convertBinaryToDecimal(row1);
				CString col1 = xored.Mid(i * 6 + 1, 1) + xored.Mid(i * 6 + 2, 1) + xored.Mid(i * 6 + 3, 1) + xored.Mid(i * 6 + 4, 1);
				int col = convertBinaryToDecimal(col1);
				int val = substition_boxes[i][row][col];
				res += convertDecimalToBinary(val);
			}
			// 3.5. Применяется другая перестановка
			CString perm2 = "";
			for (int i = 0; i < 32; i++) {
				perm2 += res[permutation_tab[i] - 1];
			}
			// 3.6. Результат совпадает с левой половиной.
			xored = Xor(perm2, left);
			// 3.7. Левая и правая части обычного текста меняются местами.
			left = xored;
			if (i < 15) {
				CString temp = right;
				right = xored;
				left = temp;
			}
		}
		// 4. Применяются половинки обычного текста
		CString combined_text = left + right;
		CString ciphertext = "";
		// Применяется обратное к исходной перестановке
		for (int i = 0; i < 64; i++) {
			ciphertext += combined_text[inverse_permutation[i] - 1];
		}
		// И наконец получаем зашифрованный текст
		return ciphertext;
	}

	//Ковектирует текст в двоичный код
	CString convertStrToBinary(CString inputText) {
		const int minNumberDigits = 32;// 8;
		CString outputTextBin;
		for (int i = 0; i < inputText.GetLength(); i++) {
			outputTextBin += convertDecimalToBinary(inputText[i], minNumberDigits);
			//outputTextBin += _T("!");
		}
		return(outputTextBin);
	}
};