// JBond.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define IN
#define OUT

#define HIDE 0x77

#include <iostream>

template <unsigned int N>
class JBond
{
public:
	constexpr JBond(IN const char* str) { //шифруем by XOR во время компиляции
		for (auto& c : local)
		{
			c = *str++ ^ HIDE;
		};
	};
	void JBond_decode(OUT char* toBuff) const
	{// расшифровка
		for (auto c : local)
		{
			*toBuff++ = c ^ HIDE;
		}
	}
private:
	char local[N] = { 0 };
};

// вычисление лямбдой с constexpr во время компиляции
#define STR(str) \
    []() -> char* { \
        constexpr auto sz = sizeof(str)/sizeof(str[0]); \
        constexpr auto code_str = JBond<sz>(str); \
        static char original_str[sz]; \
        code_str.JBond_decode((char *)original_str); \
        return original_str; \
    }()

int main()
{
	std::cout << "Hey, I see you" << "\n";

	char* pszStr = STR("Hello Bond"); // 
	std::cout << pszStr << "\n";
	std::cout << STR("Im a spy");
	return 0;
}

