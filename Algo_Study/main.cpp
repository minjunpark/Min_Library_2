
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string_view>

int main()
{
    constexpr std::string_view haystack =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
        "do eiusmod tempor incididunt ut labore et dolore magna aliqua";

    const std::string_view needle{ "pisci" };

    if (const auto it = std::search(haystack.begin(), haystack.end(),
        std::boyer_moore_searcher(needle.begin(), needle.end()));
        it != haystack.end()
        ) {
        std::cout << "The string " << quoted(needle) << " found at offset "
            << it - haystack.begin() << '\n';
    }
    else {
        std::cout << "The string " << std::quoted(needle) << " not found\n";
    }
}

//#include <stdio.h>
//
//int main()
//{
//	int a,b,c;
//	scanf_s("%d %d %d", &a,&b,&c);
//	if ((a-b+c)%10==0) 
//	{
//		printf("대박");
//	}
//	else 
//	{
//		printf("그럭저럭");
//	}
//	return 0;
//}
//
//
////printf("%d\n",a+b);
////printf("%d\n",a-b);
////printf("%d\n",a*b);
////printf("%d\n",a/b);
////printf("%d\n",a%b);
////printf("%f\n", a / b);